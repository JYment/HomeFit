/*
 * ATmega328_PCINT.c
 *
 * Created: 2019-03-15 오후 5:42:55
 *  Author: Jae
 */ 

#include "ATmega328_PCINT.h"

volatile uint8_t pin0_flg = 0, pin2_flg = 0, pin4_flg = 0, pin8_flg = 0;
volatile uint8_t pin2_forward_flg = 0, pin4_reverse_flg = 0;
uint8_t state = 0;

void PCINT_init(void)
{
	DDRB &= ~((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3));
	PCICR = (1 << PCIE0);
	PCMSK0 = (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3);
}

ISR(PCINT0_vect)
{
	uint8_t input_check = PINB & 0x0F;
	switch(input_check)
	{
		case 0x01:
			break;
		case 0x02:
			if(state == FORWARD)
			{
				pin2_forward_flg = 1;
			}
			else
			{
				pin2_flg = 1;
			}
			USART_Transmit_str("2", _ASCII);
			break;
		case 0x04:
			if(state == REVERSE)
			{
				pin4_reverse_flg = 1;
			}
			else
			{
				pin4_flg = 1;
			}
			USART_Transmit_str("4", _ASCII);
			break;		
		case 0x08:
			pin8_flg = 1;
			break;		
	}
}