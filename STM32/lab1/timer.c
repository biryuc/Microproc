/*
 * timer.c
 *
 *  Created on: 19 нояб. 2024 г.
 *      Author: Никита
 */

#include "stm32f3xx_hal.h"
#include "gpio_ctrl.h"

int button_press_time = 0;
int led_timer = 0;

void timer_init(){

	// Разрешение тактирования TIM6
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	// Настройка таймера TIM6
	TIM6->CR1 |= (0<<11)|(0<<7)|(0<<3)|(0<<1)|(0<<0); // общая настройка таймера
	TIM6->CR2 = 0; // настройка работы в режиме мастера
	TIM6->EGR = 0; // не используется
	TIM6->DIER |= (0<<0); // прерывания отключены
	TIM6->PSC = 9999; // период счетчика 1 мс

	// Разрешение прерывания по переполнению таймера TIM6
	//NVIC_EnableIRQ(TIM6_DAC_IRQn);

}


void timer_init_interrupts(){

	// Разрешение тактирования TIM6
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	// Настройка таймера TIM6
	TIM6->CR1 |= (0<<11)|(1<<7)|(0<<3)|(0<<1)|(0<<0); // общая настройка таймера
	TIM6->CR2 = 0; // настройка работы в режиме мастера
	TIM6->EGR = 0; // не используется
	TIM6->DIER |= (1<<0); // прерывания включены
	TIM6->PSC = 9999; // период счетчика 1 мс
	// Разрешение прерывания по переполнению таймера TIM6
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

}




void timer_on(){
	TIM6->CR1 |= (1<<0); // включение таймера
}

void timer_off(){
	TIM6->CR1 |= (0<<0); // выключение таймера
}

void set_period(int period_ms ){

	TIM6->ARR = period_ms; // период счетчика 1 мс
}

void get_timer_count_off(){

	while ((TIM6->CR1 & 0x01) != 0x0){

	}

}



void TIM6_DAC_IRQHandler(void)
{
// Код обработки прерывания
	GPIO_TypeDef* port =  GPIOE;
	uint32_t line = 8;


	if ((GPIOA->IDR & (1<<0)) == 1) { // Button pressed
	            button_press_time++;
	} else {
		if (button_press_time > 0 && button_press_time < 1000) { // Short press (less than 1 second)
			led_timer = 3; // 3 seconds
		} else if (button_press_time >= 1000) { // Long press (1 second or more)
			led_timer = 5; // 5 seconds
		}
		button_press_time = 0;
	}


	if (led_timer > 0) {
		gpio_set(port,  line,  1); // Turn on LED
		led_timer--;
	} else {
		gpio_set(port,  line,  0); // Turn off LED
	}

}


//void TIM6_DAC_IRQHandler(void)
//{
//// Код обработки прерывания
//	GPIO_TypeDef* port =  GPIOE;
//	uint32_t line = 10;
////	gpio_toggle( port, line);
//	gpio_set(port,  line,  0);
//
//	//timer_off();
//
//// очистка прерывания
//	TIM6->SR &= ~(0x01); // обнуление флага вызова прерывания
//
//	timer_off();
//}
