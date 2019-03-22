/*
 * ATmega328_PCINT.c
 *
 * Created: 2019-03-15 오후 5:42:55
 *  Author: Jae
 */ 

#include "ATmega328_PCINT.h"

volatile uint8_t forward_dir_flg, reverse_dir_flg;
volatile uint8_t pow_forward_dir_flg, pow_reverse_dir_flg;
volatile uint8_t wire_left_flg_1 = 0, wire_left_flg_2 = 0;
volatile uint8_t wire_right_flg_1 = 0, wire_right_flg_2 = 0;
uint8_t direction = 0;
uint8_t pow_direction = 0;
uint8_t tick = 0;
volatile uint8_t wire_dir_pos[4] = {0, 0, 0, 0};
volatile uint8_t pow_dir_pos[4] = {0, 0, 0, 0};
volatile uint8_t i = 0, j = 0;


void PCINT_init(void)
{
	DDRB &= ~((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3));
	PCICR = (1 << PCIE0);
	PCMSK0 = (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3);
}


ISR(PCINT0_vect)
{
	uint8_t input_check = PINB & 0x0F;
	tick = _SET;
	switch(input_check)
	{
		case WIRE_DIR_LEFT:							// 왼쪽 리드스위치 INT가 동작하면
	
		wire_dir_pos[i++] = forward_dir_flg = _SET;		// wire_dir_pos[0 or 2] '1' 설정
		wire_dir_pos[i++] = reverse_dir_flg = _RESET;	// wire_dir_pos[1 or 3] '0' 설정
		if(i>3)		i = _RESET;
		
// 		if(direction == FORWARD)					// 방향이 정방향으로 지정됐다면
// 		{
// 			wire_left_flg_1 = _SET;					// 왼쪽 flag_1 '0' 설정
// 			wire_left_flg_2 = _RESET;				// 왼쪽 flag_2 '1' 설정
// 		}
// 		else										// 최초 동작 스위치가 왼쪽이면
// 		{
// 			wire_left_flg_1 = _RESET;				// 왼쪽 flag '1' 초기화
// 			wire_left_flg_2 = _SET;					// 오른쪽 flag '0' 초기화
// 		}
		break;
		
		case WIRE_DIR_RIGHT:						// 오른쪽 리드스위치 INT가 동작하면
		wire_dir_pos[i++] = forward_dir_flg = _RESET;	// wire_dir_pos[0 or 2] '0' 설정
		wire_dir_pos[i++] = reverse_dir_flg = _SET;		// wire_dir_pos[1 or 3] '1' 설정
		if(i>3)		i = _RESET;		
		
// 		if(direction == FORWARD)					// 방향이 정방향으로 지정됐다면
// 		{
// 			wire_right_flg_1 = _RESET;				// 왼쪽 flag '1' 설정
// 			wire_right_flg_2 = _SET;				// 오른쪽 flag '0' 설정
// 		}
// 		else										// 최초 동작 스위치가 오른쪽이면
// 		{
// 			wire_right_flg_1 = _SET;				// 왼쪽 flag '1' 초기화
// 			wire_right_flg_2 = _RESET;				// 오른쪽 flag '0' 초기화
// 		}
		break;
		
		case POW_DIR_LEFT:
		pow_dir_pos[j++] = pow_forward_dir_flg = _SET;
		pow_dir_pos[j++] = pow_reverse_dir_flg = _RESET;
		if(j>3)		j = _RESET;
		break;
		
		case POW_DIR_RIGHT:
		pow_dir_pos[j++] = pow_forward_dir_flg = _RESET;
		pow_dir_pos[j++] = pow_reverse_dir_flg = _SET;
		if(j>3)		j = _RESET;
		break;		
	}
}