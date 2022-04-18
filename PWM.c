#include "msp.h"
#include <stdint.h>
#include "PWM.h"

uint16_t max_val;

void initialize_pwm(uint32_t clk_freq)
{
    max_val = 15000u;
    /*Configure 2.6 and 2.7 to be PWM outputs*/
    P2->SEL0 |= BIT6+BIT7;
    P2->SEL1 &= (uint16_t)(~(BIT6+BIT7));
    P2->DIR |= BIT6+BIT7;
    /*Configure TA0 to be PWM (UP/DOWN with TOGGLE)*/
    stop_pwm();
    TA0CCTL0 |= OUTMOD_4;
    TA0CCTL3 &= (uint16_t)(~CAP);
    TA0CCTL3 |= OUTMOD_2;
    TA0CCTL4 &= (uint16_t)(~CAP);
    TA0CCTL4 |= OUTMOD_2;
    TA0CCR0 = max_val;
    TA0CTL |= TASSEL__SMCLK+MC__UPDOWN;
    /*TA0CTL |= TASSEL__SMCLK+ID__4+MC__UPDOWN;
    TA0EX0 |= TAIDEX_2;*/
}
void start_pwm(void)
{
    TA0CTL |= TACLR;
}
void stop_pwm(void)
{
    TA0CTL &= (uint16_t)(~TACLR);
}
void set_left_pwm(float32_t val)
{
    float32_t temp = (val*max_val);
    TA0CCR4 = (uint16_t)temp;
}
void set_right_pwm(float32_t val)
{
    float32_t temp = (val*max_val);
    TA0CCR3 = (uint16_t)temp;
}
