#include <avr/io.h>
#include <util/delay.h>

#ifndef LED_H_
#define LED_H_

#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SCK 7
#define SPI_SS 4


extern int dg;

void SPI_init(void);
void SPI_WriteByte(uint8_t data);
uint8_t SPI_ReadByte(uint8_t data);
void Sendto7219(uint8_t rg, uint8_t dt);
void SendtoTwo7219(uint8_t rg1, uint8_t dt1, uint8_t rg2, uint8_t dt2);
void led_init();
void led_init_two(void);


#endif /* LED_H_ */