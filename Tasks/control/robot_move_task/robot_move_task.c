#include "robot_move_task.h"

#include "CAN_receive.h"
#include "bsp_can.h"
#include "struct_typedef.h"
#include "pid.h"
#include "remote_control.h"

#include "INS_task.h"

__NO_RETURN void robot_move_task(__attribute__((unused)) void * argument)
{

    const fp32 PID_chassis_angle_in[3]={3,0.00000045,0.0000001};
    const fp32 PID_chassis_speed_in[3]={1,0,5};
    //手动底盘pid

    //const fp32 PID_gimbal_angle_in[3]={3,0.00135,0.05};//好似能用的参数
    const fp32 PID_gimbal_yaw_angle_in[3]={3,0.00135,0.05};
    const fp32 PID_gimbal_yaw_speed_in[3]={4,0,0};
    const fp32 PID_gimbal_pitch_angle_in[3]={3,0.00835,0.05};
    const fp32 PID_gimbal_pitch_speed_in[3]={2,0,0};
    //手动云台pid

    const fp32 PID_yaw_ground_in[3]={50000,0.0005,0.005};
    const fp32 PID_pitch_ground_in[3]={50000,0.0005,0.005};
    //对地定向pid

    const fp32 PID_yaw_chassis_in[3]={120,0,0.00005};
    const fp32 PID_pitch_chassis_in[3]={200,0.005,0.005};
    //对底盘定向pid

    pid_type_def pid_angle[6];
    pid_type_def pid_speed[6];
    //0-3为地盘，4-5为云台

    pid_type_def pid_yaw_ground;
    pid_type_def pid_pitch_ground;
    //云台对地定向

    pid_type_def pid_yaw_chassis;
    pid_type_def pid_pitch_chassis;
    //云台对底盘定向

    gimbal_motor_t gimbal_motor;
    chassis_motor_t chassis_motor[4];
    gimbal_motor.GIMBAL = get_remote_control_point();//极值玄学获取遥控器数据
    //一些玄学易寄结构体

    for (int chmotor_id = 0; chmotor_id < 4; chmotor_id++) {
        chassis_motor[chmotor_id].chassis_motor_measure = get_chassis_motor_measure_point(chmotor_id);
    }//赋一下地盘电机接受结构体
    for (int pid_n = 0; pid_n < 4; pid_n++) {
        PID_init( &pid_angle[pid_n], PID_POSITION, PID_chassis_angle_in, 20000, 30000);
        PID_init( &pid_speed[pid_n], PID_POSITION, PID_chassis_speed_in, 20000, 30000);
        //3508: 10000,2000
        //6020: 20000,30000
    }//0-3地盘电机pid
    PID_init( &pid_angle[4], PID_POSITION, PID_gimbal_yaw_angle_in, 20000, 30000);
    PID_init( &pid_speed[4], PID_POSITION, PID_gimbal_yaw_speed_in, 20000, 30000);
    PID_init( &pid_angle[5], PID_POSITION, PID_gimbal_pitch_angle_in, 20000, 30000);
    PID_init( &pid_speed[5], PID_POSITION, PID_gimbal_pitch_speed_in, 20000, 30000);
    //4-5云台电机pid
    //PID_init( &pid_imu_angle, PID_POSITION, PID_imu_angle_in, 20000, 30000);
    PID_init( &pid_yaw_ground, PID_POSITION, PID_yaw_ground_in, 20000, 30000);
    PID_init( &pid_pitch_ground, PID_POSITION, PID_pitch_ground_in, 20000, 30000);
    //云台对地定向pid
    PID_init( &pid_yaw_chassis, PID_POSITION, PID_yaw_chassis_in, 20000, 30000);
    PID_init( &pid_pitch_chassis, PID_POSITION, PID_pitch_chassis_in, 20000, 30000);
    //云台对底盘定向pid

    //gimble_motor.chassis_motor_measure = get_yaw_gimbal_motor_measure_point();
    //chassis_motor.chassis_motor_measure = get_chassis_motor_measure_point();

    int32_t motor_front_left = 0, motor_front_right = 0, motor_back_left = 0, motor_back_right = 0, motor_gimbal_pitch = 0, motor_gimbal_yaw = 0;
    float rm_mt_g = 0.08, rm_mt_c = 2;
    //定义所有电机输出参

    int16_t gimbal_motor_ecd_temp[4] = {0, 0, 0, 0};
    //云台双轴角度暂存数据

    fp32 ins_angle_temp[3] = {0, 0, 0};
    //imu暂存数据0yaw1pitch2row

    for (int angle_id = 0; angle_id < 3; ++angle_id) {
        ins_angle_temp[angle_id] = INSTask.INS_angle[angle_id];
    }
    //初始化imu角度暂存

    gimbal_motor_ecd_temp[0] = get_yaw_gimbal_motor_measure_point()->ecd;
    gimbal_motor_ecd_temp[1] = get_pitch_gimbal_motor_measure_point()->ecd;
    //初始化电机位置暂存

    while (1) {
        //开始判断模式

        if (gimbal_motor.GIMBAL->rc.s[1] == 2) {

            PID_calc(&pid_angle[0], chassis_motor[0].chassis_motor_measure->ecd,
                     chassis_motor[0].chassis_motor_measure->ecd - gimbal_motor.GIMBAL->rc.ch[3] * rm_mt_c +
                     gimbal_motor.GIMBAL->rc.ch[2] * rm_mt_c);
            PID_calc(&pid_speed[0], chassis_motor[0].chassis_motor_measure->speed_rpm, pid_angle[0].out);
            motor_front_right = pid_speed[0].out;

            PID_calc(&pid_angle[1], chassis_motor[1].chassis_motor_measure->ecd,
                     chassis_motor[1].chassis_motor_measure->ecd + gimbal_motor.GIMBAL->rc.ch[3] * rm_mt_c +
                     gimbal_motor.GIMBAL->rc.ch[2] * rm_mt_c);
            PID_calc(&pid_speed[1], chassis_motor[1].chassis_motor_measure->speed_rpm, pid_angle[1].out);
            motor_front_left = pid_speed[1].out;

            PID_calc(&pid_angle[2], chassis_motor[2].chassis_motor_measure->ecd,
                     chassis_motor[2].chassis_motor_measure->ecd + gimbal_motor.GIMBAL->rc.ch[3] * rm_mt_c +
                     gimbal_motor.GIMBAL->rc.ch[2] * rm_mt_c);
            PID_calc(&pid_speed[2], chassis_motor[2].chassis_motor_measure->speed_rpm, pid_angle[2].out);
            motor_back_left = pid_speed[2].out;

            PID_calc(&pid_angle[3], chassis_motor[3].chassis_motor_measure->ecd,
                     chassis_motor[3].chassis_motor_measure->ecd - gimbal_motor.GIMBAL->rc.ch[3] * rm_mt_c +
                     gimbal_motor.GIMBAL->rc.ch[2] * rm_mt_c);
            PID_calc(&pid_speed[3], chassis_motor[3].chassis_motor_measure->speed_rpm, pid_angle[3].out);
            motor_back_right = pid_speed[3].out;

        }//差速转向

        if (gimbal_motor.GIMBAL->rc.s[1] == 3) {

            PID_calc(&pid_angle[0], chassis_motor[0].chassis_motor_measure->ecd,
                     chassis_motor[0].chassis_motor_measure->ecd - gimbal_motor.GIMBAL->rc.ch[3] * rm_mt_c +
                     gimbal_motor.GIMBAL->rc.ch[2] * rm_mt_c);
            PID_calc(&pid_speed[0], chassis_motor[0].chassis_motor_measure->speed_rpm, pid_angle[0].out);
            motor_front_right = pid_speed[0].out;

            PID_calc(&pid_angle[1], chassis_motor[1].chassis_motor_measure->ecd,
                     chassis_motor[1].chassis_motor_measure->ecd + gimbal_motor.GIMBAL->rc.ch[3] * rm_mt_c +
                     gimbal_motor.GIMBAL->rc.ch[2] * rm_mt_c);
            PID_calc(&pid_speed[1], chassis_motor[1].chassis_motor_measure->speed_rpm, pid_angle[1].out);
            motor_front_left = pid_speed[1].out;

            PID_calc(&pid_angle[2], chassis_motor[2].chassis_motor_measure->ecd,
                     chassis_motor[2].chassis_motor_measure->ecd + gimbal_motor.GIMBAL->rc.ch[3] * rm_mt_c -
                     gimbal_motor.GIMBAL->rc.ch[2] * rm_mt_c);
            PID_calc(&pid_speed[2], chassis_motor[2].chassis_motor_measure->speed_rpm, pid_angle[2].out);
            motor_back_left = pid_speed[2].out;

            PID_calc(&pid_angle[3], chassis_motor[3].chassis_motor_measure->ecd,
                     chassis_motor[3].chassis_motor_measure->ecd - gimbal_motor.GIMBAL->rc.ch[3] * rm_mt_c -
                     gimbal_motor.GIMBAL->rc.ch[2] * rm_mt_c);
            PID_calc(&pid_speed[3], chassis_motor[3].chassis_motor_measure->speed_rpm, pid_angle[3].out);
            motor_back_right = pid_speed[3].out;

        }//麦轮平移

        if(gimbal_motor.GIMBAL->rc.s[0] == 3){

            if(gimbal_motor.GIMBAL->rc.ch[0] > 5 || gimbal_motor.GIMBAL->rc.ch[0] < -5){

                gimbal_motor_ecd_temp[2] = get_yaw_gimbal_motor_measure_point()->ecd;

                gimbal_motor_ecd_temp[0] = gimbal_motor_ecd_temp[2] - gimbal_motor.GIMBAL->rc.ch[0] * rm_mt_g;

                PID_calc(&pid_yaw_chassis, get_yaw_gimbal_motor_measure_point()->ecd,gimbal_motor_ecd_temp[2] - gimbal_motor.GIMBAL->rc.ch[0] * rm_mt_g);

                motor_gimbal_yaw = pid_yaw_chassis.out;

                ins_angle_temp[0] = INSTask.INS_angle[0];

            }//yaw

            if(gimbal_motor.GIMBAL->rc.ch[0] < 5 && gimbal_motor.GIMBAL->rc.ch[0] > -5){

                PID_calc(&pid_yaw_ground, INSTask.INS_angle[0],ins_angle_temp[0]);
                motor_gimbal_yaw = pid_yaw_ground.out;

            }

            if(gimbal_motor.GIMBAL->rc.ch[1] > 5 || gimbal_motor.GIMBAL->rc.ch[1] < -5){

                gimbal_motor_ecd_temp[3] = get_pitch_gimbal_motor_measure_point()->ecd;

                gimbal_motor_ecd_temp[1] = gimbal_motor_ecd_temp[3] - gimbal_motor.GIMBAL->rc.ch[1] * rm_mt_g;

                PID_calc(&pid_pitch_chassis, get_pitch_gimbal_motor_measure_point()->ecd,gimbal_motor_ecd_temp[3] - gimbal_motor.GIMBAL->rc.ch[1] * rm_mt_g);

                motor_gimbal_pitch = pid_pitch_chassis.out;

                ins_angle_temp[1] = INSTask.INS_angle[1];

            }//pitch

            if(gimbal_motor.GIMBAL->rc.ch[1] < 5 && gimbal_motor.GIMBAL->rc.ch[1] > -5){

                PID_calc(&pid_pitch_ground, INSTask.INS_angle[1],ins_angle_temp[1]);
                motor_gimbal_pitch = pid_pitch_ground.out;

            }
            //定向时可手动

            gimbal_motor_ecd_temp[0] = get_yaw_gimbal_motor_measure_point()->ecd;
            gimbal_motor_ecd_temp[1] = get_pitch_gimbal_motor_measure_point()->ecd;
            //暂存云台双轴角度数据

        }//云台对地定向

        if(gimbal_motor.GIMBAL->rc.s[0] == 2){

            if(gimbal_motor.GIMBAL->rc.ch[0] > 5 || gimbal_motor.GIMBAL->rc.ch[0] < -5){

                gimbal_motor_ecd_temp[2] = get_yaw_gimbal_motor_measure_point()->ecd;

                gimbal_motor_ecd_temp[0] = gimbal_motor_ecd_temp[2] - gimbal_motor.GIMBAL->rc.ch[0] * rm_mt_g;

                PID_calc(&pid_yaw_chassis, get_yaw_gimbal_motor_measure_point()->ecd,gimbal_motor_ecd_temp[2] - gimbal_motor.GIMBAL->rc.ch[0] * rm_mt_g);

            }//yaw

            if(gimbal_motor.GIMBAL->rc.ch[0] < 5 && gimbal_motor.GIMBAL->rc.ch[0] > -5){

                PID_calc(&pid_yaw_chassis, get_yaw_gimbal_motor_measure_point()->ecd,gimbal_motor_ecd_temp[0]);

            }

            if(gimbal_motor.GIMBAL->rc.ch[1] > 5 || gimbal_motor.GIMBAL->rc.ch[1] < -5){

                gimbal_motor_ecd_temp[3] = get_pitch_gimbal_motor_measure_point()->ecd;

                gimbal_motor_ecd_temp[1] = gimbal_motor_ecd_temp[3] - gimbal_motor.GIMBAL->rc.ch[1] * rm_mt_g;

                PID_calc(&pid_pitch_chassis, get_pitch_gimbal_motor_measure_point()->ecd,gimbal_motor_ecd_temp[3] - gimbal_motor.GIMBAL->rc.ch[1] * rm_mt_g);

            }//pitch

            if(gimbal_motor.GIMBAL->rc.ch[1] < 5 && gimbal_motor.GIMBAL->rc.ch[1] > -5){

                PID_calc(&pid_pitch_chassis, get_pitch_gimbal_motor_measure_point()->ecd,gimbal_motor_ecd_temp[1]);

            }
            //定向时可手动

            motor_gimbal_yaw = pid_yaw_chassis.out;
            motor_gimbal_pitch = pid_pitch_chassis.out;

            for (int angle_id = 0; angle_id < 3; ++angle_id) {
                ins_angle_temp[angle_id] = INSTask.INS_angle[angle_id];
            }//暂存imu角度数据

        }//云台对底盘定向

        if (gimbal_motor.GIMBAL->rc.s[1] == 1 || gimbal_motor.GIMBAL->rc.s[0] == 1) {

            motor_front_left = 0, motor_front_right = 0, motor_back_left = 0, motor_back_right = 0, motor_gimbal_pitch = 0, motor_gimbal_yaw = 0;

            for (int angle_id = 0; angle_id < 3; ++angle_id) {
                ins_angle_temp[angle_id] = INSTask.INS_angle[angle_id];
            }//暂存imu角度数据

            gimbal_motor_ecd_temp[0] = get_yaw_gimbal_motor_measure_point()->ecd;
            gimbal_motor_ecd_temp[1] = get_pitch_gimbal_motor_measure_point()->ecd;
            //暂存云台双轴角度数据

        }//无力急停

        //输出电机值：
        CAN_cmd_chassis(motor_front_right,motor_front_left,motor_back_left,motor_back_right);
        CAN_cmd_gimbal(0,motor_gimbal_pitch,0,0);
        CAN_cmd_cgimbal(motor_gimbal_yaw,0,0,0);

        osDelay(2);//防can噶等2

        //+-660->+-16384max
        //CAN_cmd_chassis(1000,motor_front_left,motor_back_left,motor_back_right); //+-660->+-16384max
        //+-660->+-16384max

    }

}