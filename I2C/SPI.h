/*
 * SPI.h
 *
 * Created: 16.12.2021 12:06:41
 *  Author: Никита
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_init(void);
void SPI_SendByte(uint8_t data);
void Sendto7219(uint8_t rg, uint8_t dt);
void Clear_7219(void);
void init7219(void);



#endif /* SPI_H_ */