/*
 * spi_test_2.c
 *
 * Created: 20.03.2021 09:36:11
 * Author : SL20032
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t data = 0xAA;
uint8_t dataindeks = 0;

//Add your F_CPU to properties!!!

#define USART_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void spi0_pin_init(void)
{
	//initialize this before spi_init !!!
	PORTA.DIRSET = PIN7_bm;	//ss out
	PORTA.DIRSET = PIN6_bm;	//sck out
	PORTA.DIRSET = PIN4_bm;	//mosi out
	//miso in	
}

void spi_init(SPI_t * const spi)
{
	//data order MSb
	spi->CTRLA = SPI_PRESC_DIV16_gc;	//prescaller 16
	spi->CTRLA = 1 << SPI_MASTER_bp | 1 << SPI_ENABLE_bp;	//spi master mode | spi enabled	
	
	//dis enabled rx and tx buffer
}

void spi_send_byte(SPI_t * const spi, uint8_t data)
{
	spi->DATA = data;	//put data to spi
	while (!(spi->INTFLAGS & SPI_RXCIF_bm));	//wait to clear rx flag
}

void data_74hc595_send(uint8_t data)
{
	spi_send_byte(&SPI0,data);
	PORTA.OUTSET = PIN7_bm;		//create impulse to trigger shift register
	_delay_ms(10);
	PORTA.OUTCLR = PIN7_bm;	
}


void usart_init(USART_t * const usart, uint16_t boud_rate)
{
	usart->CTRLA = 1 << USART_RXCIE_bp;	 /* Receive Complete Interrupt Enable: enabled */ 
	
	
	usart->CTRLB = 1 << USART_RXEN_bp     /* Receiver Enable: enabled */
					| USART_RXMODE_NORMAL_gc /* Normal mode */
					| 1 << USART_TXEN_bp;    /* Transmitter Enable: enabled */
	
	usart->BAUD = (uint16_t)USART_BAUD_RATE(boud_rate);
}


void uart_sent_byte(USART_t * const usart, uint8_t data)
{
	while (!(usart->STATUS & USART_DREIF_bm));
	usart->TXDATAL = data;
}

void uart0_io_init(void)
{
	PORTA.DIRSET = PIN0_bm;	//txd out
	PORTA.DIRCLR = PIN1_bm;	//rxd in
}


ISR(USART0_RXC_vect)
{
	data = USART0.RXDATAL;	//read data from rx buffer
	
	if (dataindeks == 2)
	{
		data_74hc595_send(data);
		dataindeks = 0;
	}
	
	if(dataindeks == 1 && data == 0xAD) dataindeks++;
	else dataindeks = 0;
	
	
	if (dataindeks == 0 && data == 0xff) dataindeks++;
	 
}




int main(void)
{
    /* Replace with your application code */
	spi0_pin_init();	
	spi_init(&SPI0);
	uart0_io_init();
	usart_init(&USART0,9600);
	sei();
	
	data_74hc595_send(0x00);	
	
    while (1) 
    {

    }
}

