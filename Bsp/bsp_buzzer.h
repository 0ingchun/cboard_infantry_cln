#ifndef BSP_BUZZER_H
#define BSP_BUZZER_H


#include "struct_typedef.h"
#include "main.h"


/**
 * @brief           初始化蜂鸣器PWM
 * @return          无
 */
extern void buzzer_init(void);


/**
 * @brief           设置蜂鸣器PWM
 * @param[in]       psc: 计时器分频数
 * @param[in]       pwm: PWM通道比较值
 * @return          无
 */
extern void buzzer_on(uint16_t psc, uint16_t pwm);


/**
 * @brief           关闭蜂鸣器PWM
 * @return          无
 */
extern void buzzer_off(void);


#endif
