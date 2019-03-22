/*
 * ATmega328_PCINT.h
 *
 * Created: 2019-03-15 오후 5:43:18
 *  Author: Jae
 */ 


#ifndef ATMEGA328_PCINT_H_
#define ATMEGA328_PCINT_H_

#include "common.h"

#define WIRE_DIR_LEFT		0x02
#define WIRE_DIR_RIGHT		0x04
#define POW_DIR_LEFT		0x01
#define POW_DIR_RIGHT		0x08

extern volatile uint8_t pin0_flg, pin8_flg;
extern volatile uint8_t wire_left_flg_1, wire_left_flg_2;
extern volatile uint8_t wire_right_flg_1, wire_right_flg_2;
extern uint8_t direction, tick, pow_direction;
extern volatile uint8_t wire_dir_pos[4];
extern volatile uint8_t pow_dir_pos[4];
void PCINT_init(void);

#endif /* ATMEGA328_PCINT_H_ */