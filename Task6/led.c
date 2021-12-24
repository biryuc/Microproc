#include "led.h"

int dg = 8;

void SPI_init(void)
{
	DDRB |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(0<<SPI_MISO);
	PORTB |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(1<<SPI_MISO);
	SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(1<<SPR1)|(0<<SPR0);//¬ключили модуль SPI, передача старшим битом впреед, ћастер(мк), SPI Mode 0,
}

void SPI_WriteByte(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));//‘лаг прерывани€ от SPI, устанавливаетс€ в 1 по окончании передачи байта данных.
}

uint8_t SPI_ReadByte(uint8_t data)
{
	uint8_t report;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	report = SPDR;
	return report;
}


void Sendto7219(uint8_t rg, uint8_t dt)
{
	PORTB &= ~(1<<SPI_SS);//опускаем ножку SS дл€ выбора микросхемы, затем передаем байт с адресом регистра, затем байт данных
	SPI_WriteByte(rg);
	SPI_WriteByte(dt);
	PORTB |= (1<<SPI_SS);
}

void SendtoTwo7219(uint8_t rg1, uint8_t dt1, uint8_t rg2, uint8_t dt2){
	PORTB &= ~(1<<SPI_SS);
	SPI_WriteByte(rg1);
	SPI_WriteByte(dt1);
	SPI_WriteByte(rg2);
	SPI_WriteByte(dt2);
	PORTB |= (1<<SPI_SS);
}

void led_init_two(void){
	 SPI_init();
	
	SendtoTwo7219(0x0B, dg - 1,0x0B, dg - 1); //сколько разр€дов используем
	SendtoTwo7219(0x0A, 0x05,0x0A, 0x05); //€ркость
	SendtoTwo7219(0x09,0xFF, 0x09, 0x00);//режим декодировани€ + nondecode
	SendtoTwo7219(0x0C, 1,0x0C, 1); //включим индикатор
}

void led_init(){
	
	 SPI_init();	
	
	Sendto7219(0x0B, dg - 1); //сколько разр€дов используем
	Sendto7219(0x0A, 0x05); //€ркость
	Sendto7219(0x09, 0x00);//режим декодировани€ + nondecode
	Sendto7219(0x0C, 1); //включим индикатор
}
