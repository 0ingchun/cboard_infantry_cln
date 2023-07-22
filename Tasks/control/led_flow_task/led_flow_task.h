#ifndef LED_FLOW_TASK_H
#define LED_FLOW_TASK_H


#include "task_common.h"
#include "bsp_led.h"


typedef struct
{
    task_ctrl_t taskCtrl;                           //控制结构体

    //led_flow_task
    uint16_t change_time;                           //改变一次颜色经过多少个循环
    fp32 delta_alpha;                               //透明通道差值
    fp32 delta_red;                                 //红色通道差值
    fp32 delta_green;                               //绿色通道差值
    fp32 delta_blue;                                //蓝色通道差值
    fp32 alpha;                                     //透明通道当前值
    fp32 red;                                       //红色通道当前值
    fp32 green;                                     //绿色通道当前值
    fp32 blue;                                      //蓝色通道当前值
    uint16_t i;                                     //颜色模式循环中间变量
    uint16_t j;                                     //颜色现实循环中间变量
    uint32_t aRGB;                                  //显示的颜色
} led_flow_task_t;


extern led_flow_task_t ledFlowTask;


/**
  * @brief          led RGB任务
  * @param[in]      argument: NULL
  * @retval         无
  */
extern void led_flow_task(__attribute__((unused)) void * argument);

#endif //LED_FLOW_TASK_H



