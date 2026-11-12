/*
 * timer.h
 *
 *  Created on: Nov 4, 2026
 *      Author: ntmin
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
//1 cho UART va 1 cho LED
extern int timer_flag[2];
void setTimer(int index, int duration);
void timerRun(void);

#endif /* INC_TIMER_H_ */
