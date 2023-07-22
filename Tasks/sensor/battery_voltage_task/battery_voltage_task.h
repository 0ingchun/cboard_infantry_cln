#ifndef VOLTAGE_TASK_H
#define VOLTAGE_TASK_H


#include "task_common.h"
#include "bsp_adc.h"


typedef struct
{
    task_ctrl_t taskCtrl;                           //控制结构体

    //battery_voltage_task
    fp32 battery_voltage;                           //电池电压
    fp32 electricity_percentage;                    //电池百分比
} battery_voltage_task_t;


extern battery_voltage_task_t batteryVoltageTask;


/**
  * @brief          电池测量任务
  * @param[in]      argument: NULL
  * @retval         无
  */
extern void battery_voltage_task(__attribute__((unused)) void *argument);


#endif
