#include "bsp_rng.h"
#include "main.h"
#include "rng.h"

/**
  * @brief          获取随机数
  * @retval         生成的32bit随机数
  */
uint32_t RNG_get_random_num(void)
{
    uint32_t rng;
    HAL_RNG_GenerateRandomNumber(&hrng, &rng);
    return rng;
}


/**
  * @brief          指定范围获取随机数
  * @param[in]      min: 最小值
  * @param[in]      max: 最大值
  * @retval         生成的随机数
  */
int32_t RNG_get_random_range(int min, int max)
{
    int32_t random;
    random = (int32_t)(RNG_get_random_num() % (max - min + 1)) + min;
    return random;
}
