#include "i2c.h"

uint8_t ReceiveBuffer[8] = {};
uint8_t SendBuffer[8] = {};
uint8_t *ReceiveTemp;
uint8_t *SendTemp;
bool receiveflag = false;

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

void __attribute__((interrupt,no_auto_psv)) _SI2CInterrupt(void){
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