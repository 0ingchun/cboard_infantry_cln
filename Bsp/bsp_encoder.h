#ifndef BSP_ENCODER_H
#define BSP_ENCODER_H


#include "struct_typedef.h"


/**
 * @brief           初始化编码器计数
 * @return          无
 */
extern void encoder_init(void);


/**
 * @brief           获取编码器计数
 * @return          编码器计数
 */
extern uint32_t encoder_get_count(void);


/**
 * @brief           获取编码器方向
 * @return          正传 1,反转 0
 */
extern bool_t encoder_get_direction(void);


#endif //BSP_ENCODER_H
