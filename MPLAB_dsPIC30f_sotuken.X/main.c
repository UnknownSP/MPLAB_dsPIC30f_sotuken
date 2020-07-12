/* 
 * File:   main.c
 * Author: UnknownSP
 *
 * Created on July 12, 2020, 4:40 PM
 */

#define FCY 14740000

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "p30f4012.h"
#include <libpic30.h>
#include <stdlib.h>

_FOSC(CSW_FSCM_OFF & FRC_PLL8); 
_FWDT(WDT_OFF);
_FBORPOR(PBOR_ON & BORV20 & PWRT_64 & MCLR_EN); 
_FGS(CODE_PROT_OFF);

void __attribute__((interrupt,no_auto_psv)) _SI2CInterrupt(void);
void I2C_init(void);
bool I2C_ReceiveCheck(void);
uint8_t ReadBuffer[256] = {};
uint8_t *ReadPtr;
bool readflag = false;

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
            if((ReadBuffer[0] == 0x11) && (ReadBuffer[1] == 0x22)){
                LATCbits.LATC14=0;
            }
        }
    }
    
    return 0;
}

void I2C_init(void){
    I2CCON = 0x8000;
    I2CADD = 0x50;
    
    IFS0 = 0;
    ReadPtr = &ReadBuffer[0];
    _SI2CIE = 1;
}

void __attribute__((interrupt,no_auto_psv)) _SI2CInterrupt(void){
    unsigned char Temp;
    
    if((I2CSTATbits.R_W == 0)&&(I2CSTATbits.D_A == 0)){	//Address matched
		Temp = I2CRCV;		//dummy read
		ReadPtr = &ReadBuffer[0];	//reset the RAM pointer
        readflag = false;
	}else if((I2CSTATbits.R_W == 0)&&(I2CSTATbits.D_A == 1)){ //check for data
        readflag = true;
        *ReadPtr = (uint8_t)I2CRCV;// store data into RAM
        ReadPtr++;
    }else if((I2CSTATbits.R_W == 1)&&(I2CSTATbits.D_A == 0)){
		Temp = I2CRCV;
		I2CTRN = *ReadPtr;	//Read data from RAM & send data to I2C master device
		I2CCONbits.SCLREL = 1;	//Release SCL1 line
		while(I2CSTATbits.TBF);//Wait till all 
		ReadPtr = &ReadBuffer[0];	//reset the RAM pointer
	}
    _SI2CIF = 0;
    I2CCONbits.SCLREL = 1;
}

bool I2C_ReceiveCheck(void){
    if(readflag){
        if((I2CSTATbits.S == 0)&&(I2CSTATbits.P == 1)){
            readflag = false;
            return true;
        }
    }
    return false;
}

