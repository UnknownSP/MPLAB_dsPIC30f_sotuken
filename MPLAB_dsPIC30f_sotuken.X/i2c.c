#include "i2c.h"

uint8_t ReceiveBuffer[RECEIVE_DATA_BYTE] = {};
uint8_t SendBuffer[SEND_DATA_BYTE+1] = {};
uint8_t *ReceiveTemp;
bool receiveflag = false;
int send_count = 0;
static uint8_t add = 0;

void I2C_init(uint8_t address){
    I2CCON = 0x0000;
    I2CCON = 0x9040;
    I2CSTAT = 0x0000;
    I2CADD = address;
    //I2CBRG = 145;
    add = address;
    
    IFS0 = 0;
    ReceiveTemp = &ReceiveBuffer[0];
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
    
    if(_SI2CIF == 1){
        if((I2CSTATbits.R_W == 0)&&(I2CSTATbits.D_A == 0)){	//Address matched
            Temp = I2CRCV;		
            ReceiveTemp = &ReceiveBuffer[0];	//reset the Buffer pointer
            I2CCONbits.SCLREL = 1;
            receiveflag = false;
            _SI2CIF = 0;
        }else if((I2CSTATbits.R_W == 0)&&(I2CSTATbits.D_A == 1)){ //check for data
            receiveflag = true;
            *ReceiveTemp = (uint8_t)I2CRCV;// store data into Buffer
            ReceiveTemp++;
            _SI2CIF = 0;
            I2CCONbits.SCLREL = 1;
        }/*else if((I2CSTATbits.R_W == 1)&&(I2CSTATbits.D_A == 0)){
            if(I2CSTATbits.TBF == 1){
                I2CTRN = SendBuffer[send_count];
                I2CCONbits.SCLREL = 1;
                while((I2CSTATbits.TBF));
                send_count++;
                if(send_count == SEND_DATA_BYTE + 1){
                    send_count = 0;
                    I2C_init(add);
                }
            }else{
                if(I2CSTATbits.ACKSTAT == 0){
                    I2CTRN = SendBuffer[send_count];
                    I2CCONbits.SCLREL = 1;
                    while((I2CSTATbits.TBF));
                    send_count++;
                    if(send_count == SEND_DATA_BYTE + 1){
                        send_count = 0;
                        I2C_init(add);
                    }
                }
            }
        }*/
    }
    I2CSTAT = 0x0000;
    
    //_SI2CIF = 0;
}