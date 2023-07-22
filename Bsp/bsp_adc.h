#ifndef BSP_ADC_H
#define BSP_ADC_H


#include "struct_typedef.h"
#include "main.h"


/**
 * @brief           由内部电压基准校准ADC
 * @return          无
 */
extern void init_vrefint_reciprocal(void);


/**
 * @brief           获取芯片内部测量温度
 * @return          芯片温度(摄氏度)
 */
extern fp32 get_temperature(void);


/**
 * @brief           获取24V电池电压
 * @return          电池电压(伏特)
 */
extern fp32 get_battery_voltage(void);


/**
 * @brief           获取硬件版本号
 * @return          硬件版本号(数字)
 */
extern uint8_t get_hardware_version(void);


#endif
