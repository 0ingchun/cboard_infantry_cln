#include "buzzer_task.h"

/**
  * @brief          使得蜂鸣器响
  * @param[in]      num:响声次数
  * @retval         无
  */
static void buzzer_warn_error(uint8_t num);


#undef SELF
#define SELF buzzerTask
buzzer_task_t buzzerTask = {0};


/**
  * @brief          蜂鸣器任务
  * @param[in]      argument: NULL
  * @retval         无
  */
__NO_RETURN void buzzer_task(__attribute__((unused)) void *argument)
{
    SELF.psc = 1679;                    //蜂鸣器PWM定时器分频
    SELF.pwm = 50;                       //蜂鸣器PWM比较值
    SELF.show_num_max = 100;            //多少个循环完成一次蜂鸣

    buzzer_init();

    TASK_CTRL_INIT(SELF, 500, 10, ENABLE);

    TASK_LOOP_BEGIN(SELF)

    //有错误
    if(detectTask.error_num_display != ERROR_LIST_LENGHT)
    {
        buzzer_warn_error(detectTask.error_num_display+1);
    }
    else
    {
        buzzer_off();
    }

    TASK_LOOP_END(SELF)
}


/**
  * @brief          使得蜂鸣器响
  * @param[in]      num:响声次数
  * @retval         无
  */
static void buzzer_warn_error(uint8_t num)
{
    if(SELF.show_num == 0 && SELF.stop_num == 0)
    {
        SELF.show_num = num;
        SELF.stop_num = SELF.show_num_max;
    }
    else if(SELF.show_num == 0)
    {
        SELF.stop_num--;
        buzzer_off();
    }
    else
    {
        static uint8_t tick = 0;
        tick++;
        if(tick < SELF.show_num_max / 2)
        {
            buzzer_off();
        }
        else if(tick < SELF.show_num_max)
        {
            buzzer_on(SELF.psc, SELF.pwm);
        }
        else
        {
            tick = 0;
            SELF.show_num--;
        }
    }
}


