/*
 * ATmega328_PCINT.h
 *
 * Created: 2019-03-15 오후 5:43:18
 *  Author: Jae
 */ 


#ifndef ATMEGA328_PCINT_H_
#define ATMEGA328_PCINT_H_

#include "common.h"

extern volatile uint8_t pin0_flg, pin2_flg, pin4_flg, pin8_flg;
extern volatile uint8_t pin2_forward_flg, pin4_reverse_flg;
extern uint8_t state;

void PCINT_init(void);

#endif /* ATMEGA328_PCINT_H_ */