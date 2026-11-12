/*
 * timer.c
 *
 *  Created on: Nov 4, 2026
 *      Author: ntmin
 */
#include "timer.h"

int timer_counter[2] = {0, 0};
int timer_flag[2] = {0, 0};
int TICK = 10;

void setTimer(int index, int duration)
{
    timer_counter[index] = duration / TICK;
    timer_flag[index] = 0;
}

void timerRun(void)
{
    for(int i = 0; i < 2; i++)
    {
        if(timer_counter[i] > 0)
        {
            timer_counter[i]--;
            if(timer_counter[i] <= 0)
            {
                timer_flag[i] = 1;
            }
        }
    }
}

