#include "timer.h"

void TIMER1_init(void){
    T1CONbits.TCKPS = 0x00;
    T1CONbits.TCS = 0;
    _T1IE = 1;
    _T1IF = 0;
    TMR1 = 61851;//65536-7370/2
    T1CONbits.TON = 0;
}

void TIMER1_START(void){
    T1CONbits.TON = 1;
}

void TIMER1_STOP(void){
    T1CONbits.TON = 0;
    TIMER1_init();
}

uint32_t get_interval_time(void){
    uint32_t return_count;
    return_count = timer_clock_count;
    timer_clock_count = 0;
    return return_count;
}

void __attribute__((interrupt,no_auto_psv)) _T1Interrupt(void){
    if(_T1IF == 1){
        timer_clock_count++;
        TMR1 = 61851; //65536-7370/2 0.000125s
        _T1IF = 0;
    }
}
