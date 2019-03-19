/*
 * application.c
 *
 * Created: 2019-03-15 오후 3:39:30
 *  Author: Jae
 */ 
#include "common.h"

#define FORWARD_OP

uint8_t ex_cnt = 0, count = 0;
uint8_t pos[2] = {0, 0};
uint8_t before_pos[2] = {0, 0};


void ApplicationMain(void)
{
	PORTB |= (1 << PORTB5);
	
	if(tick == 1)									// 인터럽트 동작하면
	{
		tick = 0;									// 인터럽트 tick 초기화

		#ifdef FORWARD_OP
		//USART_Transmit_str("FORWARD MODE\n", _ASCII);
		if(pin2_flg == 1 && pin4_flg == 0)			// 최초 동작 방향 체크
		{
			state = FORWARD;
		}
		
		if(state == FORWARD)
		{
			pos[0] = pin2_forward_flg;
			pos[1] = pin4_forward_flg;
			
			if(before_pos[0] == pos[0])
			{
				uint8_t check = 0;
				ex_cnt++;
				check = ex_cnt%2;
				if(check == 0)
				{
					ex_cnt = 0;
					count++;
					USART_Transmit_char(0xEA);
					USART_Transmit_char(count);
					USART_Transmit_char(0x33);
					USART_Transmit_char(0x5A);
// 					USART_Transmit_str("\n------- cnt = ", _ASCII);
// 					translateChartoASCII(count);
// 					USART_Transmit_str(" -----------\n", _ASCII);
				}
				
				if(before_pos[1] == pos[1])
				{
					pin2_flg = 0;
					pin4_flg = 0;
				}
			}

			before_pos[0] = pos[0];
			before_pos[1] = pos[1];
		}
		
		#else
		//USART_Transmit_str("REVERSE MODE\n", _ASCII);
		if(pin2_flg == 0 && pin4_flg == 1)			// 최초 동작 방향 체크
		{
			state = REVERSE;
		}

		if(state == REVERSE)
		{
			pos[0] = pin2_reverse_flg;
			pos[1] = pin4_reverse_flg;
	
			if(before_pos[0] == pos[0])
			{
				uint8_t check = 0;
				ex_cnt++;
				check = ex_cnt%2;
				if(check == 0)
				{
					ex_cnt = 0;
					count++;
					USART_Transmit_char(0xEA);
					USART_Transmit_char(count);
					USART_Transmit_char(0x33);
					USART_Transmit_char(0x5A);
// 					USART_Transmit_str("\n------- cnt = ", _ASCII);
// 					translateChartoASCII(count);
// 					USART_Transmit_str(" -----------\n", _ASCII);
				}
		
				if(before_pos[1] == pos[1])
				{
					pin2_flg = 0;
					pin4_flg = 0;
				}
			}

			before_pos[0] = pos[0];
			before_pos[1] = pos[1];
		}		
		
		#endif
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