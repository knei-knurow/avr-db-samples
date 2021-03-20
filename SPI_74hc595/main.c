/*
 * spi_test_2.c
 *
 * Created: 20.03.2021 09:36:11
 * Author : SL20032
 */ 

#include <avr/io.h>
#include <util/delay.h>

//Add your F_CPU to properties!!!

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



int main(void)
{
    /* Replace with your application code */
	spi0_pin_init();	
	spi_init(&SPI0);
	
    while (1) 
    {
		data_74hc595_send(0xAA);
		_delay_ms(1000);	//i know delays are bad
		data_74hc595_send(0x55);
		_delay_ms(1000);	
    }
}

