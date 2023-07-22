#include "bsp_crc32.h"
#include "crc.h"


/**
 * @brief           获取CRC32校验值
 * @param[in]       data: 数据指针
 * @param[in]       len: 数据长度
 * @return          校验值
 */
uint32_t get_crc32_check_sum(uint32_t *data, uint32_t len)
{
    return HAL_CRC_Calculate(&hcrc, data, len);
}


/**
 * @brief           验证附加在数据末尾的CRC32校验值
 * @param[in]       data: 数据指针(包含末尾校验数据)
 * @param[in]       len: 数据长度(包含末尾校验数据)
 * @return          结果
 */
bool_t verify_crc32_check_sum(uint32_t *data, uint32_t len)
{
    static uint32_t crc32;
    crc32 = get_crc32_check_sum(data, len-1);
    return (crc32 == data[len-1]);
}


/**
 * @brief           将CRC32校验值附加在数据末尾
 * @param[in,out]   data: 数据指针
 * @param[in]       len: 数据长度
 * @return          无
 */
void append_crc32_check_sum(uint32_t *data, uint32_t len)
{
    uint32_t crc32;
    crc32 = get_crc32_check_sum(data, len-1);
    data[len-1] = crc32;
}

