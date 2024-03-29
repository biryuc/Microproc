#include <avr/io.h>
#include <avr/interrupt.h>


#include "lcd.h"
#include "led.h"
#include "button_matrix.h"
#include "string.h"
#include "Guess_the_figure.h"

#include "i2c_eeprom.h"
uint8_t byte[10]={0xAA,7,8,5};
uint16_t address = 0;
uint8_t res[10];


int counter =0;
int random_flag =0;
int enter_flag = 0;
int change_lcd =0;
int random_num = 0;
int enter_counter =0;
int end =0;
uint16_t btn = 0;
uint8_t result[3]={0,0,0};
uint8_t LCD_house[8] =  {0x04 , 0x0E, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x1F};
uint8_t LCD_snow[8] =  {0x15 , 0x0E, 0x1F, 0x0E, 0x15, 0xE0, 0xE0, 0xE0};
uint8_t LCD_lattice[8] =  {0x0A , 0x0A, 0x1F, 0x0A, 0x0A, 0x1F, 0x0A, 0x0A};
uint8_t lattice[8] = {0x24,0x24,0xFF,0x24,0x24,0xFF,0x24,0x24};
uint8_t choose_[10] = {'Y','o', 'u', '-','c', 'h','o','o', 's','e'};
uint8_t win_[7] = {'Y','o','u',' ','W', 'I', 'N'};
uint8_t lose_[18] = {'Y','o','u',' ','L', 'o', 's','e',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
uint8_t happy[16]={'H','a','p','p','y',' ', 'N', 'e','w',' ','Y','e','a','r',' ',' '};
void Timer_init(){
	TCCR0 = (1 << CS02) | (0 << CS01) | (1 << CS00);
	TIMSK = (1 << TOIE0);
}

ISR(TIMER0_OVF_vect){
	
	btn = btn_scan();
	if(btn==0x10){
		random_flag=1;
	}
	if(btn == 0b00001000){
		change_lcd=1;
	}
	if(btn==0x01){
		enter_flag=1;
	}
}

int del=0;
int flag_level=0;
int save=0;
int main(void){
	
	
	//HD_Init();
	//led_init();
	uint8_t my_data[10] = {'0','1', '2', '3', '4', '5', '6', '7', '8','9'};
	//lcd_print(my_data);
	//Sendto7219(0x01,1);
	
	//init(MYUBRR);
	//Init_I2C();
	Timer_init();
	HD_Init();
	btn_init();
	led_init();
	sei();
	uint8_t byte[8]={0x04 , 0x0E, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x1F};
	uint8_t res_[8];
	uint16_t addr = 0;
	/*WriteByte_I2C(addr,byte);
	_delay_ms(300);
	ReadByte_I2C(addr,res_);
	Draw(res);*/
	
	while(1){
		if(random_flag==1){
			lcd_clear();
			lcd_print(happy);
			_delay_ms(7000);
			//srand(time(NULL));
			random_num=rand()%6+1;
			Start(random_num,del,flag_level);
			
			//save=del;
			//del++;
			
			
			//if(del==3){del=0;}
			//if(del==2){flag_level=1;}
			LCD_start();
			random_flag=0;
		}
		if(change_lcd==1){
			counter++;
			Clear_SPI();
			//LCD_figure(counter);
			if(flag_level==0 ){SPI_show(counter,del);}
			else if(flag_level==1){SPI_show_level3(counter,0);}
			/*del++;
			if(flag_level==1 && del==1){flag_level=0;
			del=0;}
			if (del==2){;
				del=0;
				flag_level=1;
			}*/
			if(counter==7){
				counter=0;
			}
			change_lcd=0;
		}
		if(enter_flag==1){
			if(counter==random_num){
				lcd_clear();
				lcd_print(win_);
			}else if(counter!=random_num){
				lcd_clear();
				lcd_print(lose_);
				//cur_move(4);
			}
			//cur_scdline();
			
			counter=0;
			enter_flag=0;
			del++;
			if(flag_level==1 && del==1){flag_level=0;
			del=0;}
			if (del==2){;
				del=0;
				flag_level=1;
			}
		}
	}
}

