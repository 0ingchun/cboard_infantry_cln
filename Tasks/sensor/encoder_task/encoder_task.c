#include "encoder_task.h"


/**
  * @brief          读取编码器任务
  * @param[in]      delta_count: 编码器增量
  * @param[in]      count_per_rev: 每圈编码器数字
  * @param[in]      radius: 轮子半径
  * @retval         底盘速度 m/s
  */
static fp32 get_chassis_speed(uint32_t delta_count, fp32 count_per_rev, fp32 radius);


#undef SELF
#define SELF encoderTask
encoder_task_t encoderTask = {0};


/**
  * @brief          读取编码器任务
  * @param[in]      argument: NULL
  * @retval         无
  */
__NO_RETURN void encoder_task(__attribute__((unused)) void * argument)
{
    //TODO 轮子半径和每圈多少脉冲
    SELF.counts_per_revolution = 1;             //每圈多少脉冲
    SELF.wheel_radius = 1;                      //轮子半径
    SELF.reversed = 0;                          //是否反向

    encoder_init();

    TASK_CTRL_INIT(SELF, 0, 1, ENABLE);

    TASK_LOOP_BEGIN(SELF)

    //判断是否重设原点
    if (SELF.flag_reset_origin) SELF.position = 0; SELF.flag_reset_origin = 0;

    //获取读数
    SELF.raw_count = encoder_get_count();
    SELF.dir = encoder_get_direction();

    //TODO 判断寄存器是否溢出

    //计算速度
    SELF.delta_count = SELF.raw_count - SELF.last_count;
    SELF.speed = get_chassis_speed(SELF.delta_count, SELF.counts_per_revolution, SELF.wheel_radius);

    //判断是否需要反向
    if (SELF.reversed) SELF.speed = -SELF.speed;
    if (SELF.reversed) SELF.dir = !SELF.dir;

    //积分位置
    SELF.position += SELF.speed;

    //更新上一次度数
    SELF.last_count = SELF.raw_count;

    TASK_LOOP_END(SELF)
}


/**
  * @brief          读取编码器任务
  * @param[in]      delta_count: 编码器增量
  * @param[in]      count_per_rev: 每圈编码器数字
  * @param[in]      radius: 轮子半径
  * @retval         底盘速度 m/s
  */
static fp32 get_chassis_speed(uint32_t delta_count, fp32 count_per_rev, fp32 radius)
{
    return ((fp32)delta_count / count_per_rev) * radius;
}