#ifndef BSP_IMU_PWM_H
#define BSP_IMU_PWM_H


#include "struct_typedef.h"


/**
  * @brief          初始化IMU加热电阻PWM
  * @retval         无
  */
extern void imu_pwm_init(void);


/**
  * @brief          设置IMU加热电阻PWM
  * @param[in]      pwm: PWM比较寄存器值
  * @retval         无
  */
extern void imu_pwm_set(uint16_t pwm);


#endif
