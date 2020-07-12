/* 
 * File:   main.c
 * Author: UnknownSP
 *
 * Created on July 12, 2020, 4:40 PM
 */

#define FCY 14740000

#include "main.h"
#include <xc.h>

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

void __attribute__((interrupt,no_auto_psv)) _SI2CInterrupt(void){
    Slave_Interrupt();
}

void I2C_init(void){
    I2CCON = 0x8000;
    I2CADD = 0x50;
    
    IFS0 = 0;
    ReceiveTemp = &ReceiveBuffer[0];
    SendTemp = &SendBuffer[0];
    _SI2CIE = 1;
}

bool I2C_ReceiveCheck(void){
    if(receiveflag){
        if((I2CSTATbits.S == 0)&&(I2CSTATbits.P == 1)){
            receiveflag = false;
            return true;
        }
    }
    return false;
}

void Slave_Interrupt(void){
    unsigned char Temp;
    
    if((I2CSTATbits.R_W == 0)&&(I2CSTATbits.D_A == 0)){	//Address matched
		Temp = I2CRCV;		
		ReceiveTemp = &ReceiveBuffer[0];	//reset the Buffer pointer
        receiveflag = false;
	}else if((I2CSTATbits.R_W == 0)&&(I2CSTATbits.D_A == 1)){ //check for data
        receiveflag = true;
        *ReceiveTemp = (uint8_t)I2CRCV;// store data into Buffer
        ReceiveTemp++;
    }else if((I2CSTATbits.R_W == 1)&&(I2CSTATbits.D_A == 0)){
		Temp = I2CRCV;
		I2CTRN = *SendTemp;	//Read data from Buffer & send data to master
		while(I2CSTATbits.TBF); 
		SendTemp = &SendBuffer[0];	//reset the Buffer pointer
	}
    _SI2CIF = 0;
    I2CCONbits.SCLREL = 1; //SCL‚Ì‰ð•ú
}