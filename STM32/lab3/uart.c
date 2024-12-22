/*
 * uart.c
 *
 *  Created on: Dec 11, 2024
 *      Author: Никита
 */

#include "stm32f3xx_hal.h"



typedef struct uart_rx_tx_type{
	uint8_t len;
	uint8_t ptr;
	uint8_t data[255];
} uart_rx_tx_type;


void uart_init_interrupts(){

	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	RCC->APB1ENR |= RCC_APB1ENR_UART4EN;

	GPIOC->MODER |= GPIO_MODER_MODER10_1|GPIO_MODER_MODER11_1;

	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1|GPIO_OSPEEDER_OSPEEDR11_1;

	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR10_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR11;

	GPIOC->AFR[0] = 0;
	GPIOC->AFR[1] |= (5<<12)|(5<<8);
	GPIOC->OTYPER = 0; // Push-Pull

	UART4->CR1 = 0;
	UART4->CR2 = 0;
	UART4->CR3 = 0;

	UART4->BRR = 1042;

	//Разрешение прерываний
	UART4->CR1 |= ( USART_CR1_RE| USART_CR1_TE | USART_CR1_RXNEIE );
//	USART_CR1_TXEIE //USART_CR1_TE
	NVIC_EnableIRQ(UART4_IRQn);

	UART4->CR1 |= (1<<0);



}

uint8_t receive_byte(void){
	 while (!(UART4->ISR & USART_ISR_RXNE));
	 return UART4->RDR;
}



void Led_control(char led_num, char mode){

	   uint8_t port_state = 0;

	   if (mode == 'N'){
			   port_state = 1;
	   }

		switch ( led_num )
			{

			    case '0':

					gpio_set(GPIOE, 10, port_state);
					break;
			    case '1':
			    	gpio_set(GPIOE, 11, port_state);
			    	break;
			    case '2':
			    	gpio_set(GPIOE, 12, port_state);
			    	break;
			    case '3':
			    	gpio_set(GPIOE, 13, port_state);
			    	break;
			    case '4':
			    	gpio_set(GPIOE, 14, port_state);
			    	break;
			    case '5':
			    	gpio_set(GPIOE, 15, port_state);
			    	break;
			    case '8':
			    	gpio_set(GPIOE, 8, port_state);
			    	break;
			    case '9':
			    	gpio_set(GPIOE, 9, port_state);
			    	break;
			}



}





