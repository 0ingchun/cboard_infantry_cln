#ifndef DETECT_TASK_H
#define DETECT_TASK_H


#include "task_common.h"
#include "iwdg.h"


//错误码以及对应设备顺序
enum errorList
{
    DBUS_TOE = 0,
    CHASSIS_MOTOR1_TOE,
    CHASSIS_BREAK_TOE,
    CHASSIS_ENCODER_TOE,
    BOARD_GYRO_TOE,
    BOARD_ACCEL_TOE,
    BOARD_MAG_TOE,
    REFEREE_TOE,
    ERROR_LIST_LENGHT,
};

//故障检测结构体
typedef struct __attribute__((packed))
{
    uint32_t new_time;
    uint32_t last_time;
    uint32_t lost_time;
    uint32_t work_time;
    uint16_t set_offline_time : 12;
    uint16_t set_online_time : 12;
    uint8_t enable : 1;
    uint8_t priority : 4;
    uint8_t error_exist : 1;
    uint8_t is_lost : 1;
    uint8_t data_is_error : 1;

    fp32 frequency;
    bool_t (*data_is_error_fun)(void);
    void (*solve_lost_fun)(void);
    void (*solve_data_error_fun)(void);
} error_t;


typedef struct
{
    task_ctrl_t taskCtrl;                           //控制结构体

    //detect_task
    uint32_t system_time;                           //当前系统时间
    error_t error_list[ERROR_LIST_LENGHT + 1];      //故障检测列表
    uint8_t error_num_display;                      //优先级最高的故障
} detect_task_t;


extern detect_task_t detectTask;


/**
  * @brief          检测任务
  * @param[in]      argument: NULL
  * @retval         无
  */
extern void detect_task(__attribute__((unused)) void *argument);


/**
  * @brief          获取设备对应的错误状态
  * @param[in]      toe:设备目录
  * @retval         true(错误) 或者false(没错误)
  */
extern bool_t toe_is_error(uint8_t err);


/**
  * @brief          钩子
  * @param[in]      toe:设备目录
  * @retval         无
  */
extern void detect_hook(uint8_t toe);


#endif
