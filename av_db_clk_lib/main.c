/*
 * av_db_clk_lib.c
 *
 * Created: 31.03.2021 20:24:40
 * Author : SL20032
 */

#include <avr/io.h>
#include "clklib/clk_ctrl.h"
#include <util/delay.h>
//#define F_CPU 4000000UL

void led_init(void)
{
	PORTA.DIRSET = PIN7_bm;
	PORTA.OUTSET = PIN7_bm;
}

int main(void)
{
    config_clk();
	change_clk_sorce_ext_clk();
	led_init();
    while (1) 
    {
		_delay_ms(1000);
		PORTA.OUTTGL = PIN7_bm;
    }
}

