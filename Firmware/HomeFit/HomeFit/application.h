/*
 * application.h
 *
 * Created: 2019-03-15 오후 3:39:18
 *  Author: Jae
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "common.h"

// 통신 프로토콜
#define PT_HEADER		0xEA
#define PT_TAIL			0x5A
#define PT_RESET		0xEE


// 동작
#define FORWARD			11
#define REVERSE			22


void ApplicationMain(void);
void AppInit(void);
void all_mode_init(void);
void send_MSG(void);

#endif /* APPLICATION_H_ */