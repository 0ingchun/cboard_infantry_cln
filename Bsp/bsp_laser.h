#ifndef BSP_LASER_H
#define BSP_LASER_H


#include "struct_typedef.h"


/**
  * @brief          初始化激光发射器PWM
  * @retval         无
  */
extern void laser_init(void);


/**
  * @brief          开启激光发射器
  * @retval         无
  */
extern void laser_on(void);


/**
  * @brief          关闭激光发射器
  * @retval         无
  */
extern void laser_off(void);


#endif
