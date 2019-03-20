/*
 * application.c
 *
 * Created: 2019-03-15 오후 3:39:30
 *  Author: Jae
 */ 
#include "common.h"

uint8_t flag = 0;
uint8_t ex_cnt = 0, count = 0;
uint8_t pos[4] = {0, 0, 0, 0};
uint8_t before_pos[4] = {0, 0, 0, 0};
uint8_t before_dir = 0;

void ApplicationMain(void)
{
	if(rx_flag == _SET)
	{
		rx_flag = _RESET;
		if(str[0] == PT_HEADER && str[2] == PT_TAIL)
		{
			if(str[1] == PT_RESET)
			{
/*				USART_Transmit_str("Initiallizing....\n", _ASCII);*/
				all_mode_init();
			}
		}
	}
	
	if(tick == _SET)									// 인터럽트 동작하면
	{
		tick = _RESET;									// 인터럽트 tick 초기화

		if(dir_pos[0] == 1 && dir_pos[1] == 0 && dir_pos[2] == 0 && dir_pos[3] == 1)		// 방향 확인
		{
			direction = FORWARD;					// 정방향으로 초기화
			for(int i=0; i<4; i++)					
			{
				dir_pos[i] = _RESET;						// 1 0 0 1 초기화
			}
		}
		else if(dir_pos[0] == 0 && dir_pos[1] == 1 && dir_pos[2] == 1 && dir_pos[3] == 0)			
		{
			direction = REVERSE;					// 역방향으로 초기화
			for(int i=0; i<4; i++)
			{
				dir_pos[i] = _RESET;						// 0 1 1 0 초기화
			}
			flag = _SET;								// 해당 뱡향에 의한 동작 flag
		}
		
		if(flag == _SET)								// 해당 방향이 SET이면
		{
			if(before_dir != direction)
			{
				uint8_t check = 0;					// 체크 변수
				ex_cnt++;							// 방향이 전환될 때 ex_cnt가 오름
				check = ex_cnt%2;					// ex_cnt 짝수를 확인
				if(check == 0)						// 짝수이면 
				{
					ex_cnt = 0;						// ex_cnt 초기화
					count++;						// 운동 횟수 count를 '1'씩 더함
					send_MSG();						// 프로토콜 전송
// 					USART_Transmit_str("\n------- cnt = ", _ASCII);
// 					translateChartoASCII(count);
// 					USART_Transmit_str(" -----------\n", _ASCII);
					flag = _RESET;
				}
			}

			before_dir = direction;
		}
	}
}

void AppInit(void)
{
	USART_Init(BAUD_9600);			// USART 9600 baudrate 설정
	PCINT_init();
	sei();
/*	USART_Transmit_str("START\n", _ASCII);*/
}

void all_mode_init(void)
{
	flag = _RESET;
	count = _RESET;
	ex_cnt = _RESET;
	direction = _RESET;
	before_dir = _RESET;
	send_MSG();
}

void send_MSG(void)
{
	USART_Transmit_char(0xEA);		// 프로토콜 전송
	USART_Transmit_char(count);
	USART_Transmit_char(0x00);
	USART_Transmit_char(0x5A);	
}