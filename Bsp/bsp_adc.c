#include "bsp_adc.h"
#include "adc.h"


/**
 * @brief           开始转换并获取ADC转换结果
 * @param[in]       ADCx: 要开始转换的ADC
 * @param[in]       ch: 要开始转换的ADC通道
 * @return          ADC转换结果(0-4095)
 */
static uint16_t adcx_get_chx_value(ADC_HandleTypeDef *ADCx, uint32_t ch);


/**
 * @brief           获取红外传感器距离
 * @param[in]       ADCx: 要开始转换的ADC
 * @param[in]       ch: 要开始转换的ADC通道
 * @return          距离(mm)
 */
static fp32 get_ir_distance(ADC_HandleTypeDef *ADCx, uint32_t ch);


//ADC校准值
volatile fp32 voltage_vrefint_proportion = 8.0586080586080586080586080586081e-4f;


/**
 * @brief           由内部电压基准校准ADC
 * @return          无
 */
void init_vrefint_reciprocal(void)
{
    uint32_t total_adc = 0;
    for(uint8_t i = 0; i < 200; i++)
    {
        total_adc += adcx_get_chx_value(&hadc1, ADC_CHANNEL_VREFINT);
    }

    voltage_vrefint_proportion = 200 * 1.2f / (fp32)total_adc;
}


// TODO 改成线程安全
/**
 * @brief           开始转换并获取ADC转换结果
 * @param[in]       ADCx: 要开始转换的ADC
 * @param[in]       ch: 要开始转换的ADC通道
 * @return          ADC转换结果(0-4095)
 */
static uint16_t adcx_get_chx_value(ADC_HandleTypeDef *ADCx, uint32_t ch)
{
    static ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ch;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

    HAL_StatusTypeDef res;
    do {
        res = HAL_ADC_ConfigChannel(ADCx, &sConfig);
    } while (res != HAL_OK);

    HAL_ADC_Start(ADCx);

    HAL_ADC_PollForConversion(ADCx, 10);
    return (uint16_t)HAL_ADC_GetValue(ADCx);
}


/**
 * @brief           获取芯片内部测量温度
 * @return          芯片温度(摄氏度)
 */
fp32 get_temperature(void)
{
    uint16_t val;
    fp32 temperature;

    val = adcx_get_chx_value(&hadc1, ADC_CHANNEL_TEMPSENSOR);
    temperature = (fp32)val * voltage_vrefint_proportion;
    temperature = (temperature - 0.76f) * 400.0f + 25.0f;

    return temperature;
}


/**
 * @brief           获取24V电池电压
 * @return          电池电压(伏特)
 */
fp32 get_battery_voltage(void)
{
    fp32 voltage;
    uint16_t val;

    val = adcx_get_chx_value(&hadc3, ADC_CHANNEL_8);
    voltage =  (fp32)val * voltage_vrefint_proportion * 10.090909090909090909090909090909f;

    return voltage;
}


/**
 * @brief           获取硬件版本号
 * @return          硬件版本号(数字)
 */
uint8_t get_hardware_version(void)
{
    uint8_t hardware_version;
    hardware_version = HAL_GPIO_ReadPin(HW0_GPIO_Port, HW0_Pin)
                                | (HAL_GPIO_ReadPin(HW1_GPIO_Port, HW1_Pin)<<1)
                                | (HAL_GPIO_ReadPin(HW2_GPIO_Port, HW2_Pin)<<2);

    return hardware_version;
}
