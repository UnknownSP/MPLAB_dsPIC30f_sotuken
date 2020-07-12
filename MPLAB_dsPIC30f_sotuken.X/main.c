/* 
 * File:   main.c
 * Author: UnknownSP
 *
 * Created on July 12, 2020, 4:40 PM
 */

#define FCY 14740000

#include "main.h"
#include "i2c.h"

_FOSC(CSW_FSCM_OFF & FRC_PLL8); 
_FWDT(WDT_OFF);
_FBORPOR(PBOR_ON & BORV20 & PWRT_64 & MCLR_EN); 
_FGS(CODE_PROT_OFF);

int main(void){
    
    I2C_init();
    
    TRISC=0;
    LATCbits.LATC14=1;
    while(1){
        /*LATCbits.LATC13=1;
        __delay_ms(1000);
        LATCbits.LATC13=0;
        __delay_ms(1000);*/
        if(I2C_ReceiveCheck()){
            if((ReceiveBuffer[0] == 0x11) && (ReceiveBuffer[1] == 0x32)){
                LATCbits.LATC14 ^= 1;
            }
        }
    }
    
    return 0;
}

