#include <avr/io.h>
#include <avr/interrupt.h>


#include "lcd.h"
#include "led.h"
#include "button_matrix.h"
#include "string.h"
#include "Guess_the_figure.h"


int counter =0;
int random_flag =0;
int enter_flag = 0;
int change_lcd =0;
int random_num = 0;
uint16_t btn = 0;

uint8_t LCD_house[8] =  {0x04 , 0x0E, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x1F};
uint8_t LCD_snow[8] =  {0x15 , 0x0E, 0x1F, 0x0E, 0x15, 0xE0, 0xE0, 0xE0};
uint8_t LCD_lattice[8] =  {0x0A , 0x0A, 0x1F, 0x0A, 0x0A, 0x1F, 0x0A, 0x0A};
uint8_t lattice[8] = {0x24,0x24,0xFF,0x24,0x24,0xFF,0x24,0x24};

void Timer_init(){
	TCCR0 = (1 << CS02) | (0 << CS01) | (1 << CS00);
	TIMSK = (1 << TOIE0);
}

ISR(TIMER0_OVF_vect){
	
	btn = btn_scan();
	if(btn==0x10){
		random_flag=1;
	}
	if(btn == 0x01){
		change_lcd=1;
	}
	if(btn==0x22){
		enter_flag=1;
	}
}



int main(void){
	
	/*btn_init();
	Timer_init();
	led_init();
	HD_Init();*/
	Timer_init();
	HD_Init();
	btn_init();
	led_init();
	sei();
	
	
	while(1){
		if(random_flag==1){
			//srand(time(NULL));
			random_num=rand()%6+1;
			Start(random_num);
			LCD_start();
			random_flag=0;
		}
		if(change_lcd==1){
			counter++;
			lcd_clear();
			
			Change_figure_LCD(counter);
			if(counter==6){
				counter=0;
			}
			change_lcd=0;
		}
		if(enter_flag==1){
			if(counter==random_num){
				Winner();
			}
			Losing();
		}
	}
}

