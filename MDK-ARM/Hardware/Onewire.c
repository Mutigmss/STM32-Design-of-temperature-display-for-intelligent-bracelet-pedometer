#include "gpio.h"
#include "tim.h"
void OneWire_DQ(uint8_t BitValue)//
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,BitValue);
	
}
unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char AckBit;
	OneWire_DQ(1);
	OneWire_DQ(0);
	delay_us(500);	//Delay 500us
	OneWire_DQ(1);
	delay_us(70);			//Delay 70us
	AckBit=HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	delay_us(500);			//Delay 500us
	return AckBit;
}

/**
  * @brief  ???????
  * @param  Bit ?????
  * @retval ?
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ(0);
	delay_us(10);		//Delay 10us
	OneWire_DQ(Bit);
	delay_us(50);			//Delay 50us
	OneWire_DQ(1);
}

/**
  * @brief  ???????
  * @param  ?
  * @retval ????
  */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ(0);
	delay_us(5);		//Delay 5us
	OneWire_DQ(1);
	delay_us(5);			//Delay 5us
	Bit=HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	delay_us(50);			//Delay 50us
	return Bit;
}

/**
  * @brief  ?????????
  * @param  Byte ??????
  * @retval ?
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}

/**
  * @brief  ?????????
  * @param  ?
  * @retval ???????
  */
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);}
	}
	return Byte;
}
