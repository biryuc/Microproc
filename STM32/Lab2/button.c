/*
 * button.c
 *
 *  Created on: 13 нояб. 2024 г.
 *      Author: Никита
 */
#include "stm32f3xx_hal.h"
#include "gpio_ctrl.h"
#include "timer_lab3.h"
#define GPIO_ODR_A0 (1 << 0)



void button_init()
{
	GPIO_TypeDef* port =  GPIOA;
	/* Инициалищация GPIO для кнопки */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	port->MODER |= (0x0 << 0); // устанавливаем режим
	port->OTYPER |= (0x0 << 0); // устанавливаем тип выхода
	port->OSPEEDR |= (0x0 << 0); // устанавливаем скорость
	port->PUPDR |= (0x0 << 0); // отключаем подтяжки порта


}

void button_init_with_interrupts()
{
	GPIO_TypeDef* port =  GPIOA;
	/* Инициалищация GPIO для кнопки */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	port->MODER |= (0x0 << 0); // устанавливаем режим
	port->OTYPER |= (0x0 << 0); // устанавливаем тип выхода
	port->OSPEEDR |= (0x0 << 0); // устанавливаем скорость
	port->PUPDR |= (0x0 << 0); // отключаем подтяжки порта

	NVIC_EnableIRQ(EXTI0_IRQn);
	EXTI->IMR |= GPIO_ODR_A0;
	EXTI->RTSR |= GPIO_ODR_A0; // включаем срабатывание по переднему фронту
	EXTI->FTSR &= ~GPIO_ODR_A0; // отключаем срабатывание по заднему фронту

}

void button_init_with_interrupts_ftsr()
{
	GPIO_TypeDef* port =  GPIOA;
	/* Инициалищация GPIO для кнопки */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	port->MODER |= (0x0 << 0); // устанавливаем режим
	port->OTYPER |= (0x0 << 0); // устанавливаем тип выхода
	port->OSPEEDR |= (0x0 << 0); // устанавливаем скорость
	port->PUPDR |= (0x0 << 0); // отключаем подтяжки порта

	NVIC_EnableIRQ(EXTI0_IRQn);
	EXTI->IMR |= (1 << 0);
	EXTI->RTSR |= (1 << 0); // включаем срабатывание по переднему фронту
	EXTI->FTSR |= (1 << 0); // включаем срабатывание по заднему фронту

}

uint16_t button_read(void){

	return GPIOA->IDR&(1<<0);
}

void button_toggle( uint32_t line){
	GPIO_TypeDef* port =  GPIOE;
	uint16_t state = button_read();

	if (state){
		gpio_toggle( port, line);
	}


}


void button_without_interrupts(){
	//	delay(count);
	//	button_toggle(line1);
	//
	//	gpio_toggle( port, line1);
	//	delay(count*10);
}

//void EXTI0_IRQHandler(void) {
//	static volatile uint8_t flag = 0;
//	if (flag) {
//		GPIOE->BSRR = (0x1 << 10); // led on
//	    flag = 0;
//	} else {
//		GPIOE->BSRR = (0x1 << (10+16)); // led off
//		flag = 1;
//	}
//
//	EXTI->PR |= (1 << 0);
//
//}


//Task3
//void EXTI0_IRQHandler(void) {
//
//	GPIOE->BSRR = (0x1 << 10); // led on
//	timer_on();
//	set_period(1);
//
//	EXTI->PR |= (1 << 0);
//}



//Task 2
//Срабатывание только при нажатии
void EXTI0_IRQHandler(void) {
	static volatile uint8_t flag = 0;
//	if (flag) {
//		GPIOE->BSRR = (0x1 << (10+16)); // led off
//	    flag = 0;
//	} else {
		GPIOE->BSRR = (0x1 << 10); // led on
		flag = 1;
//	}

	EXTI->PR |= (1 << 0);

	 timer_on();
	 set_period(5000);

}
