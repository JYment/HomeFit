/*
 * application.c
 *
 * Created: 2019-03-15 오후 3:39:30
 *  Author: Jae
 */ 
#include "common.h"

uint8_t forward_state = 0, reverse_state = 0;
uint8_t pin2_cnt = 0, pin4_cnt = 0;
uint8_t ex_cnt = 0;

void ApplicationMain(void)
{
	PORTB |= (1 << PORTB5);
	
	if(pin2_flg == 1 && pin4_flg == 0)
	{
		state = FORWARD;
	}
	else if(pin2_flg == 0 && pin4_flg == 1)
	{
		state = REVERSE;
	}
	
	if(state == FORWARD)
	{
		if(pin2_forward_flg == 1)
		{
			pin2_forward_flg = 0;
			pin2_cnt++;
			if(pin2_cnt > 5)
			{
// 				uint8_t str[10] = "FORWARD\n";
// 				USART_Transmit_str(str, _ASCII);
				forward_state = 1;
				pin2_flg = 0;
			}
		}
	}
	else if(state == REVERSE)
	{
		if(pin4_reverse_flg == 1)
		{
			pin4_reverse_flg = 0;
			pin4_cnt++;
			if(pin4_cnt > 5)
			{
// 				uint8_t str[10] = "REVERSE\n";
// 				USART_Transmit_str(str, _ASCII);
				reverse_state = 1;
				pin4_flg = 0;
			}
		}
	}
	
	if(forward_state == 1 && reverse_state == 1)
	{
		ex_cnt++;
// 		uint8_t str[10] = "cnt = ";
// 		USART_Transmit_str(str, _ASCII);
// 		translateChartoASCII(ex_cnt);
//		USART_Transmit_char('\n');
		
// 		USART_Transmit_char(0xEA);
// 		USART_Transmit_char(ex_cnt);
// 		USART_Transmit_char(0x00);
// 		USART_Transmit_char(0x5A);
		forward_state = 0;
		reverse_state = 0;
		pin2_cnt = 0;
		pin4_cnt = 0;
	}
}

void AppInit(void)
{
	USART_Init(BAUD_9600);			// USART 9600 baudrate 설정
	PCINT_init();
	DDRB = (1 << PORTB5);			// 확인용 LED
	sei();
	USART_Transmit_str("START\n", _ASCII);
}