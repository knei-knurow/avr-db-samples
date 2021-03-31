/*
 * clk_ctrl.c
 *
 * Created: 31.03.2021 20:27:41
 *  Author: stani
 */ 

#include "clk_ctrl.h"
#include "ccp.h"
#include "protected_io.h"

void config_clk(void)
{
	ccp_write_io((void *)&(CLKCTRL.MCLKCTRLC),
	CLKCTRL_CFDSRC_XOSCHF_gc /* XOSCHF */
	| 1 << CLKCTRL_CFDEN_bp); /* Setting: enabled */


	ccp_write_io((void *)&(CLKCTRL.XOSCHFCTRLA),
	CLKCTRL_CSUTHF_4K_gc   /* 4K XOSCHF cycles */
	| CLKCTRL_FRQRANGE_8M_gc /* Max 8 MHz XTAL Frequency */
	| 1 << CLKCTRL_ENABLE_bp); /* External high-frequency Oscillator: enabled */

	ccp_write_io((void *)&(CLKCTRL.OSCHFCTRLA),
	CLKCTRL_FREQSEL_16M_gc);         /* 16 */
	
}

void change_clk_sorce_ext_clk(void)
{

	ccp_write_io((void *)&(CLKCTRL.MCLKCTRLA),
	CLKCTRL_CLKSEL_EXTCLK_gc); /* External clock */
	
	/* wait for system oscillator changing to finish */
	while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm);
	
	
}

void change_clk_sorce_int_osc(void)
{
	ccp_write_io((void *)&(CLKCTRL.MCLKCTRLA),
	CLKCTRL_CLKSEL_OSCHF_gc); /* External clock */
	
	/* wait for system oscillator changing to finish */
	while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm);	
	
}