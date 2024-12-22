/*
 * timer.h
 *
 *  Created on: Nov 24, 2024
 *      Author: Никита
 */

#ifndef MY_CODE_TIMER_TIMER_H_
#define MY_CODE_TIMER_TIMER_H_



#endif /* MY_CODE_TIMER_TIMER_H_ */

void timer_on();
void timer_off();
void set_period(uint32_t period_ms );
void get_timer_count_off();

void timer_init_interrupts6();
void timer_init_interrupts7();

void timer_on7();
void timer_off7();
void set_period7(uint32_t period_ms );

void GPIO_Init(void);

void timer_init2();
void Set_LED1_Brightness(uint16_t brightness);
void Set_LED2_Brightness(uint16_t brightness);

