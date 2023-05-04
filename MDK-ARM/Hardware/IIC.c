#include "main.h"

void MyI2C_W_SCL(uint8_t BitValue)//写函数MyI2C_W_SCL(1/0)方便操作
{
	HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin,BitValue);
	
}

void MyI2C_W_SDA(uint8_t BitValue)
{
	HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin,BitValue);
	
}
uint8_t MyI2C_R_SDA(void)//读从机的值
{
	uint8_t BitValue;
	BitValue = HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin);

	return BitValue;//将读取的值返回
}



//初始化IIC
void MyI2C_Init(void)
{
	HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,GPIO_PIN_SET);

}
void MyI2C_Start(void)//IIC起始条件,SCL高电平期间，SDA从高电平切换到低电平

{
	MyI2C_W_SDA(1);//SDA放在前，可以让这个初始条件兼容重复初始条件
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);

}
void MyI2C_Stop(void)//IIC停止条件,SCL高电平期间，SDA从低电平切换到高电平
{
	MyI2C_W_SDA(0);//SDA放在前，可以让这个初始条件兼容重复初始条件
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);

}
//SCL低电平期间，主机将数据位依次放到SDA线（高位先行）、
//然后释放SCL，从机将在SCL高电平期间读取数据位
//所以SCL高电平期间SDA不允许有数据变化，依次循环上述过程8次，即可发送一个字节

void MyI2C_SendByte(uint16_t Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte & (0x80>>i));//从高到低依次将数据发送
		MyI2C_W_SCL(1);//读取数据
		MyI2C_W_SCL(0);
	}
}
uint8_t MyI2C_ReceiveByte(void)//接受数据
{
	uint8_t i, Byte = 0x00;
	for(i=0;i<8;i++)
	{
		MyI2C_W_SDA(1);//主机释放SDA
		for(i=0;i<8;i++)
		{
		MyI2C_W_SCL(1);//释放SCL主机读取从机的数据	
		if(MyI2C_R_SDA() == 1){(Byte|=(0x80>>i));}
		MyI2C_W_SCL(0);//sda在scl低电平期间送数
		}
	}
	return Byte;
}
void MyI2C_SendAck(uint8_t AckBit)//发送一个应答
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);//进入下一个时序单元
}

uint8_t MyI2C_ReceiveAck(void)//接受应答
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);//将SDA拉低
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);//进入下一个时序单元
	return AckBit;
}



