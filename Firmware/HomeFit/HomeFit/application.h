/*
 * application.h
 *
 * Created: 2019-03-15 오후 3:39:18
 *  Author: Jae
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "common.h"



// 동작
#define FORWARD			11
#define REVERSE			22


void ApplicationMain(void);
void AppInit(void);
void all_mode_init(void);
void send_msg(void);
void receive_msg(void);

#endif /* APPLICATION_H_ */