#include "pid.h"

#define Kp 0.2
#define Ki 0.0
#define Kd 0.0

int get_pid_duty(uint16_t* return_duty, Drive_Mode_t* return_mode, uint16_t target_duty, Drive_Mode_t target_mode, uint32_t time_count, int16_t encoder_count){
    int now_val,target_val;
    int cal_duty;
    int now_diff=0;
    static int recent_diff = 0;
    double P_val,I_val = 0,D_val;
    double dt;
    
    if(target_mode == FREE_MODE || target_mode == BRAKE_MODE){
        *return_duty = 0;
        *return_mode = target_mode;
        return 0;
    }
    
    dt = 0.000125 * (double)time_count;
    target_val = (int)((double)MAX_PULSE_100MS * ((double)target_duty / (double)MAX_DUTY));
    if(target_mode == BACKWARD_MODE){
        target_val *= -1;
    }
    now_val = (int)(0.1 * (double)(encoder_count) / dt);
    now_diff = target_val - now_val;
    
    P_val = (double)now_diff;
    I_val += (((double)now_diff + (double)recent_diff) / 2.0) * dt;
    D_val = ((double)now_diff - (double)recent_diff) / dt;
    cal_duty = (int)(Kp * P_val + Ki * I_val + Kd * D_val);
    recent_diff = now_diff;
    
    *return_duty = abs(cal_duty);
    if(cal_duty >= 0){
        *return_mode = FORWARD_MODE;
    }else{
        *return_mode = BACKWARD_MODE;
    }
}