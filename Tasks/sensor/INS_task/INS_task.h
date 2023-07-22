#ifndef INS_Task_H
#define INS_Task_H


#include "struct_typedef.h"
#include "main.h"
#include "cmsis_os.h"
#include "bsp_imu_pwm.h"
#include "bsp_spi.h"
#include "bmi088driver.h"
#include "ist8310driver.h"
#include "pid.h"
#include "ahrs.h"
#include "calibrate_task.h"
#include "detect_task.h"
#include "bsp_delay.h"
#include "spi.h"


#define SPI_DMA_GYRO_LENGHT       8
#define SPI_DMA_ACCEL_LENGHT      9
#define SPI_DMA_ACCEL_TEMP_LENGHT 4


#define IMU_DR_SHFITS        0
#define IMU_SPI_SHFITS       1
#define IMU_UPDATE_SHFITS    2
#define IMU_NOTIFY_SHFITS    3


#define BMI088_GYRO_RX_BUF_DATA_OFFSET  1
#define BMI088_ACCEL_RX_BUF_DATA_OFFSET 2

//ist83100原始数据在缓冲区buf的位置
#define IST8310_RX_BUF_DATA_OFFSET 16


#define TEMPERATURE_PID_KP 1600.0f //温度控制PID的kp
#define TEMPERATURE_PID_KI 0.2f    //温度控制PID的ki
#define TEMPERATURE_PID_KD 0.0f    //温度控制PID的kd

#define TEMPERATURE_PID_MAX_OUT   4500.0f //温度控制PID的max_out
#define TEMPERATURE_PID_MAX_IOUT 4400.0f  //温度控制PID的max_iout

#define TEMP_PWM_MAX 5000 //mpu6500控制温度的设置TIM的重载值，即给PWM最大为 MPU6500_TEMP_PWM_MAX - 1


#define INS_TASK_INIT_TIME 7 //任务开始初期 delay 一段时间

#define INS_YAW_ADDRESS_OFFSET    0
#define INS_PITCH_ADDRESS_OFFSET  1
#define INS_ROLL_ADDRESS_OFFSET   2

#define INS_GYRO_X_ADDRESS_OFFSET 0
#define INS_GYRO_Y_ADDRESS_OFFSET 1
#define INS_GYRO_Z_ADDRESS_OFFSET 2

#define INS_ACCEL_X_ADDRESS_OFFSET 0
#define INS_ACCEL_Y_ADDRESS_OFFSET 1
#define INS_ACCEL_Z_ADDRESS_OFFSET 2

#define INS_MAG_X_ADDRESS_OFFSET 0
#define INS_MAG_Y_ADDRESS_OFFSET 1
#define INS_MAG_Z_ADDRESS_OFFSET 2

extern int32_t imu_angle_go; //我拉的屎

typedef struct
{
    task_ctrl_t taskCtrl;                           //控制结构体

    //INS_task
    fp32 INS_angle[3];                              //欧拉角 单位 rad
} INS_task_t;

extern INS_task_t INSTask;


/**
  * @brief          imu任务, 初始化 bmi088, ist8310, 计算欧拉角
  * @param[in]      argument: NULL
  * @retval         无
  */
extern void INS_task(__attribute__((unused)) void *argument);


/**
  * @brief          校准陀螺仪
  * @param[out]     cali_scale: 陀螺仪的比例因子，1.0f为默认值，不修改
  * @param[out]     cali_offset: 陀螺仪的零漂，采集陀螺仪的静止的输出作为offset
  * @param[out]     time_count: 陀螺仪的时刻，每次在gyro_offset调用会加1,
  * @retval         无
  */
extern void INS_cali_gyro(fp32 cali_scale[3], fp32 cali_offset[3], uint16_t *time_count);


/**
  * @brief          校准陀螺仪设置，将从flash或者其他地方传入校准值
  * @param[in]      cali_scale: 陀螺仪的比例因子，1.0f为默认值，不修改
  * @param[in]      cali_offset: 陀螺仪的零漂
  * @retval         无
  */
extern void INS_set_cali_gyro(fp32 cali_scale[3], fp32 cali_offset[3]);


#endif
