
#include "Includes.h"



// RB0/INT pin is used for capturing external edge triggered interrupts



void InitExternal_INT(void)
{
	TRISB0 = 1;                 // Make RB0 pin as input

	INTCON     |= 0x90;         // Enable Global + INT interrupt
	OPTION_REG |= 0x40;         // Make INT as posedge triggered
}