#ifndef ENCODER_TASK_H
#define ENCODER_TASK_H


#include "task_common.h"
#include "bsp_encoder.h"


typedef struct
{
    task_ctrl_t taskCtrl;                           //控制结构体

    //encoder_task
    uint16_t counts_per_revolution;                 //每圈多少脉冲
    fp32 wheel_radius;                              //轮子半径
    bool_t reversed;                                //是否反向
    uint32_t raw_count;                             //原始度数
    bool_t dir;                                     //旋转方向
    uint32_t last_count;                            //上一次度数
    uint32_t delta_count;                           //编码器增量
    fp32 speed;                                     //底盘速度
    fp32 position;                                  //底盘位置
    bool_t flag_reset_origin;                       //重设原点

} encoder_task_t;


extern encoder_task_t encoderTask;


/**
  * @brief          读取编码器任务
  * @param[in]      argument: NULL
  * @retval         无
  */
extern void encoder_task(__attribute__((unused)) void * argument);


#endif //ENCODER_TASK_H
