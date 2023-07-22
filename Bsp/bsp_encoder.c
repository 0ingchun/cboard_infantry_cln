#include "bsp_encoder.h"
#include "main.h"
#include "tim.h"


/**
 * @brief           初始化编码器计数
 * @return          无
 */
void encoder_init(void)
{
    HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
    __HAL_TIM_SET_COUNTER(&htim1, 16384);
}


/**
 * @brief           获取编码器计数
 * @return          编码器计数
 */
uint32_t encoder_get_count(void)
{
    return __HAL_TIM_GET_COUNTER(&htim1);
}


/**
 * @brief           获取编码器方向
 * @return          正传 1,反转 0
 */
bool_t encoder_get_direction(void)
{
    return __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1);
}
