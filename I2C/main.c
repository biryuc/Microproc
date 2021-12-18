#define F_CPU 16000000UL

#include <avr/io.h>
#include "util/delay.h"
#include "i2c_eeprom.h"
#include "SPI.h"
int main(void)
{
	DDRA = 0xFF;
	//DDRB =0xFF;
	
	uint8_t byte[10]={0xAA,7,8,5};
	uint16_t address = 0;
	uint8_t res[10];
	//Настраиваем TWI
	eeInit();
	
	if(eeWriteByte(address, byte))
	{

		
		_delay_ms(15);
		
		eeReadByte(address,res);
		
		PORTA= res[0];
		
		}else{
			
		PORTA=3;
	}
	
	//Sendto7219(0x01,1);
}
