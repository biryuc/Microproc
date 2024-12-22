/*
 * gpio_ctrl.c
 *
 *  Created on: 11 нояб. 2024 г.
 *      Author: Никита
 */

#include "stm32f3xx_hal.h"

void gpio_init(GPIO_TypeDef* port, uint32_t line){

	/* Данный код для настроек после перезагрузки */
	port->MODER |= (0x1 << line*2); // устанавливаем режим входа
	port->OTYPER |= (0x0 << line); // устанавливаем тип входа
	port->OSPEEDR |= (0x3 << line*2); // устанавливаем скорость
	port->PUPDR |= (0x0 << line*2); // отключаем подтяжки порта
	//GPIOE

}

void gpio_init_all_led(){
	for(int line=8 ;line<=15;line++){
		gpio_init(GPIOE, line);
	}
}


void gpio_set(GPIO_TypeDef* port, uint32_t line, uint8_t state){

	/* Установка значение линии порта с сохранение состояния остальных линий */
	if (state){
		port->BSRR = (state << line);
	}
	else{
		port->BSRR = (0x1 << (line+16));
	}


}


uint8_t gpio_get(GPIO_TypeDef* port, uint32_t line){


	return port->IDR>>line;
}

void gpio_toggle(GPIO_TypeDef* port, uint32_t line){

	uint8_t port_state = gpio_get(port,line);

	port_state ^= (1<<0);

	gpio_set(port, line, port_state);

}


void delay(int count){
	int j = 0;
	for(int i=0;i<count;i++){
		j++;
	}
}


//Lab1
void gpio_order_toggle(){

	int count = 50000;
	GPIO_TypeDef* port =  GPIOE;
	for(int line=8;line<=15;line++){
		gpio_toggle( port, line);
		delay(count);
		gpio_toggle( port, line);
	}
	//	gpio_toggle( port, line);
	//	delay(count);
}
