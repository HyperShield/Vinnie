#include "msp.h"
#include "encoders.h"

/*interrupt routine for TA3CCR0*/
uint16_t right_period;
/*interrupt routine for TA3CCR1*/
uint16_t left_period;
void TA3_0_IRQHandler(void)
{
    TA3CCTL0 &= ~CCIFG;
    static uint16_t prev_ccr0=0u;
    right_period = (TA3CCR0-prev_ccr0);
    prev_ccr0 = TA3CCR0;
}
void TA3_N_IRQHandler(void)
{
    TA3CCTL1 &= ~CCIFG;
    static uint16_t prev_ccr1=0u;
    left_period = (TA3CCR1-prev_ccr1);
    prev_ccr1 = TA3CCR1;
}
void initialize_encoders(uint32_t clk_freq)
{
    /*Setup the ports/pins necessary*/
    P10->SEL0 |= BIT4+BIT5;
    P10->SEL1 &= ~(BIT4+BIT5);
    P10->DIR &= ~(BIT4+BIT5);
    /*Setup reading from the encoders (Timers?)*/
    TA3CCTL0 |= CM__RISING + SCS + CAP + CCIE + CCIS__CCIA;
    TA3CCTL1 |= CM__RISING + SCS + CAP + CCIE + CCIS__CCIA;
    TA3CTL |= TASSEL__SMCLK+MC__CONTINUOUS+TACLR;
    /*TA3CTL |= TASSEL__SMCLK+ID__4+MC__CONTINUOUS+TACLR;
    TA0EX0 |= TAIDEX_2;*/
    /*Setup global interrupts and peripheral interrupts*/
    __NVIC_EnableIRQ(TA3_0_IRQn);
    __NVIC_EnableIRQ(TA3_N_IRQn);
    /*Calculate the angular velocity of a wheel*/
    left_period = 0u;
    right_period = 0u;
}

float32_t calc_w_r(void)
{
    __NVIC_DisableIRQ(TA3_0_IRQn);
    uint16_t right_period_copy = right_period;
    __NVIC_EnableIRQ(TA3_0_IRQn);
    if(right_period_copy == 0u)
        return 0.0f;
    else
        return (float32_t)(52359.87755982989)/(float32_t)(right_period_copy);
}
float32_t calc_w_l(void)
{
    __NVIC_DisableIRQ(TA3_N_IRQn);
    uint16_t left_period_copy = left_period;
    __NVIC_EnableIRQ(TA3_N_IRQn);
    if(left_period_copy == 0u)
        return 0.0f;
    else
        return (float32_t)(52359.87755982989)/(float32_t)(left_period_copy);
}
