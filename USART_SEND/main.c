/*
 * Uart_AVR128DB28.c
 *
 * Created: 12.03.2021 16:16:34
 * Author : SL20032
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define USART_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

char data = 0;

void usart_init(USART_t * const usart, uint16_t boud_rate)
{
	usart->CTRLB = 1 << USART_RXEN_bp     /* Receiver Enable: enabled */
				| USART_RXMODE_NORMAL_gc /* Normal mode */
				| 1 << USART_TXEN_bp;    /* Transmitter Enable: enabled */
	
	usart->BAUD = (uint16_t)USART_BAUD_RATE(boud_rate);	
}


void sent_byte(USART_t * const usart, uint8_t data)
{
	while (!(usart->STATUS & USART_DREIF_bm));
	usart->TXDATAL = data;	
}

void tca0_init(void)
{
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc     /* System Clock / 64 */
	| 1 << TCA_SINGLE_ENABLE_bp;    /* Module Enable: enabled */
	TCA0.SINGLE.INTCTRL = 1 << TCA_SINGLE_OVF_bp; /* Overflow Interrupt: enabled */
	//mode - normal default	
}

ISR(TCA0_OVF_vect)
{
	//PORTA.OUTTGL = PIN6_bm;	//zmiana stanu pinu na przeciwny
	sent_byte(&USART0,0xff);
	sent_byte(&USART0,0xfe);
	sent_byte(&USART0,0xfd);	
	//element wymagany do poprawnego dzia?ana!!!!
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;	//zerownie flagi przerwania
}


int main(void)
{
	PORTA.DIRSET = PIN6_bm;
	PORTA.OUTSET = PIN6_bm;
	PORTA.DIRSET = PIN1_bm;
	PORTA.DIRSET = PIN0_bm;
	
	usart_init(&USART0,9600);
	tca0_init();
	sei();
	
	
    while (1) 
    {		

    }
}

