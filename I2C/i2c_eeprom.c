#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "i2c_eeprom.h"
#define slaveF_SCL 400000

void eeInit(void)
{
	TWBR = (F_CPU/slaveF_SCL - 16)/2;
	if(TWBR < 10) TWBR = 10; // В ведущем режиме TWBR должно быть больше 10
	TWSR &= (~((1<<TWPS1)|(1<<TWPS0))); // предделитель = 1
}

uint8_t eeWriteByte(uint16_t address,uint8_t ArrayBytes[10])
{
	do   //Условие начала(сост покоя SCL SDA - высокий уровень) Начало передачи - SDA в низкий
	{ 
		TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // Сбрасываем флаг прерывания, устанавливаем бит старт и разрешения реботы TWI
		while(!(TWCR & (1<<TWINT))); // Возможно линия занята, ждем освобождения
		if((TWSR & 0xF8) != 0x08) // Проверка 5 посл. битов регистра статуса (0x08 - условие статуса)
		return 0;
		TWDR = 0b10100000; //1010 - const part of address, 000 - we have only one 24lc64, 0 - we'll write into
		TWCR=(1<<TWINT)|(1<<TWEN); // want to transm data
		while(!(TWCR & (1<<TWINT))); //w8 for end of transm
	}while((TWSR & 0xF8) != 0x18); // Ждем подтверждения от слейва(проверил адрес и готов к записи)
	//передача адреса записи
	TWDR=(address>>8); //адрес 16тибитный
	TWCR=(1<<TWINT)|(1<<TWEN); //Передали адрес записи
	while(!(TWCR & (1<<TWINT))); //подождали конец записи
	if((TWSR & 0xF8) != 0x28) return 0;//Ждем подтверждения приема данных(0x28)
	//Далее тоже самое для младшего разряда адреса
	TWDR=(address);
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x28) return 0;
	for(int i=0;ArrayBytes[i]!='\0';i++)
	{
		TWDR=(ArrayBytes[i]);
		TWCR=(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		if((TWSR & 0xF8) != 0x28)
		return 0;
	}
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//Установили стоп
	while(TWCR & (1<<TWSTO)); //Ждем пока стоп установится
	return 1;
}

uint8_t eeReadByte(uint16_t address,uint8_t *data)
{
	//Установка связи
	do
	{
		TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		if((TWSR & 0xF8) != 0x08) return 0;
		TWDR = 0b10100000;
		TWCR=(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
	}while((TWSR & 0xF8) != 0x18);
	//передача адреса чтения
	TWDR=(address>>8);
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x28)
	return 0;
	TWDR=(address);
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x28)
	return 0;
	/*****ПЕРЕХОД В РЕЖИМ ЧТЕНИЯ********/
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x10)//Проверяем статус( условие повтора начала передачи)
	return 0;
	/*Записываем адрес ведомого (7 битов) и в конце бит чтения (1)*/
	TWDR = 0b10100001;//1010 - const part of address, 000 - we have only one 24lc64, 0 - we'll write from (slave address)
	TWCR=(1<<TWINT)|(1<<TWEN);//отправляем
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x40)//проверяем нашелся ли слейв с таким адресом и готов ли он работать на чтение
	return 0;
	/*****СЧИТЫВАЕМ БАЙТ ДАННЫХ********/
	/*
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//Начинаем прием данных(очищаем TWINT), байт запишется в TWDR
	while(!(TWCR & (1<<TWINT)));//Ждем окончания приема..
	*data++=TWDR;
	if( ((TWSR & 0xF8) != 0x50) ) return 0;//Проверяем статус. (Ведущий принял данные и не передал подтверждение)
	TWCR=(1<<TWINT)|(1<<TWEN);//Начинаем прием данных(очищаем TWINT), байт запишется в TWDR
	while(!(TWCR & (1<<TWINT)));//Ждем окончания приема..
	if((TWSR & 0xF8) != 0x58) return 0;//Проверяем статус. (Ведущий принял данные и не передал подтверждение)
	*data=TWDR;
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//Устанавливаем условие завершения передачи данных (СТОП)
	while(TWCR & (1<<TWSTO));    //Ждем установки условия СТОП
//	*/
	for(int a=0; a!=10; a++)
		{
			if (a==9)
			{
				TWCR=(1<<TWINT)|(1<<TWEN);//Начинаем прием данных(очищаем TWINT), байт запишется в TWDR
				while(!(TWCR & (1<<TWINT)));//Ждем окончания приема..
				if((TWSR & 0xF8) != 0x58) return 0;//Проверяем статус. (Ведущий принял данные и не передал подтверждение)
				data[a]=TWDR;
				TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//Устанавливаем условие завершения передачи данных (СТОП)
				while(TWCR & (1<<TWSTO));//Ждем установки условия СТОП  
				break;
			}
			TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//Начинаем прием данных(очищаем TWINT), байт запишется в TWDR
			while(!(TWCR & (1<<TWINT)));//Ждем окончания приема..
			data[a]=TWDR;
			if( ((TWSR & 0xF8) != 0x50) ) return 0;//Проверяем статус. (Ведущий принял данные и не передал подтверждение)
		}
	return 1;
}
