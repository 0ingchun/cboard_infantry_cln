#include "IR_task.h"


#undef SELF
#define SELF IRTask
IR_task_t IRTask = {0};


//TODO 距离传感器任务
/**
  * @brief          读取红外距离传感器任务
  * @param[in]      argument: NULL
  * @retval         无
  */
__NO_RETURN void IR_task(__attribute__((unused)) void * argument)
{
    SELF.reversed = 0;                          //是否反向

    TASK_CTRL_INIT(SELF, 100, 1, ENABLE);

    TASK_LOOP_BEGIN(SELF)



    TASK_LOOP_END(SELF)
}
