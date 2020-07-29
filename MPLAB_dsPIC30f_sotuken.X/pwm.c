#include "pwm.h"

void PWM_init(void){
    TRISC = 0;
    LED1 = 0;
    LED2 = 0;
    TRISE = 0x0000;
    LATE = 0x0000;
    PTPER = 999; //29.48kHz
    SEVTCMP = 0;
    DTCON1bits.DTAPS = 0;
    DTCON1bits.DTA = 50;
    PWMCON1bits.PTMOD1 = 0;
    PWMCON1bits.PTMOD2 = 0;
    PWMCON1bits.PTMOD3 = 1;
    PWMCON1bits.PEN1H = 1;
    PWMCON1bits.PEN1L = 1;
    PWMCON1bits.PEN2H = 1;
    PWMCON1bits.PEN2L = 1;
    PWMCON1bits.PEN3H = 0;
    PWMCON1bits.PEN3L = 0;
    PWMCON2bits.OSYNC = 0;
    PWMCON2bits.UDIS = 0;
    PWMCON2bits.SEVOPS = 0;
    PDC1 = 0;
    PDC2 = 0;
    PTCONbits.PTSIDL = 0;
    PTCONbits.PTOPS = 0;
    PTCONbits.PTCKPS = 0;
    PTCONbits.PTMOD = 0;
    OVDCON = 0x0000;
    PTCONbits.PTEN = 1;
}

void set_pwm(uint16_t duty, Drive_Mode_t mode){
    if(duty > MAX_DUTY){
        duty = MAX_DUTY;
    }
    
    switch(mode){
    case FREE_MODE:
        PDC1 = 0;
        PDC2 = 0;
        pwm_output_reset();
        LED1 = 0;
        LED2 = 0;
        break;
        
    case FORWARD_MODE:
        pwm_output_reset();
        LED1 = 1;
        LED2 = 0;
        PDC1 = (unsigned int)((double)PTPER * (((double)duty*2.0)/1024.0));
        PDC2 = (unsigned int)((double)PTPER * (((double)duty*2.0)/1024.0));
        OVDCONbits.POVD1H = 1;
        OVDCONbits.POVD1L = 0;
        OVDCONbits.POVD2H = 0;
        OVDCONbits.POVD2L = 0;
        OVDCONbits.POUT1H = 0;
        OVDCONbits.POUT1L = 0;
        OVDCONbits.POUT2H = 0;
        OVDCONbits.POUT2L = 1;
        break;
        
    case BACKWARD_MODE:
        pwm_output_reset();
        LED1 = 0;
        LED2 = 1;
        PDC1 = (unsigned int)((double)PTPER * (((double)duty*2.0)/1024.0));
        PDC2 = (unsigned int)((double)PTPER * (((double)duty*2.0)/1024.0));
        OVDCONbits.POVD1H = 0;
        OVDCONbits.POVD1L = 0;
        OVDCONbits.POVD2H = 1;
        OVDCONbits.POVD2L = 0;
        OVDCONbits.POUT1H = 0;
        OVDCONbits.POUT1L = 1;
        OVDCONbits.POUT2H = 0;
        OVDCONbits.POUT2L = 0;    
        break;
         
    case BRAKE_MODE:
        pwm_output_reset();
        LED1 = 1;
        LED2 = 1;
        PDC1 = 0;
        PDC2 = 0;
        OVDCONbits.POVD1H = 0;
        OVDCONbits.POVD1L = 0;
        OVDCONbits.POVD2H = 0;
        OVDCONbits.POVD2L = 0;
        OVDCONbits.POUT1H = 0;
        OVDCONbits.POUT1L = 1;
        OVDCONbits.POUT2H = 0;
        OVDCONbits.POUT2L = 1;    
        break;
    }
}

void pwm_output_reset(void){
    OVDCONbits.POVD1H = 0;
    OVDCONbits.POVD1L = 0;
    OVDCONbits.POVD2H = 0;
    OVDCONbits.POVD2L = 0;
    OVDCONbits.POUT1H = 0;
    OVDCONbits.POUT1L = 0;
    OVDCONbits.POUT2H = 0;    
    OVDCONbits.POUT2L = 0;  
}
