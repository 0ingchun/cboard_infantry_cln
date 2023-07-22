#ifndef IR_TASK_H
#define IR_TASK_H


#include "task_common.h"
#include "bsp_adc.h"


typedef struct
{
    task_ctrl_t taskCtrl;                           //控制结构体

    //IR_task
    bool_t reversed;                                //是否反向
    uint32_t raw_data;                              //原始数据
    bool_t dir;                                     //旋转方向
    uint32_t last_data;                             //上一次数据
    uint32_t delta_data;                            //数据增量
    fp32 speed;                                     //底盘速度
    fp32 position;                                  //底盘位置
    bool_t flag_reset_origin;                       //重设原点
} IR_task_t;


extern IR_task_t IRTask;


/**
  * @brief          读取红外距离传感器任务
  * @param[in]      argument: NULL
  * @retval         无
  */
extern void IR_task(__attribute__((unused)) void * argument);


#endif //IR_TASK_H
