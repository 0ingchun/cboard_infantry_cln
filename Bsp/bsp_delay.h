#ifndef BSP_DELAY_H
#define BSP_DELAY_H


#include "struct_typedef.h"


/**
 * @brief           由主频计算tick每微秒和tick每毫秒
 * @return          无
 */
extern void delay_init(void);


/**
 * @brief           延时n微秒
 * @param[in]       nus: 要延时的微秒数
 * @return          无
 */
extern void delay_us(uint16_t nus);


/**
 * @brief           延时n毫秒
 * @param[in]       nus: 要延时的毫秒数
 * @return          无
 */
extern void delay_ms(uint16_t nms);


#endif

