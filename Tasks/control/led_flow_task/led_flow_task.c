#include "led_flow_task.h"


#define RGB_FLOW_COLOR_LEN   6
//blue-> green(dark)-> red -> blue(dark) -> green(dark) -> red(dark) -> blue
//蓝 -> 绿(灭) -> 红 -> 蓝(灭) -> 绿 -> 红(灭) -> 蓝 
uint32_t RGB_flow_color[RGB_FLOW_COLOR_LEN + 1] = {0xFF0000FF, 0x0000FF00, 0xFFFF0000, 0x000000FF, 0xFF00FF00, 0x00FF0000, 0xFF0000FF};


#undef SELF
#define SELF ledFlowTask
led_flow_task_t ledFlowTask = {0};


/**
  * @brief          led RGB任务
  * @param[in]      argument: NULL
  * @retval         无
  */
__NO_RETURN void led_flow_task(__attribute__((unused)) void * argument)
{
    SELF.change_time = 50;            //改变一次颜色经过多少个循环

    aRGB_led_init();

    TASK_CTRL_INIT(SELF, 0, 20, ENABLE);

    TASK_LOOP_BEGIN(SELF)

    if (SELF.j == SELF.change_time) {

        SELF.i++;
        SELF.j = 0;
        if (SELF.i >= RGB_FLOW_COLOR_LEN) SELF.i = 0;

        SELF.alpha = (fp32) ((RGB_flow_color[SELF.i] & 0xFF000000) >> 24);
        SELF.red = (fp32) ((RGB_flow_color[SELF.i] & 0x00FF0000) >> 16);
        SELF.green = (fp32) ((RGB_flow_color[SELF.i] & 0x0000FF00) >> 8);
        SELF.blue = (fp32) ((RGB_flow_color[SELF.i] & 0x000000FF) >> 0);

        SELF.delta_alpha = (fp32) ((RGB_flow_color[SELF.i + 1] & 0xFF000000) >> 24) - (fp32) ((RGB_flow_color[SELF.i] & 0xFF000000) >> 24);
        SELF.delta_red = (fp32) ((RGB_flow_color[SELF.i + 1] & 0x00FF0000) >> 16) - (fp32) ((RGB_flow_color[SELF.i] & 0x00FF0000) >> 16);
        SELF.delta_green = (fp32) ((RGB_flow_color[SELF.i + 1] & 0x0000FF00) >> 8) - (fp32) ((RGB_flow_color[SELF.i] & 0x0000FF00) >> 8);
        SELF.delta_blue = (fp32) ((RGB_flow_color[SELF.i + 1] & 0x000000FF) >> 0) - (fp32) ((RGB_flow_color[SELF.i] & 0x000000FF) >> 0);

        SELF.delta_alpha /= SELF.change_time;
        SELF.delta_red /= SELF.change_time;
        SELF.delta_green /= SELF.change_time;
        SELF.delta_blue /= SELF.change_time;
    }

    SELF.alpha += SELF.delta_alpha;
    SELF.red += SELF.delta_red;
    SELF.green += SELF.delta_green;
    SELF.blue += SELF.delta_blue;

    SELF.aRGB = ((uint32_t) (SELF.alpha)) << 24 | ((uint32_t) (SELF.red)) << 16 | ((uint32_t) (SELF.green)) << 8 | ((uint32_t) (SELF.blue)) << 0;
    aRGB_led_show(SELF.aRGB);

    SELF.j++;

    TASK_LOOP_END(SELF)
}