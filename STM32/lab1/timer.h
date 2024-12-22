/*
 * timer.h
 *
 *  Created on: 19 нояб. 2024 г.
 *      Author: Никита
 */

#ifndef MY_CODE_TIMER_H_
#define MY_CODE_TIMER_H_



#endif /* MY_CODE_TIMER_H_ */

void timer_init();

void timer_init_interrupts();

void timer_on();
void timer_off();
void set_period(uint32_t period_ms );
void get_timer_count_off();
