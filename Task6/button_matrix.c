#include "button_matrix.h"


void btn_init(){
	DDRD &= ~(COL_MASK | ROW_MASK);
	PORTD |= (COL_MASK | ROW_MASK);
	
}

uint16_t btn_scan(){
	uint16_t res = 0;
	for (uint8_t col = 0; col < 3; col++) {
		PORTD &= ~(1 << (col + COL_SHIFT));
		DDRD |= 1 << (col + COL_SHIFT);

		res <<= 4;
		res |= (~PIND & ROW_MASK) >> ROW_SHIFT;

		DDRD &= ~(COL_MASK);
		PORTD |= COL_MASK;
	}
	return res;
	
}