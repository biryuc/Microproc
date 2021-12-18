#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SCK 7
#define SPI_SS 4
char dg = 8;

void SPI_init(void)
{
	DDRB |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(0<<SPI_MISO);
	PORTB |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(1<<SPI_MISO);
	SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR1)|(1<<SPR0);//Включил модуль SPI, передача старшим битом впреед, Мастер(мк), SPI Mode 0,
}
//  Передача одного байта данных по SPI
void SPI_SendByte(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));//Флаг прерывания от SPI, устанавливается в 1 по окончании передачи байта данных.
}
//Передача и прием одного байта данных по SPI
/*uint8_t SPI_ReadByte(uint8_t data)
{
	uint8_t report;
	PORTB &= ~(1<<SPI_SS);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	report = SPDR;
	PORTB |= (1<<SPI_SS); 
	return report;
}*/


void Sendto7219(uint8_t rg, uint8_t dt)
{
	PORTB &= ~(1<<SPI_SS);//опускаем ножку SS для выбора микросхемы, затем передаем байт с адресом регистра, затем байт данных
	SPI_SendByte(rg);
	SPI_SendByte(dt);
	PORTB |= (1<<SPI_SS);
}

void Clear_7219(void)
{
	char i = dg;
	do {
		Sendto7219(i, 0xF); //CHAR BLANK
	} while (--i);
}

uint8_t data[8] = {
	0b11101101,
	0b00010010,
	0b00001100,
	0b00010010,
	0b11101101,
	0b00010010,
	0b00001100,
	0b00010010
};

void init7219(void){
	Sendto7219(0x09, 0xFF);
	Sendto7219(0x0B, dg - 1); //сколько разрядов используем
	Sendto7219(0x0A,  0x02); //яркость
	Sendto7219(0x0C, 1); //включим индикатор
}

/*int main(void)
{
	//int helper;
	SPI_init();
	Sendto7219(0x09, 0xFF); 
	Sendto7219(0x0B, dg - 1); //сколько разрядов используем
	Sendto7219(0x0A,  0x02); //яркость
	Sendto7219(0x0C, 1); //включим индикатор
	
	Sendto7219(0x01, 1);
	Sendto7219(0x02, 2);
	Sendto7219(0x03, 3);
	Sendto7219(0x04, 4);
	Sendto7219(0x05, 5);
	Sendto7219(0x06, 6);
	Sendto7219(0x07, 7);
	//Sendto7219(0x08, 8);
	//Clear_7219();
	
}*/