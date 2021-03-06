#include "qei.h"

void QEI_init(void){
    ADPCFGbits.PCFG3 = 1;
    ADPCFGbits.PCFG4 = 1;
    ADPCFGbits.PCFG5 = 1;
    
    QEICONbits.QEISIDL = 0;  
    QEICONbits.SWPAB = 0;
    QEICONbits.PCDOUT = 0;
    QEICONbits.TQCS = 1;
    POSCNT = 32767;
    MAXCNT = 0xffff;
    QEICONbits.QEIM = 0x07;
}

void get_encoder_data(int32_t *sum, int16_t *increment){
    increment_num = POSCNT - 32767;
    POSCNT = 32767;
    encoder_count_num += increment_num;
    *sum = encoder_count_num;
    *increment = increment_num;
}
