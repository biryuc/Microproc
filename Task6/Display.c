#include <avr/io.h>
#include <util/delay.h>
/*
#define DATA_PORT PORTA
#define DATA_DDR DDRA
#define DATA_PIN PINA

#define CTL_PORT PORTB
#define CTL_DDR DDRB
#define RS_PIN PORTB0
#define RW_PIN PORTB1
#define E_PIN PORTB2

int cur_pos = 0;

void lcd_Init(){
	CTL_DDR = (1 << E_PIN) | (1 << RS_PIN) | (1 << RW_PIN);
	_delay_ms(20);
	hd_cmd(0x38); //8-bit mode, 2 lines, 5*8 fronts
	hd_cmd(0x0F); // display ON, cursor ON, blink ON
	//hd_cmd(0x06);//increase cursor possition
	cur_home();
	lcd_clear();
}

void hd_write(uint8_t data, uint8_t is_data){
	if (is_data)
	CTL_PORT |= (1 << RS_PIN);
	else
	CTL_PORT &= ~(1 << RS_PIN);
	
	CTL_PORT &= ~(1 << RW_PIN);
	CTL_PORT |= ( 1 << E_PIN);
	DATA_DDR = 0xFF;
	DATA_PORT = data;
	_delay_ms(1);
	CTL_PORT &= ~(1 << E_PIN);
	DATA_DDR = 0x00;
	_delay_ms(15);
}
void hd_cmd(uint8_t cmd){
	hd_write(cmd, 0);
}

void hd_data(uint8_t data){
	hd_write(data, 1);
	cur_pos++;
}
/*

void lcd_clear(){
	hd_cmd(0x01);
}


void cur_home(){
	hd_cmd(0x02);
	cur_pos = 0;
}

void lcd_print(uint8_t *data_array){
	for(int i = 0; data_array[i] != 0; i++){
		if(cur_pos == 15) cur_scdline();
		if(cur_pos == 31) cur_home();
		hd_data(data_array[i]);
	}
}

void cur_move(int steps){
	for (int i = 0; i<steps; i++){
		if(cur_pos == 15) cur_scdline();
		if(cur_pos == 31) cur_home();
		hd_cmd(0x14);
		cur_pos++;
	}
}

void cur_scdline(){
	hd_cmd(0xC0);
}

void my_char(uint8_t* data){
	hd_cmd(0x48); //переключились в CGRAM 0x01
	lcd_print(data);
	hd_cmd(0x80);//переключаемся в DDRAM
	hd_data(0x01);
	cur_pos = 0;
}



