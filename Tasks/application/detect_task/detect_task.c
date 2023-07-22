#include "detect_task.h"


/**
  * @brief          初始化SELF.error_list,赋值 offline_time, online_time, priority
  * @param[in]      time:系统时间
  * @retval         无
  */
void detect_init(uint32_t time);


#undef SELF
#define SELF detectTask
detect_task_t detectTask = {0};


/**
  * @brief          检测任务
  * @param[in]      argument: NULL
  * @retval         无
  */
__NO_RETURN void detect_task(__attribute__((unused)) void *argument)
{
    TASK_CTRL_INIT(SELF, 400, 10, ENABLE);

    //初始化
    detect_init(xTaskGetTickCount());
    //初始化看门狗
    HAL_IWDG_Init(&hiwdg);

    TASK_LOOP_BEGIN(SELF)

    SELF.system_time = xTaskGetTickCount();

    SELF.error_num_display = ERROR_LIST_LENGHT;
    SELF.error_list[ERROR_LIST_LENGHT].is_lost = 0;
    SELF.error_list[ERROR_LIST_LENGHT].error_exist = 0;

    for (int i = 0; i < ERROR_LIST_LENGHT; i++)
    {
        //未使能，跳过
        if (SELF.error_list[i].enable == 0) continue;

        //判断掉线
        if (SELF.system_time - SELF.error_list[i].new_time > SELF.error_list[i].set_offline_time)
        {
            if (SELF.error_list[i].error_exist == 0)
            {
                //记录错误以及掉线时间
                SELF.error_list[i].is_lost = 1;
                SELF.error_list[i].error_exist = 1;
                SELF.error_list[i].lost_time = SELF.system_time;
            }
            //判断错误优先级， 保存优先级最高的错误码
            if (SELF.error_list[i].priority > SELF.error_list[SELF.error_num_display].priority) SELF.error_num_display = i;
            
            SELF.error_list[ERROR_LIST_LENGHT].is_lost = 1;
            SELF.error_list[ERROR_LIST_LENGHT].error_exist = 1;
            
            //如果提供解决函数，运行解决函数
            if (SELF.error_list[i].solve_lost_fun != NULL) SELF.error_list[i].solve_lost_fun();
        }
        else if (SELF.system_time - SELF.error_list[i].work_time < SELF.error_list[i].set_online_time)
        {
            //刚刚上线，可能存在数据不稳定，只记录不丢失，
            SELF.error_list[i].is_lost = 0;
            SELF.error_list[i].error_exist = 1;
        }
        else
        {
            SELF.error_list[i].is_lost = 0;
            //判断是否存在数据错误
            if (SELF.error_list[i].data_is_error != 0) SELF.error_list[i].error_exist = 1;
            else SELF.error_list[i].error_exist = 0;
            //计算频率
            if (SELF.error_list[i].new_time > SELF.error_list[i].last_time)
            {
                SELF.error_list[i].frequency = configTICK_RATE_HZ / (fp32)(SELF.error_list[i].new_time - SELF.error_list[i].last_time);
            }
        }
    }

    //喂狗
    HAL_IWDG_Refresh(&hiwdg);

    TASK_LOOP_END(SELF)
}


/**
  * @brief          获取设备对应的错误状态
  * @param[in]      toe:设备目录
  * @retval         true(错误) 或者false(没错误)
  */
bool_t toe_is_error(uint8_t toe)
{
    return (SELF.error_list[toe].error_exist == 1);
}


/**
  * @brief          钩子
  * @param[in]      toe:设备目录
  * @retval         无
  */
void detect_hook(uint8_t toe)
{
    SELF.error_list[toe].last_time = SELF.error_list[toe].new_time;
    SELF.error_list[toe].new_time = xTaskGetTickCount();
    
    if (SELF.error_list[toe].is_lost)
    {
        SELF.error_list[toe].is_lost = 0;
        SELF.error_list[toe].work_time = SELF.error_list[toe].new_time;
    }
    
    if (SELF.error_list[toe].data_is_error_fun != NULL)
    {
        if (SELF.error_list[toe].data_is_error_fun())
        {
            SELF.error_list[toe].error_exist = 1;
            SELF.error_list[toe].data_is_error = 1;

            if (SELF.error_list[toe].solve_data_error_fun != NULL)
            {
                SELF.error_list[toe].solve_data_error_fun();
            }
        }
        else
        {
            SELF.error_list[toe].data_is_error = 0;
        }
    }
    else
    {
        SELF.error_list[toe].data_is_error = 0;
    }
}


/**
  * @brief          初始化SELF.error_list,赋值 offline_time, online_time, priority
  * @param[in]      time:系统时间
  * @retval         无
  */
void detect_init(uint32_t time)
{
    //设置离线时间，上线稳定工作时间，优先级
    uint16_t set_item[ERROR_LIST_LENGHT][3] =
    {
        {1000, 1000, 1000},     //DBUS
        {50, 10, 11},           //chassis
        {50, 10, 11},           //break
        {50, 10, 11},           //encoder
        {50, 3, 7},             //board gyro
        {50, 5, 7},             //board accel
        {50, 200, 7},           //board mag
        {50, 100, 5},           //referee
    };

    for (uint32_t i = 0; i < ERROR_LIST_LENGHT; i++)
    {
        SELF.error_list[i].set_offline_time = set_item[i][0];
        SELF.error_list[i].set_online_time = set_item[i][1];
        SELF.error_list[i].priority = set_item[i][2];
        SELF.error_list[i].data_is_error_fun = NULL;
        SELF.error_list[i].solve_lost_fun = NULL;
        SELF.error_list[i].solve_data_error_fun = NULL;

        SELF.error_list[i].enable = 1;
        SELF.error_list[i].error_exist = 1;
        SELF.error_list[i].is_lost = 1;
        SELF.error_list[i].data_is_error = 1;
        SELF.error_list[i].frequency = 0.0f;
        SELF.error_list[i].new_time = time;
        SELF.error_list[i].last_time = time;
        SELF.error_list[i].lost_time = time;
        SELF.error_list[i].work_time = time;
    }
}
