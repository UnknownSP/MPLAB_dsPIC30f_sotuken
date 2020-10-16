#include "pid.h"
#include "i2c.h"

#define Kp 0.084//0.063//0.084 //0.6*0.2
#define Ki 0.87264//0.2796//0.87264 //Ti=0.5*0.33ms 0.7272*1.1
#define Kd 0.00278//0.003//0.00278//0.00594 //0.00495*1.2

/*
 kp = 0.6 * ku
 ki = kp/(0.5*pu)
 kd = kp*0.125*pu
 
 kp = 0.45 * ku
 ki = kp/(0.85*pu)
 
 ku = 0.2
 pu = 0.33
 
 ku = 0.14
 pu = 0.265
 
 */

int get_pid_duty(int16_t* operate_target, int16_t* operate_nowval, uint16_t* return_duty, Drive_Mode_t* return_mode, uint16_t target_duty, Drive_Mode_t target_mode, uint32_t time_count, int16_t encoder_count){
    int16_t now_val,target_val;
    static int16_t cal_duty = 0;
    int16_t now_diff=0;
    static int16_t recent_diff = 0;
    double P_val,I_val = 0.0,D_val;
    double dt;
    static int16_t recent_duty;
    static Drive_Mode_t recent_mode = 0;
    
    if(target_mode == FREE_MODE || target_mode == BRAKE_MODE){
        *return_duty = 0;
        *return_mode = target_mode;
        cal_duty = 0;
        recent_duty = 0;
        *operate_target = 0;
        *operate_nowval = 0;
        I_val = 0.0;
        return 0;
    }
    
    if(recent_mode != target_mode){
        //I_val = 0.0;
    }
    recent_mode = target_mode;
    
    dt = 0.000125 * (double)time_count;
    target_val = (int16_t)((double)MAX_PULSE_100MS * ((double)target_duty / (double)MAX_DUTY));
    if(target_mode == BACKWARD_MODE){
        target_val *= -1;
        //cal_duty = -1 * target_duty;
    }else{
        //cal_duty = target_duty;
    }
    now_val = (int16_t)(0.1 * (double)(abs(encoder_count)) / dt);
    if(encoder_count < 0){
        now_val *= -1;
    }
    now_diff = target_val - now_val;
    *operate_target = target_val;
    *operate_nowval = now_val;
    
    double now_diff_add = 0.0;
    
    //if(abs(now_diff) > 100){
    P_val = (double)now_diff;
    I_val += (((double)now_diff + (double)recent_diff) / 2.0) * dt;
    D_val = ((double)now_diff - (double)recent_diff) / dt;
    //cal_duty += (int)(Kp * P_val + Ki * I_val + Kd * D_val);
    if(target_mode == BACKWARD_MODE){
        cal_duty = (int)(-(double)target_duty*0.9) - 38 + (int)(Kp * P_val + Ki * I_val + Kd * D_val);
    }else{
        cal_duty = (int)((double)target_duty*0.9) + 38 + (int)(Kp * P_val + Ki * I_val + Kd * D_val);
    }
    recent_duty = cal_duty;
    now_diff_add = 0.0;
    /*}else{
        now_diff_add += now_diff * 0.02;
        cal_duty = target_duty + (int)now_diff_add;
    }*/
    if(abs(cal_duty) > MAX_DUTY){
        if(cal_duty >= 0){
            cal_duty = MAX_DUTY;
        }else{
            cal_duty = -MAX_DUTY;
        }
    }
    recent_diff = now_diff;
    
    /*if(cal_duty < 0){
        cal_duty = 0;
    }*/
    *return_duty = abs(cal_duty);
    if(cal_duty >= 0){
        *return_mode = FORWARD_MODE;
    }else{
        *return_mode = BACKWARD_MODE;
    }
    
    return 0;
}

int get_pid_duty_2(int16_t* operate_target, int16_t* operate_nowval, uint16_t* return_duty, Drive_Mode_t* return_mode, uint16_t target_duty, Drive_Mode_t target_mode, uint32_t time_count, int16_t encoder_count){
    int now_val,target_val;
    static int cal_duty = 0;
    int now_diff=0;
    static int recent_diff = 0;
    double P_val,I_val = 0.0,D_val;
    double dt;
    
    if(target_mode == FREE_MODE || target_mode == BRAKE_MODE){
        *return_duty = 0;
        *return_mode = target_mode;
        cal_duty = 0;
        //I_val = 0.0;
        return 0;
    }
    
    dt = 0.000125 * (double)time_count;
    target_val = (int)((double)MAX_PULSE_100MS * ((double)target_duty / (double)MAX_DUTY));
    if(target_mode == BACKWARD_MODE){
        target_val *= -1;
        //cal_duty = -1 * target_duty;
    }else{
        //cal_duty = target_duty;
    }
    now_val = (int)(0.1 * (double)(encoder_count) / dt);
    now_diff = target_val - now_val;
    *operate_target = target_val;
    *operate_nowval = now_val;
    /*
    double kp = 0.054;
    double ki = 5.087264;
    double kd = 0.0000278;
    */
    
    /*P_val = (double)now_diff;
    I_val += (((double)now_diff + (double)recent_diff) / 2.0) * dt;
    D_val = ((double)now_val) / dt;
    cal_duty = target_duty + (int)(kp * P_val + ki * I_val - kd * D_val);
    */
    //cal_duty = target_duty + now_diff*0.05;
    
    cal_duty = target_duty;
    
    if(abs(cal_duty) > MAX_DUTY){
        if(cal_duty >= 0){
            cal_duty = MAX_DUTY;
        }else{
            cal_duty = -1 * MAX_DUTY;
        }
    }
    //recent_diff = now_diff;
    
    /*if(cal_duty < 0){
        cal_duty = 0;
    }*/
    *return_duty = abs(cal_duty);
    *return_mode = target_mode;
    
    return 0;
}