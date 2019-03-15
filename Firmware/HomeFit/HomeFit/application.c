/*
 * application.c
 *
 * Created: 2019-03-15 오후 3:39:30
 *  Author: Jae
 */ 
#include "common.h"

ISR(PCINT0_vect)
{
	
}

void ApplicationMain(void)
{
	if(rx_flag == 1)
	{
		rx_flag = 0;
		USART_Transmit_str(str, _ASCII);
	}
}

void AppInit(void)
{
	USART_Init(BAUD_9600);
	sei();
}