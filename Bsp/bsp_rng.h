#ifndef BSP_RNG_H
#define BSP_RNG_H


#include "struct_typedef.h"


/**
  * @brief          获取随机数
  * @retval         生成的32bit随机数
  */
extern uint32_t RNG_get_random_num(void);


/**
  * @brief          指定范围获取随机数
  * @param[in]      min: 最小值
  * @param[in]      max: 最大值
  * @retval         生成的随机数
  */
extern int32_t RNG_get_random_range(int min, int max);


#endif
