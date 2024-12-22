/*
 * timer.c
 *
 *  Created on: Nov 24, 2024
 *      Author: Никита
 */


#include "stm32f3xx_hal.h"
#include "gpio_ctrl.h"

static volatile uint32_t button_press_time = 0;
static volatile uint32_t led_timer = 0;
int flag = 0;

uint16_t brightness = 0;
int8_t direction = 1;

int8_t procent = 0;
int8_t procent2 = 0;


int8_t direction_procent = 1;

void timer_init_interrupts6(){

	// Разрешение тактирования TIM6
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	// Настройка таймера TIM6
	TIM6->CR1 |= (0<<11)|(1<<7)|(0<<3)|(0<<1)|(0<<0); // общая настройка таймера
	TIM6->CR2 = 0; // настройка работы в режиме мастера
	TIM6->EGR = 0; // не используется
	TIM6->DIER |= (1<<0); // прерывания включены
	//TIM6->PSC = 9999; // период счетчика 1 мс
	TIM6->PSC = 99 ;
	// Разрешение прерывания по переполнению таймера TIM6
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

}

void timer_init_interrupts7(){


	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	// Настройка таймера TIM7
	TIM7->CR1 |= (0<<11)|(1<<7)|(0<<3)|(0<<1)|(0<<0); // общая настройка таймера
	TIM7->CR2 = 0; // настройка работы в режиме мастера
	TIM7->EGR = 0; // не используется
	TIM7->DIER |= (1<<0); // прерывания включены
	TIM7->PSC = 99; // период счетчика 1 мс
	// Разрешение прерывания по переполнению таймера TIM6
	NVIC_EnableIRQ(TIM7_IRQn);

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


void timer_on7(){
	TIM7->CR1 |= (1<<0); // включение таймера
}

void timer_off7(){
	TIM7->CR1 |= (0<<0); // выключение таймера
}

void set_period7(int period_ms ){

	TIM7->ARR = period_ms; // период счетчика 1 мс
}

void get_timer_count_off(){

	while ((TIM6->CR1 & 0x01) != 0x0){

	}

}

void change_brightness(){
	procent+=direction_procent;
	procent2++;
	if (procent== 100){
		//procent =0;
		direction_procent = -1;
	}else if (procent == 0){
		direction_procent = 1;
	}
	if (procent2== 100){
		procent2 =0;
	}
}
//Task 2 выключение через 5 сек

//void TIM6_DAC_IRQHandler(void)
//{
//// Код обработки прерывания
//	GPIO_TypeDef* port =  GPIOE;
//	uint32_t line = 10;
//
//	gpio_set(port,  line,  0);
//
//// очистка прерывания
//	TIM6->SR &= ~(0x01); // обнуление флага вызова прерывания
//
//	timer_off();
//}



//Task 4 Мигание с разными периодами

//void TIM6_DAC_IRQHandler(void){
//
//	// Код обработки прерывания
//			GPIO_TypeDef* port =  GPIOE;
//			uint32_t line = 8;
//			gpio_toggle( port, line);
//
//		// очистка прерывания
//			TIM6->SR &= ~(0x01); // обнуление флага вызова прерывания
//
//}
//
//void TIM7_IRQHandler(void){
//
//	// Код обработки прерывания
//		GPIO_TypeDef* port =  GPIOE;
//		uint32_t line = 10;
//		gpio_toggle( port, line);
//
//	// очистка прерывания
//		TIM7->SR &= ~(0x01); // обнуление флага вызова прерывания
//
//}


//Task 3
//void TIM6_DAC_IRQHandler(void)
//{
//
//	GPIO_TypeDef* port =  GPIOE;
//	uint32_t line = 10;
//
//
//	if ((GPIOA->IDR & (1<<0)) == 1) {
//	            button_press_time++;
//	} else {
//		if (button_press_time > 0 && button_press_time < 1000) {
//			led_timer = 1500;
//
//		} else if (button_press_time >= 1000) {
//			led_timer = 2500;
//
//		}
//		button_press_time = 0;
//	}
//
//
//	if (led_timer > 0 ) {
//		gpio_set(port,  line,  1);
//		led_timer--;
//
//	}
//	else  {
//		gpio_set(port,  line,  0);
//
//		flag = 0;
//	}
//
//	TIM6->SR &= ~(0x01);
//
//}


// Task 5 изменение яркости

volatile uint16_t brightness1 = 0;
volatile uint16_t brightness2 = 0;

void TIM6_DAC_IRQHandler(void){

	// Код обработки прерывания
	GPIO_TypeDef* port =  GPIOE;
	uint32_t line = 8;
	//gpio_toggle( port, line);


    if (brightness1 == 100) {
    	direction = -1;
	  // gpio_set(port,  line,  1);

	} else if (brightness1 == 0) {
		direction = 1;
		//gpio_set(port,  line,  0);

	}

    brightness1 +=direction;

    if (brightness1 < procent  ) {
    	gpio_set(port,  line,  1);
   } else {
	   gpio_set(port,  line,  0);
   }



	// очистка прерывания
	TIM6->SR &= ~(0x01); // обнуление флага вызова прерывания

}

void TIM7_IRQHandler(void){

	// Код обработки прерывания
		GPIO_TypeDef* port =  GPIOE;
		uint32_t line = 10;


		 if (brightness2 < procent2) {
			   gpio_set(port,  line,  1);

			} else {
				gpio_set(port,  line,  0);

			}

		    brightness2++;


		    if (brightness2 == 100){
		    	brightness2 =0;
		    }

	// очистка прерывания
		TIM7->SR &= ~(0x01); // обнуление флага вызова прерывания

}




