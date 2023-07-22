#ifndef BSP_LED_H
#define BSP_LED_H


#include "struct_typedef.h"


/**
  * @brief          初始化PWM用于驱动RGB
  * @retval         无
  */
extern void aRGB_led_init(void);


/**
  * @brief          显示RGB
  * @param[in]      aRGB:0xaaRRGGBB,'aa' 是透明度,'RR'是红色,'GG'是绿色,'BB'是蓝色
  * @retval         无
  */
extern void aRGB_led_show(uint32_t aRGB);


#endif
