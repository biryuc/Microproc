#include <avr/io.h>
#include <util/delay.h>

#ifndef LCD_H_
#define LCD_H_

#define DATA_PORT PORTA
#define DATA_DDR DDRA
#define DATA_PIN PINA

#define CTL_PORT PORTB
#define CTL_DDR DDRB
#define RS_PIN PORTB0
#define RW_PIN PORTB1
#define E_PIN PORTB2

//extern int cur_pos;

void HD_Init();
void lcd_clear();
void cur_home();
void hd_write(uint8_t data, uint8_t is_data);
void hd_cmd(uint8_t cmd);
void hd_data(uint8_t data);
void lcd_print(uint8_t *data_array);
void cur_move(int steps);
void my_char(uint8_t* data);
void cur_scdline();

#endif /* LCD_H_ */