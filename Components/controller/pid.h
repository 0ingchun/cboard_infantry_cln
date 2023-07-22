#ifndef PID_H
#define PID_H


#include "struct_typedef.h"


enum PID_MODE
{
    PID_POSITION = 0,
    PID_DELTA
};


typedef struct
{
    fp32 Q_coefficient;
    fp32 last_state;
    fp32 last_input;
    fp32 last_input_hat;
    fp32 d_hat;
    fp32 (*Nominal_Input_Cal)(fp32 current_state, fp32 last_state);
}NominalDOB;


extern void NominalDOB_Init(NominalDOB* instance, fp32 Q_coefficient, fp32 (*Input_Fcn)(fp32,fp32));
extern fp32 NominalDOB_Update(NominalDOB* instance, fp32 current_state, fp32 current_input);


typedef struct
{
    uint8_t mode;
    //PID 三参数
    fp32 Kp;
    fp32 Ki;
    fp32 Kd;

    fp32 max_out;  //最大输出
    fp32 max_iout; //最大积分输出
		fp32 derivative_output_filter_coefficient;
    fp32 proportion_output_filter_coefficient;
    fp32 set;
    fp32 fdb;

    fp32 out;
    fp32 Pout;
    fp32 Iout;
    fp32 Dout;
    fp32 Dbuf[3];  //微分项 0最新 1上一次 2上上次
    fp32 error[3]; //误差项 0最新 1上一次 2上上次
} pid_type_def;


/**
  * @brief          pid struct data init
  * @param[out]     pid: PID结构数据指针
  * @param[in]      mode: PID_POSITION:普通PID
  *                 PID_DELTA: 差分PID
  * @param[in]      PID: 0: kp, 1: ki, 2:kd
  * @param[in]      max_out: pid最大输出
  * @param[in]      max_iout: pid最大积分输出
  * @retval         none
  */
extern void PID_init(pid_type_def *pid, uint8_t mode, const fp32 PID[3], fp32 max_out, fp32 max_iout);


/**
  * @brief          pid计算
  * @param[out]     pid: PID结构数据指针
  * @param[in]      ref: 反馈数据
  * @param[in]      set: 设定值
  * @retval         pid输出
  */
extern fp32 PID_calc(pid_type_def *pid, fp32 ref, fp32 set);


/**
  * @brief          pid 输出清除
  * @param[out]     pid: PID结构数据指针
  * @retval         none
  */
extern void PID_clear(pid_type_def *pid);


#endif
