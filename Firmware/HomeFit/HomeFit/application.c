/*
 * application.c
 *
 * Created: 2019-03-15 오후 3:39:30
 *  Author: Jae
 */ 
#include "common.h"

uint8_t flag = 0, pow_flag = 0;
uint8_t ex_cnt = 0, count = 0, pow_ex_cnt = 1, pow_count = 1;
uint8_t before_dir = 0;

void ApplicationMain(void)
{
	receive_msg();										// 초기화 메세지 받을때 처리
	
	if(tick == _SET)									// 인터럽트 동작하면
	{
		tick = _RESET;									// 인터럽트 tick 초기화

		if(wire_dir_pos[0] == 1 && wire_dir_pos[1] == 0 && wire_dir_pos[2] == 0 && wire_dir_pos[3] == 1)		
		{
			direction = FORWARD;						// 1 0 0 1 이면 정방향으로 초기화
			for(int i=0; i<4; i++)					
			{
				wire_dir_pos[i] = _RESET;				
			}
		}
		else if(wire_dir_pos[0] == 0 && wire_dir_pos[1] == 1 && wire_dir_pos[2] == 1 && wire_dir_pos[3] == 0)			
		{
			direction = REVERSE;						// 0 1 1 0 이면 역방향으로 초기화
			for(int i=0; i<4; i++)
			
			{
				wire_dir_pos[i] = _RESET;				
			}
			flag = _SET;								// 해당 뱡향에 의한 동작 flag
		}
		
		if(flag == _SET)								// 해당 방향이 SET이면
		{
			if(before_dir != direction)
			{
				uint8_t check = 0;						// 체크 변수
				ex_cnt++;								// 방향이 전환될 때 ex_cnt가 오름
				check = ex_cnt%2;						// ex_cnt 짝수를 확인
				if(check == 0)							// 짝수이면 
				{
					ex_cnt = 0;							// ex_cnt 초기화
					count++;							// 운동 횟수 count를 '1'씩 더함
					send_msg();							// 데이터 프로토콜 전송
// 					USART_Transmit_str("\n------- cnt = ", _ASCII);
// 					translateChartoASCII(count);
// 					USART_Transmit_str(" -----------\n", _ASCII);
					flag = _RESET;
				}
			}

			before_dir = direction;					
		}
		
		if(pow_dir_pos[0] == 1 && pow_dir_pos[1] == 0 && pow_dir_pos[2] == 0 && pow_dir_pos[3] == 1)
		{
			pow_ex_cnt++;
			if(pow_ex_cnt == 5)
			{
				pow_count++;
				pow_ex_cnt = 1;
			}
			send_msg();
			for(int i=0; i<4; i++)
			{
				pow_dir_pos[i] = _RESET;					
			}
		}
		else if(pow_dir_pos[0] == 0 && pow_dir_pos[1] == 1 && pow_dir_pos[2] == 1 && pow_dir_pos[3] == 0)
		{
			pow_ex_cnt--;
			if(pow_ex_cnt == 0)
			{
				pow_count--;
				pow_ex_cnt = 4;
				if(pow_count < 1)	pow_count = 1;
			}
			
			send_msg();
			for(int i=0; i<4; i++)
			{
				pow_dir_pos[i] = _RESET;					
			}
		}
	}
}

void AppInit(void)
{
	USART_Init(BAUD_9600);			// USART 9600 baudrate 설정
	PCINT_init();
	sei();
	USART_Transmit_str("START\n", _ASCII);
}

void all_mode_init(void)
{
	flag = _RESET;
	count = _RESET;
	ex_cnt = _RESET;
	direction = _RESET;
	before_dir = _RESET;
	pow_flag = _RESET;
	pow_count = _RESET;
	send_msg();
}

void send_msg(void)
{
	USART_Transmit_char(0xEA);		// 프로토콜 전송
	USART_Transmit_char(count);
	USART_Transmit_char(pow_count);
	USART_Transmit_char(0x5A);	
}

void receive_msg(void)
{
	if(rx_flag == _SET)
	{
		rx_flag = _RESET;
		if(str[0] == PT_HEADER && str[2] == PT_TAIL)
		{
			if(str[1] == PT_RESET)
			{
				USART_Transmit_str("Initiallizing....\n", _ASCII);
				all_mode_init();
			}
			for(int i=0; i<PT_LENTH; i++)
			{
				str[i] = _RESET;
			}
		}
		else
		{
			for(int i=0; i<PT_LENTH; i++)
			{
				str[i] = _RESET;
			}
		}
	}
}