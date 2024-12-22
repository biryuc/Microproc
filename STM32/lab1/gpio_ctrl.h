/*
 * gpio_ctrl.h
 *
 *  Created on: 11 нояб. 2024 г.
 *      Author: Никита
 */

#ifndef MY_CODE_GPIO_CTRL_H_
#define MY_CODE_GPIO_CTRL_H_



#endif /* MY_CODE_GPIO_CTRL_H_ */

#include "stm32f3xx_hal.h"

void gpio_init(GPIO_TypeDef* port, uint32_t line);
void gpio_set(GPIO_TypeDef* port, uint32_t line, uint8_t state);
uint8_t gpio_get(GPIO_TypeDef* port, uint32_t line);
void gpio_toggle(GPIO_TypeDef* port, uint32_t line);
void delay(int count);
void gpio_init_all_led();
void gpio_order_toggle();
