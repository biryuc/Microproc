/*
 * Display.h
 *
 * Created: 23.12.2021 14:25:41
 *  Author: Никита
 */ 
/*

#ifndef DISPLAY_H_
#define DISPLAY_H_

void lcd_Init();
void hd_write(uint8_t data, uint8_t is_data);
void hd_cmd(uint8_t cmd);
void hd_data(uint8_t data);
void lcd_clear();
void cur_home();
void lcd_print(uint8_t *data_array);
void cur_move(int steps);
void cur_scdline();
void hd_wait();
void my_char(uint8_t* data);
void lcd_print(uint8_t *data_array);
//void my_char1(uint8_t* data1,uint8_t* data2 );



#endif /* DISPLAY_H_ */