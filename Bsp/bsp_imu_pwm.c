#include "bsp_imu_pwm.h"
#include "main.h"
#include "tim.h"


/**
  * @brief          初始化IMU加热电阻PWM
  * @retval         无
  */
void imu_pwm_init(void)
{
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
}


/**
  * @brief          设置IMU加热电阻PWM
  * @param[in]      pwm: PWM比较寄存器值
  * @retval         无
  */
void imu_pwm_set(uint16_t pwm)
{
    __HAL_TIM_SetCompare(&htim10, TIM_CHANNEL_1, pwm);
}
