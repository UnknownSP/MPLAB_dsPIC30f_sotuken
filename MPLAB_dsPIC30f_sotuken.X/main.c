/* 
 * File:   main.c
 * Author: UnknownSP
 *
 * Created on July 12, 2020, 4:40 PM
 */

#define FCY 14744000  //7.3728MHz ... ?

#include "main.h"
#include "i2c.h"
#include "qei.h"
#include "timer.h"
#include "pwm.h"
#include "pid.h"
#include <stdbool.h>

_FOSC(CSW_FSCM_OFF & FRC_PLL16); 
_FWDT(WDT_OFF);
_FBORPOR(PBOR_ON & BORV20 & PWRT_64 & MCLR_EN); 
_FGS(CODE_PROT_OFF);

int main(void){
    
    int32_t encoder_count;
    int16_t encoder_increment;
    uint32_t time_count = 0;
    uint16_t duty = 0,target_duty = 0;
    Drive_Mode_t mode = 0,target_mode = 0;
    int16_t operate_target=0,operate_nowval=0;
    int count;
    unsigned int system_time=0;
    bool start_flag = false;
    double random;
    
    init();
    
    TIMER1_START();
    while(1){
        if(I2C_ReceiveCheck()){
            target_duty = ((uint8_t)(ReceiveBuffer[0]) & 0x03) << 8;
            target_duty |= (uint8_t)(ReceiveBuffer[1]);
            if(target_duty > 990){
                target_duty = 990;
            }
            target_mode = (ReceiveBuffer[0] >> 2) & 0x03;
            get_encoder_data(&encoder_count,&encoder_increment);
            time_count = get_interval_time();
            
            /*if((uint8_t)(ReceiveBuffer[1]) != 0){
                system_time += time_count;
                start_flag = true;
            }else if((uint8_t)(ReceiveBuffer[1]) == 0){
                srand(3);
                system_time = 0;
                start_flag = false;
                target_mode = 0;
                target_duty = 0;
            }
            if(system_time >= 16000){
                random = (double)rand()/(double)(RAND_MAX);
                target_duty = (unsigned int)(990.0 * random);
                if(target_duty%2 == 0){
                    target_mode = 2;
                }else{
                    target_mode = 1;
                }  
                system_time = 0;
            }*/
            
            get_pid_duty(&operate_target,&operate_nowval,&duty,&mode,target_duty,target_mode,time_count,encoder_increment);
            set_pwm(duty, mode);
            //SendBuffer[2] = (uint8_t)(mode);
            //SendBuffer[3] = (uint8_t)(time_count);
            //SendBuffer[0] = (int8_t)duty;
            //SendBuffer[1] = (int8_t)(duty >> 8);
            //SendBuffer[4] = (int8_t)encoder_increment;
            //SendBuffer[5] = (int8_t)(encoder_increment >> 8);
            //SendBuffer[0] = (int8_t)operate_target;
            //SendBuffer[1] = (int8_t)(operate_target >> 8);
            //SendBuffer[4] = (int8_t)operate_nowval;
            //SendBuffer[5] = (int8_t)(operate_nowval >> 8);
        }
    }
    
    return 0;
}


void init(void){
    int i;
    uint8_t address;
    
    ADPCFG = 0xffff;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    
    address = 0x10;
    address |= (ADD_INPUT_1 << 0);
    address |= (ADD_INPUT_2 << 1);
    address |= (ADD_INPUT_3 << 2);
    address |= (ADD_INPUT_4 << 3);
    
    I2C_init(address);
    QEI_init();
    TIMER1_init();
    PWM_init();
    
    for(i=0;i<SEND_DATA_BYTE;i++){
        SendBuffer[i] = i+1; 
    }
}