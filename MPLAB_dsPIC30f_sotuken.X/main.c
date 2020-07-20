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

_FOSC(CSW_FSCM_OFF & FRC_PLL16); 
_FWDT(WDT_OFF);
_FBORPOR(PBOR_ON & BORV20 & PWRT_64 & MCLR_EN); 
_FGS(CODE_PROT_OFF);

int main(void){
    
    int32_t encoder_count;
    int16_t encoder_increment;
    uint32_t time_count = 0;
    
    init();
    
    uint16_t duty = 0;
    uint8_t mode = 0;
    
    TIMER1_START();
    while(1){
        /*LATCbits.LATC13=1;
        __delay_ms(1000);
        LATCbits.LATC13=0;
        __delay_ms(1000);*/
        /*if((I2CSTATbits.S == 0)){
            LATCbits.LATC13=1;
        }else{
            LATCbits.LATC13=0;
        }
        if((I2CSTATbits.P == 0)){
            LATCbits.LATC14=1;
        }else{
            LATCbits.LATC14=0;
        }*/
        if(I2C_ReceiveCheck()){
            if((ReceiveBuffer[0] == 0x11) && (ReceiveBuffer[1] == 0x32)){
                LATCbits.LATC14 = 0; //green
                LATCbits.LATC13 = 1; //blue
            }else{
                LATCbits.LATC14 = 1;
                LATCbits.LATC13 = 0;
            }
            duty = (ReceiveBuffer[0] & 0x03) << 8;
            duty |= ReceiveBuffer[1];
            mode = (ReceiveBuffer[0] >> 2) & 0x03;
            set_pwm(duty, mode);
            get_encoder_data(&encoder_count,&encoder_increment);
            time_count = get_interval_time();
            SendBuffer[2] = (uint8_t)(time_count);
            SendBuffer[3] = (uint8_t)((time_count)>>8);
            SendBuffer[0] = (int8_t)encoder_count;
            SendBuffer[1] = (int8_t)(encoder_count >> 8);
            SendBuffer[4] = (int8_t)encoder_increment;
            SendBuffer[5] = (int8_t)(encoder_increment >> 8);
        }
    }
    
    return 0;
}


void init(void){
    int i;
    
    I2C_init();
    QEI_init();
    TIMER1_init();
    PWM_init();
    
    TRISC=0;
    
    for(i=0;i<SEND_DATA_BYTE;i++){
        SendBuffer[i] = i+1; 
    }
}