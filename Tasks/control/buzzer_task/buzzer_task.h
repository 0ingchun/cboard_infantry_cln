#ifndef BUZZER_TASK_H
#define BUZZER_TASK_H


#include "task_common.h"
#include "bsp_buzzer.h"
#include "detect_task.h"


typedef struct
{
    task_ctrl_t taskCtrl;                       //控制结构体

    //buzzer_warn_error
    uint8_t show_num_max;                       //多少个循环完成一次蜂鸣
    uint8_t show_num;                           //已经展示的次数
    uint8_t stop_num;                           //还需要展示的次数
    uint16_t psc;                               //蜂鸣器PWM定时器分频
    uint16_t pwm;                               //蜂鸣器PWM比较值
} buzzer_task_t;


extern buzzer_task_t buzzerTask;


/**
  * @brief          蜂鸣器任务
  * @param[in]      argument: NULL
  * @retval         无
  */
extern void buzzer_task(__attribute__((unused)) void *argument);


#endif
