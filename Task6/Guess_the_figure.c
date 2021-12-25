
#include "Guess_the_figure.h"
#include "led.h"
#include "lcd.h"
#include "i2c_eeprom.h"
#include <stdio.h>   
#include <stdlib.h>
uint8_t LCD_house_[8] =  {0x04 , 0x0E, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x1F};
uint8_t LCD_snow_[8] =  {0x15 , 0x0E, 0x1F, 0x0E, 0x15, 0xE0, 0xE0, 0xE0};
uint8_t LCD_lattice_[8] =  {0x0A , 0x0A, 0x1F, 0x0A, 0x0A, 0x1F, 0x0A, 0x0A};
	
uint8_t zero_grid[8] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t snow[8] = {0x99,0x5A,0x3C,0x18,0xFF,0x3C,0x5A,0x99};
uint8_t house[8] = {0x18,0x3C,0x7E,0xFF,0xFF,0x81,0x81,0xFF};
uint8_t lattice_[8] = {0x24,0x24,0xFF,0x24,0x24,0xFF,0x24,0x24};
uint8_t new_grid[8] ={0x24,0x24,0xFF,0x24,0x24,0xFF,0x24,0x24};
uint8_t three[8] = {0xFF,0x01,0x01,0xFF,0x01,0x01,0x01,0xFF};
uint8_t two[8] = {0xFF,0x01,0x01,0xFF,0x80,0x80,0x80,0xFF};
uint8_t one[8] = {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18};
/*
 uint8_t LCD_house[8] =  {0x04 , 0x0E, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x1F};
 uint8_t LCD_snow[8] =  {0x15 , 0x0E, 0x1F, 0x0E, 0x15, 0x00, 0x00, 0x00};
 uint8_t LCD_lattice[8] =  {0x0A , 0x0A, 0x1F, 0x0A, 0x0A, 0x1F, 0x0A, 0x0A};
	
 uint8_t zero_grid[8] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

 uint8_t snow[8] = {
	0b10011001,
	0b01011010,
	0b00111100,
	0b00011000,
	0b11111111,
	0b00111100,
	0b01011010,
	0b10011001};

 uint8_t house[8] = {
	0b00011000,
	0b00111100,
	0b01111110,
	0b11111111,
	0b11111111,
	0b10000001,
	0b10000001,
	0b11111111};

 uint8_t lattice_[8] = {0x24,0x24,0xFF,0x24,0x24,0xFF,0x24,0x24};
 uint8_t new_grid[8] ={0x24,0x24,0xFF,0x24,0x24,0xFF,0x24,0x24};


uint8_t player_1 = 0b01000000;
uint8_t player_2 = 0b11000000;

uint8_t LCD_data1[11] = {'E', 'N', 'D', '!','A','g','a','i','n','?'};
uint8_t LCD_data2[20] = {'Y','o','u',' ','W', 'I', 'N'};
uint8_t LCD_data3[8] = {'P', 'L', 'A', 'Y', 'E', 'R', ':'};

uint8_t error_data[7] = {'E','r','r','o','r','!'};
*/	

uint8_t start_data[6] = {'S','t', 'a', 'r', 't'};	
uint8_t choose[6] = {'C','h','o','o','s','e'};
uint8_t press_btn[5]={'P','r','e','s','s'};
uint8_t win[7] = {'Y','o','u',' ','W', 'I', 'N'};
uint8_t lose[8] = {'Y','o','u',' ','L', 'o', 's','e'};	
uint8_t score[5] = {'S','c', 'o', 'r', 'e'}	;
uint8_t zero_[9] = {' ',' ', ' ', ' ',' ', ' ',' ',' ', ' '};
int Random_num(){
	int r=0;
	//struct pair arr[3] ;
	//srand(time(NULL));
	//srand(1);
	r = rand()%6 +1;
	return r;
}




void Clear_SPI(){
	_delay_ms(500);
	for (int i=1;i<9;i++){
		Sendto7219(i,zero_grid[i-1]);
	}
	
}
void Draw(uint8_t *picture){
	_delay_ms(3500);
	for (int i=1;i<9;i++){
		Sendto7219(i,picture[i-1]);
	}
	
}


void Change_figure(int num){
	//int fi=0;
	//if (start==1){
	//	fi =Random_num();
		
		switch ( num )
		{
		
			case 1:
			Draw(house);
			Clear_SPI();
			Draw(lattice_);
			Clear_SPI();
			Draw(snow);
			break;
			case 2:
			Draw(house);
			Clear_SPI();
			Draw(snow);
			Clear_SPI();
			Draw(lattice_);
			break;
			case 3:
			Draw(snow);
			Clear_SPI();
			Draw(lattice_);
			Clear_SPI();
			Draw(house);
			break;
			case 4:
			Draw(snow);
			Clear_SPI();
			Draw(house);
			Clear_SPI();
			Draw(lattice_);
			break;
			case 5:
			Draw(house);
			Clear_SPI();
			Draw(lattice_);
			Clear_SPI();
			Draw(snow);
			break;
			case 6:
			Draw(lattice_);
			Clear_SPI();
			Draw(house);
			Clear_SPI();
			Draw(snow);
			break;
		}
		Clear_SPI();
	//}
	
	
}

uint8_t Read_score(){
	uint8_t res[10];
	ReadByte_I2C(0,res);
	return res[0];
}

void Start(int run_){
	uint8_t res[1];
	res[0]=Read_score();
	lcd_clear();
	Clear_SPI();
	lcd_print(start_data);
	cur_scdline();
	//lcd_print(score);
	cur_move(1);
	//lcd_print(res);
	//lcd_print(zero_);
	Draw(three);
	Clear_SPI();
	Draw(two);
	Clear_SPI();
	Draw(one);
	Clear_SPI();
	Change_figure(run_);
	lcd_clear();
	cur_home();
}

void LCD_start(){
	cur_home();
	Clear_SPI();
	lcd_clear();
	lcd_print(press_btn);
	
}

void LCD_figure(int count){
	switch ( count )
	{
		
		case 1:
		my_char(LCD_house_);
		break;
		case 2:
		my_char(LCD_lattice_);
		break;
		case 3:
		my_char(LCD_snow_);
		break;
	}
}

uint8_t h_l_s_1_5[8]= {0x40,0xA0,0xF4,0x1C,0x14,0x05,0x02,0x05};
uint8_t h_s_l_2[8]=	  {0x40,0xA0,0xF4,0x08,0x14,0x05,0x07,0x05};
uint8_t s_l_h_3[8]=   {0xA0,0x40,0xA0,0x14,0x1C,0x16,0x05,0x07};
uint8_t s_h_l_4[8]=   {0xA0,0x40,0xA8,0x14,0x1C,0x05,0x07,0x05};
uint8_t l_h_s_6[8]=   {0xA0,0xE0,0xA8,0x14,0x1C,0x05,0x02,0x05};
	
void SPI_show(int num){
	switch ( num )
	{
		case 1:
		Draw(h_l_s_1_5);
		break;
		case 2:
		Draw(h_s_l_2);
		break;
		case 3:
		Draw(s_l_h_3);
		break;
		case 4:
		Draw(s_h_l_4);
		break;
		case 5:
		Draw(h_l_s_1_5);
		break;
		case 6:
		Draw(l_h_s_6);
		break;
	}
}

void Change_figure_LCD(int count){	
	switch ( count )
	{
		
		case 1:
		my_char(LCD_house_);
		cur_move(2);
		my_char(LCD_lattice_);
		cur_move(2);
		my_char(LCD_snow_);
		break;
		case 2:
		my_char(LCD_house_);
		cur_move(2);
		my_char(LCD_snow_);
		cur_move(2);
		my_char(LCD_lattice_);
		break;
		case 3:
		my_char(LCD_snow_);
		cur_move(2);
		my_char(LCD_lattice_);
		cur_move(2);
		my_char(LCD_house_);
		break;
		case 4:
		my_char(LCD_snow_);
		cur_move(2);
		my_char(LCD_house_);
		cur_move(2);
		my_char(LCD_lattice_);
		break;
		case 5:
		my_char(LCD_house_);
		cur_move(2);
		my_char(LCD_lattice_);
		cur_move(2);
		my_char(LCD_snow_);
		break;
		case 6:
		my_char(LCD_lattice_);
		cur_move(2);
		my_char(LCD_house_);
		cur_move(2);
		my_char(LCD_snow_);
		break;
	}
	
}

void Winner(){
	lcd_clear();
	lcd_print(win);
}
void Losing(){
	lcd_clear();
	lcd_print(lose);	
}
//house-1   lattice-2  snow-3
int Win(uint8_t *res,int rnd){
	int win_=0;
	switch ( rnd )
	{
		
		case 1:
		if(res[0]==1 && res[1]==2 && res[2]==3){
			win_=1;
		}
		break;
		case 2:
		if(res[0]==1 && res[1]==3 && res[2]==2){
			win_=1;
		}
		break;
		case 3:
		if(res[0]==3 && res[1]==2 && res[2]==1){
			win_=1;
		}
		break;
		case 4:
		if(res[0]==3 && res[1]==1 && res[2]==2){
			win_=1;
		}
		break;
		case 5:
		if(res[0]==1 && res[1]==2 && res[2]==3){
			win_=1;
		}
		break;
		case 6:
		if(res[0]==2 && res[1]==1 && res[2]==3){
			win_=1;
		}
		break;
	}
	return win_;
}