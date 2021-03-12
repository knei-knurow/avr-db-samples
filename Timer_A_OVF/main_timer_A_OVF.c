/*
 * AVR_DB_led_test.c
 *
 * Created: 11.03.2021 16:00:52
 * Author : SL20032
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void tca0_init(void)
{
	
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc     /* System Clock / 64 */
	                    | 1 << TCA_SINGLE_ENABLE_bp;    /* Module Enable: enabled */

	TCA0.SINGLE.INTCTRL = 1 << TCA_SINGLE_OVF_bp; /* Overflow Interrupt: enabled */
	
	//mode - normal default		
	
	
}

ISR(TCA0_OVF_vect)
{
	PORTA.OUTTGL = PIN6_bm;	//zmiana stanu pinu na przeciwny
	//element wymagany do poprawnego dzia³ana!!!!
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;	//zerownie flagi przerwania
}



int main(void)
{
    PORTA.DIRSET = PIN6_bm;	//usatwienie na wyjœcie
	PORTA.OUTSET = PIN6_bm;	//stan wysoki
	tca0_init();
	sei();	//myÅ›lÄ™ Å¼e wiadomo co to robi xD
    while (1) 
    {
		
    }
}

