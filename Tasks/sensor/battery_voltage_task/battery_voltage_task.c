#include "battery_voltage_task.h"


#define FULL_BAT_VOLTAGE     25.2f
#define LOW_BAT_VOLTAGE      22.2f   //about 20%
#define VOLTAGE_DROP         0.00f


/**
  * @brief          计算电源百分比
  * @param[in]      pvParameters: NULL
  * @retval         [0.0-1.0] 电量百分比
  */
static fp32 calc_battery_percentage(float voltage);


#undef SELF
#define SELF batteryVoltageTask
battery_voltage_task_t batteryVoltageTask = {0};


/**
  * @brief          电池测量任务
  * @param[in]      pvParameters: NULL
  * @retval         无
  */
__NO_RETURN void battery_voltage_task(__attribute__((unused)) void *argument)
{
    init_vrefint_reciprocal();

    TASK_CTRL_INIT(SELF, 1000, 200, ENABLE);

    TASK_LOOP_BEGIN(SELF)

    SELF.battery_voltage = get_battery_voltage() + VOLTAGE_DROP;
    SELF.electricity_percentage = calc_battery_percentage(SELF.battery_voltage);

    TASK_LOOP_END(SELF)
}


/**
  * @brief          计算电源百分比
  * @param[in]      argument: NULL
  * @retval         [0.0-1.0] 电量百分比
  */
static fp32 calc_battery_percentage(float voltage)
{
    fp32 percentage;
    fp32 voltage_2 = voltage * voltage;
    fp32 voltage_3 = voltage_2 * voltage;
    
    if(voltage < 19.5f)
    {
        percentage = 0.0f;
    }
    else if(voltage < LOW_BAT_VOLTAGE)
    {
        percentage = 0.005664f * voltage_3 - 0.3386f * voltage_2 + 6.765f * voltage - 45.17f;
    }
    else if(voltage < FULL_BAT_VOLTAGE)
    {
        percentage = 0.02269f * voltage_3 - 1.654f * voltage_2 + 40.34f * voltage - 328.4f;
    }
    else
    {
        percentage = 1.0f;
    }
    if(percentage < 0.0f) percentage = 0.0f;
    if(percentage > 1.0f) percentage = 1.0f;

    //another formulas
    //另一套公式
//    if(voltage < 19.5f)
//    {
//        percentage = 0.0f;
//    }
//    else if(voltage < 22.5f)
//    {
////        percentage = 0.05776f * (voltage - 22.5f) * (voltage_2 - 39.0f * voltage + 383.4f) + 0.5f;
//        percentage = 0.05021f * voltage_3 - 3.075f * voltage_2 + 62.77f * voltage - 427.02953125f;
//    }
//    else if(voltage < 25.5f)
//    {
////        percentage = 0.01822f * (voltage - 22.5f) * (voltage_2 - 52.05f * voltage + 637.0f) + 0.5f;
//        percentage = 0.0178f * voltage_3 - 1.292f * voltage_2 + 31.41f * voltage - 254.903125f;
//    }
//    else
//    {
//        percentage = 1.0f;
//    }

    return percentage;
}
