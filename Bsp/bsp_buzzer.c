#include "bsp_buzzer.h"
#include "tim.h"


/**
 * @brief           初始化蜂鸣器PWM
 * @return          无
 */
void buzzer_init(void)
{
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
}


/**
 * @brief           设置蜂鸣器PWM
 * @param[in]       psc: 计时器分频数
 * @param[in]       pwm: PWM通道比较值
 * @return          无
 */
void buzzer_on(uint16_t psc, uint16_t pwm)
{
    __HAL_TIM_PRESCALER(&htim4, psc);
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm);

}

/**
 * @brief           关闭蜂鸣器PWM
 * @return          无
 */
void buzzer_off(void)
{
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 0);
}
