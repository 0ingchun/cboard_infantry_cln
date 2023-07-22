#ifndef BSP_CRC32_H
#define BSP_CRC32_H


#include "struct_typedef.h"
#include "main.h"


/**
 * @brief           获取CRC32校验值
 * @param[in]       data: 数据指针
 * @param[in]       len: 数据长度
 * @return          校验值
 */
extern uint32_t get_crc32_check_sum(uint32_t *data, uint32_t len);


/**
 * @brief           验证附加在数据末尾的CRC32校验值
 * @param[in]       data: 数据指针(包含末尾校验数据)
 * @param[in]       len: 数据长度(包含末尾校验数据)
 * @return          结果
 */
extern bool_t  verify_crc32_check_sum(uint32_t *data, uint32_t len);


/**
 * @brief           将CRC32校验值附加在数据末尾
 * @param[in,out]   data: 数据指针
 * @param[in]       len: 数据长度
 * @return          无
 */
extern void append_crc32_check_sum(uint32_t *data, uint32_t len);


#endif
