#include <avr/io.h>
#include <util/delay.h>
#ifndef BUTTON_MATRIX_H_
#define BUTTON_MATRIX_H_

#define COL_SHIFT 4
#define COL_MASK (0b111 << COL_SHIFT)
#define ROW_SHIFT 0
#define ROW_MASK (0b1111 << ROW_SHIFT)
#define BTN(C, R) (1 << ((2 - C) * 4 + R))


void btn_init();
uint16_t btn_scan();


#endif /* BUTTON_MATRIX_H_ */