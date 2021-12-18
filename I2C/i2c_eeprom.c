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
	if(TWBR < 10) TWBR = 10; // � ������� ������ TWBR ������ ���� ������ 10
	TWSR &= (~((1<<TWPS1)|(1<<TWPS0))); // ������������ = 1
}

uint8_t eeWriteByte(uint16_t address,uint8_t ArrayBytes[10])
{
	do   //������� ������(���� ����� SCL SDA - ������� �������) ������ �������� - SDA � ������
	{ 
		TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // ���������� ���� ����������, ������������� ��� ����� � ���������� ������ TWI
		while(!(TWCR & (1<<TWINT))); // �������� ����� ������, ���� ������������
		if((TWSR & 0xF8) != 0x08) // �������� 5 ����. ����� �������� ������� (0x08 - ������� �������)
		return 0;
		TWDR = 0b10100000; //1010 - const part of address, 000 - we have only one 24lc64, 0 - we'll write into
		TWCR=(1<<TWINT)|(1<<TWEN); // want to transm data
		while(!(TWCR & (1<<TWINT))); //w8 for end of transm
	}while((TWSR & 0xF8) != 0x18); // ���� ������������� �� ������(�������� ����� � ����� � ������)
	//�������� ������ ������
	TWDR=(address>>8); //����� 16��������
	TWCR=(1<<TWINT)|(1<<TWEN); //�������� ����� ������
	while(!(TWCR & (1<<TWINT))); //��������� ����� ������
	if((TWSR & 0xF8) != 0x28) return 0;//���� ������������� ������ ������(0x28)
	//����� ���� ����� ��� �������� ������� ������
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
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//���������� ����
	while(TWCR & (1<<TWSTO)); //���� ���� ���� �����������
	return 1;
}

uint8_t eeReadByte(uint16_t address,uint8_t *data)
{
	//��������� �����
	do
	{
		TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		if((TWSR & 0xF8) != 0x08) return 0;
		TWDR = 0b10100000;
		TWCR=(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
	}while((TWSR & 0xF8) != 0x18);
	//�������� ������ ������
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
	/*****������� � ����� ������********/
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x10)//��������� ������( ������� ������� ������ ��������)
	return 0;
	/*���������� ����� �������� (7 �����) � � ����� ��� ������ (1)*/
	TWDR = 0b10100001;//1010 - const part of address, 000 - we have only one 24lc64, 0 - we'll write from (slave address)
	TWCR=(1<<TWINT)|(1<<TWEN);//����������
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & 0xF8) != 0x40)//��������� ������� �� ����� � ����� ������� � ����� �� �� �������� �� ������
	return 0;
	/*****��������� ���� ������********/
	/*
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//�������� ����� ������(������� TWINT), ���� ��������� � TWDR
	while(!(TWCR & (1<<TWINT)));//���� ��������� ������..
	*data++=TWDR;
	if( ((TWSR & 0xF8) != 0x50) ) return 0;//��������� ������. (������� ������ ������ � �� ������� �������������)
	TWCR=(1<<TWINT)|(1<<TWEN);//�������� ����� ������(������� TWINT), ���� ��������� � TWDR
	while(!(TWCR & (1<<TWINT)));//���� ��������� ������..
	if((TWSR & 0xF8) != 0x58) return 0;//��������� ������. (������� ������ ������ � �� ������� �������������)
	*data=TWDR;
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//������������� ������� ���������� �������� ������ (����)
	while(TWCR & (1<<TWSTO));    //���� ��������� ������� ����
//	*/
	for(int a=0; a!=10; a++)
		{
			if (a==9)
			{
				TWCR=(1<<TWINT)|(1<<TWEN);//�������� ����� ������(������� TWINT), ���� ��������� � TWDR
				while(!(TWCR & (1<<TWINT)));//���� ��������� ������..
				if((TWSR & 0xF8) != 0x58) return 0;//��������� ������. (������� ������ ������ � �� ������� �������������)
				data[a]=TWDR;
				TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//������������� ������� ���������� �������� ������ (����)
				while(TWCR & (1<<TWSTO));//���� ��������� ������� ����  
				break;
			}
			TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//�������� ����� ������(������� TWINT), ���� ��������� � TWDR
			while(!(TWCR & (1<<TWINT)));//���� ��������� ������..
			data[a]=TWDR;
			if( ((TWSR & 0xF8) != 0x50) ) return 0;//��������� ������. (������� ������ ������ � �� ������� �������������)
		}
	return 1;
}
