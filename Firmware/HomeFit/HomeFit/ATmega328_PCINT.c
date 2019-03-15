/*
 * ATmega328_PCINT.c
 *
 * Created: 2019-03-15 오후 5:42:55
 *  Author: Jae
 */ 

#include "ATmega328_PCINT.h"



void PCINT_init(void)
{
	PCIFR = (1 << PCIF0);
	
	
}