/*
 * Guess_the_figure.h
 *
 * Created: 12.12.2021 15:27:32
 *  Author: Никита
 */ 


#ifndef GUESS_THE_FIGURE_H_
#define GUESS_THE_FIGURE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <util/delay.h>

int Random_num();
//uint8_t Random_grid();
//Start_game(uint8_t *lcd_data1, uint8_t *SPI_data1);
void Clear_SPI();
void Draw(uint8_t *picture,int delay);
void Change_figure(int num,int delay);
//Change_data_display(int res);

void LCD_start(void);
void Change_figure_LCD(int count);
void Winner(void);
void Losing(void);
void LCD_figure(int count);
int Win(uint8_t *res,int rnd);
void SPI_show(int num,int delay);
void Start(int run_,int delay);
#endif /* GUESS_THE_FIGURE_H_ */