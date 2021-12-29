
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
void Draw(uint8_t *picture,int delay){
	if(delay==0){_delay_ms(3500);}
	else if(delay==1){_delay_ms(2000);}
	else if(delay==2){_delay_ms(3500);}
	else if(delay==3){_delay_ms(2000);}
	for (int i=1;i<9;i++){
		Sendto7219(i,picture[i-1]);
	}
	
}


void Change_figure(int num,int delay){
	//int fi=0;
	//if (start==1){
	//	fi =Random_num();
		
		switch ( num )
		{
		
			case 1:
			Draw(house, delay);
			Clear_SPI();
			Draw(lattice_, delay);
			Clear_SPI();
			Draw(snow, delay);
			break;
			case 2:
			Draw(house, delay);
			Clear_SPI();
			Draw(snow, delay);
			Clear_SPI();
			Draw(lattice_, delay);
			break;
			case 3:
			Draw(snow, delay);
			Clear_SPI();
			Draw(lattice_, delay);
			Clear_SPI();
			Draw(house, delay);
			break;
			case 4:
			Draw(snow, delay);
			Clear_SPI();
			Draw(house, delay);
			Clear_SPI();
			Draw(lattice_, delay);
			break;
			case 5:
			Draw(house, delay);
			Clear_SPI();
			Draw(lattice_, delay);
			Clear_SPI();
			Draw(snow, delay);
			break;
			case 6:
			Draw(lattice_, delay);
			Clear_SPI();
			Draw(house, delay);
			Clear_SPI();
			Draw(snow, delay);
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

void Start(int run_,int delay,int flag){

	lcd_clear();
	Clear_SPI();
	lcd_print(start_data);
	cur_scdline();
	
	cur_move(1);
	
	Draw(three, delay);
	Clear_SPI();
	Draw(two, delay);
	Clear_SPI();
	Draw(one, delay);
	Clear_SPI();
	if(flag==0){Change_figure(run_, delay);}
	else{Change_figure_level3(run_, 0);}
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
	
void SPI_show(int num,int delay){
	switch ( num )
	{
		case 1:
		Draw(h_l_s_1_5, delay);
		break;
		case 2:
		Draw(h_s_l_2, delay);
		break;
		case 3:
		Draw(s_l_h_3, delay);
		break;
		case 4:
		Draw(s_h_l_4, delay);
		break;
		case 5:
		Draw(h_l_s_1_5, delay);
		break;
		case 6:
		Draw(l_h_s_6, delay);
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
uint8_t tree[8]={0x10,0x28,0x28,0x44,0x7C,0x28,0x44,0xFE};

void Change_figure_level3(int num,int delay){
	
	
	switch ( num )
	{
		
		case 1:
		Draw(house, delay);
		Clear_SPI();
		Draw(lattice_, delay);
		Clear_SPI();
		Draw(snow, delay);
		Clear_SPI();
		Draw(tree,delay);
		break;
		case 2:
		
		Draw(tree,delay);
		Clear_SPI();
		Draw(house, delay);
		Clear_SPI();
		Draw(snow, delay);
		Clear_SPI();
		Draw(lattice_, delay);
		break;
		case 3:
		Draw(snow, delay);
		Clear_SPI();
		Draw(lattice_, delay);
		Clear_SPI();
		Draw(tree,delay);
		Clear_SPI();
		Draw(house, delay);
		break;
		case 4:
		Draw(tree,delay);
		Clear_SPI();
		Draw(snow, delay);
		Clear_SPI();
		Draw(lattice_, delay);
		Clear_SPI();
		Draw(house, delay);
		
		break;
		case 5:
		Draw(house, delay);
		Clear_SPI();
		Draw(lattice_, delay);
		Clear_SPI();
		Draw(tree,delay);
		Clear_SPI();
		Draw(snow, delay);
		break;
		case 6:
		Draw(lattice_, delay);
		Clear_SPI();
		Draw(house, delay);
		Clear_SPI();
		Draw(snow, delay);
		Clear_SPI();
		Draw(tree,delay);
		break;
	}
	Clear_SPI();
	//}
	
	
}
uint8_t h_l_s_t_1[8]={0xA8,0xE8,0xAC,0x00,0xDC,0x88,0x48,0xC8};
uint8_t t_h_s_l_2[8]={0xEA,0x4E,0x4A,0x00,0xC8,0x88,0x48,0xCC};	
uint8_t s_l_t_h_3[8]={0xD0,0x90,0x50,0xD8,0x00,0xEA,0x4E,0x4A};
uint8_t t_s_l_h_4[8]={0xE6,0x44,0x42,0x46,0x00,0x8A,0x8E,0xCA};
uint8_t h_l_t_s_5[8]={0xA8,0xE8,0xAC,0x00,0xEC,0x48,0x44,0x4C};
uint8_t l_h_s_t_6[8]={0x8A,0x8E,0xCA,0x00,0xCE,0x84,0x44,0xC4};

void SPI_show_level3(int num,int delay){
	switch ( num )
	{
		case 1:
		Draw(h_l_s_t_1, delay);
		break;
		case 2:
		Draw(t_h_s_l_2, delay);
		break;
		case 3:
		Draw(s_l_t_h_3, delay);
		break;
		case 4:
		Draw(t_s_l_h_4, delay);
		break;
		case 5:
		Draw(h_l_t_s_5, delay);
		break;
		case 6:
		Draw(l_h_s_t_6, delay);
		break;
	}
}