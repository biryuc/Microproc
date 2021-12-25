#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "i2c_eeprom.h"
#define slaveF_SCL 400000
#define F_CPU 8000000UL
//TWBR = (F_CPU/slaveF_SCL - 16)/2;
void Init_I2C(void)
{
	TWBR = 10; 
	TWSR &= (~((1<<TWPS1)|(1<<TWPS0))); 
}

uint8_t WriteByte_I2C(uint16_t address,uint8_t ArrayBytes[10])
{
	do  
	{ 
		TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); 
		while(!(TWCR & (1<<TWINT))); 
		if((TWSR & 0xF8) != TW_START) 
		return 0;
		TWDR = 0b10100000; 
		TWCR=(1<<TWINT)|(1<<TWEN); 
		while(!(TWCR & (1<<TWINT))); 
	}while((TWSR & 0xF8) != TW_MT_SLA_ACK); 
	
	//Передача адреса записи
	TWDR=(address>>8); 
	TWCR=(1<<TWINT)|(1<<TWEN); 
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != TW_MT_DATA_ACK) return 0;
	
	//Для младшего разряда адреса
	TWDR=(address);
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != TW_MT_DATA_ACK) return 0;
	
	for(int i=0;ArrayBytes[i]!='\0';i++)
	{
		TWDR=(ArrayBytes[i]);
		TWCR=(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		if((TWSR & 0xF8) != TW_MT_DATA_ACK)
		return 0;
	}
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(TWCR & (1<<TWSTO)); 
	return 1;
}

uint8_t ReadByte_I2C(uint16_t address,uint8_t *data)
{
	
	do
	{
		TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		if((TWSR & 0xF8) != TW_START) return 0;
		TWDR = 0b10100000;
		TWCR=(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
	}while((TWSR & 0xF8) != TW_MT_SLA_ACK);
	
	//передача адреса чтения
	TWDR=(address>>8);
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != TW_MT_DATA_ACK)
	return 0;
	
	//Для младшего разряда адреса
	TWDR=(address);
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != TW_MT_DATA_ACK)
	return 0;
	
	/*****ПЕРЕХОД В РЕЖИМ ЧТЕНИЯ********/
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != TW_REP_START)
	return 0;
	
	/*Записываем адрес ведомого (7 бит) и бит чтения (1)*/
	TWDR = 0b10100001;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != TW_MR_SLA_ACK)
	return 0;

	for(int a=0; a!=10; a++)
		{
			if (a==9)
			{
				TWCR=(1<<TWINT)|(1<<TWEN);
				while(!(TWCR & (1<<TWINT)));
				if((TWSR & 0xF8) != TW_MR_DATA_NACK) return 0;
				data[a]=TWDR;
				TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
				while(TWCR & (1<<TWSTO));
				break;
			}
			
			TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
			while(!(TWCR & (1<<TWINT)));
			data[a]=TWDR;
			if( ((TWSR & 0xF8) != TW_MR_DATA_NACK) ) return 0;
			//if( ((TWSR & 0xF8) != 0x50) ) return 0;
		}
	return 1;
}
