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
#define HEADER			0xEA
#define TAIL			0x5A
#define STATE_ON		0xFF
#define STATE_OFF		0x00

// 동작
#define FORWARD			11
#define REVERSE			22


void ApplicationMain(void);
void AppInit(void);

#endif /* APPLICATION_H_ */