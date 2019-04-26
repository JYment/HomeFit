/*
 * common.h
 *
 * Created: 2019-03-15 오후 3:38:14
 *  Author: Jae
 */ 


#ifndef COMMON_H_
#define COMMON_H_

#define F_CPU		16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "ATmega328_USART.h"
#include "application.h"
#include "ATmega328_PCINT.h"

#define _SET				1
#define _RESET				0

// 통신 프로토콜
#define PT_HEADER		0xEA
#define PT_TAIL			0x5A
#define PT_RESET		0xEE
#define PT_LENTH		3

#endif /* COMMON_H_ */