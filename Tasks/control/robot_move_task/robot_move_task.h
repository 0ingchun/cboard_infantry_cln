#include "task_common.h"

#include "CAN_receive.h"
#include "remote_control.h"

#include "INS_task.h"

typedef struct
{
    const motor_measure_t *chassis_motor_measure;
    const RC_ctrl_t *GIMBAL;

} chassis_motor_t;

typedef struct
{
    const motor_measure_t *gimbal_motor_measure;
    const RC_ctrl_t *GIMBAL;

} gimbal_motor_t;