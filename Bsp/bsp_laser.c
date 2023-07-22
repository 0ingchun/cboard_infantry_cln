#include "bsp_laser.h"
#include "main.h"
#include "tim.h"


/**
  * @brief          初始化激光发射器PWM
  * @retval         无
  */
void laser_init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}


/**
  * @brief          开启激光发射器
  * @retval         无
  */
void laser_on(void)
{
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 8399);
}


/**
  * @brief          关闭激光发射器
  * @retval         无
  */
void laser_off(void)
{
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
}
