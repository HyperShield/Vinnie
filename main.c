#include "msp.h"
#include <stdint.h>
#include "Vinnie.h"
/*#include "Clock.h"*/
/*Functions*/
void SysTick_Handler(void);
void main(void);

/*Variables*/
typedef struct flag_struct{
    uint8_t systick;
}flag_st;
static flag_st flags;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		/*stop watchdog timer*/
	/*const uint32_t clk_freq =  48000000;*/
    const uint32_t clock_freq = 3000000u;
	/*Clock_Init48MHz();*/
	__delay_cycles(4*clock_freq);
	flags.systick = 0u;
	initialize_Vinnie(clock_freq);
	SysTick_Config(clock_freq/100u);
	for(;;){
	    if(flags.systick){
	        flags.systick = 0u;
	        update_Vinnie();
	    }
	    /*Sleep mode*/
	    __low_power_mode_0();
	}
}

void SysTick_Handler(void)
{
    flags.systick = 1u;
    /*wakeup*/
    __low_power_mode_off_on_exit();
}
