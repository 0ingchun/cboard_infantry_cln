#ifndef TASK_COMMON_H
#define TASK_COMMON_H


#include "struct_typedef.h"
#include "cmsis_os.h"
#include "main.h"


typedef struct
{
    uint8_t enabled;
    uint32_t loop_time;

} task_ctrl_t;


#define TASK_CTRL_INIT(task, init_delay, loop_delay, enable)     do {(task).taskCtrl.enabled=(enable); (task).taskCtrl.loop_time=(loop_delay); osDelay(init_delay);} while(0)
#define TASK_LOOP_BEGIN(task)                   while(1) { if ((task).taskCtrl.enabled == ENABLE) {
#define TASK_LOOP_END(task)                     }osDelay((task).taskCtrl.loop_time);}


#endif //TASK_COMMON_H
