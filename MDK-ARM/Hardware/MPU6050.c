#include "main.h"
#include "gpio.h"
#include "IIC.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS		0xD0//从机地址+写位

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)//指定地址写寄存器
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);//指定寄存器地址
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);//写入指定寄存器下的数据
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}
uint8_t MPU6050_ReadReg(uint8_t RegAddress)//指定地址读
{
	uint8_t Data;
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();//指定一个寄存器
	
	MyI2C_Start();//重复起始条件
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);//将写位转换为读位
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);//如果需要继续发送数据（没发送一次数据地址就会自增），就需要一个应答，但此时只发送一个字节所以从机归还控制权，
	MyI2C_Stop();
	
	return Data;
}
void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);//接触睡眠
  MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);//6个轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);//采样分屏为10
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);//滤波参数最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}
uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
uint8_t DataH, DataL;
	//加速度值
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);//读取x轴高八位赋值给DateH
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;//将16位数据展现出来
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);//读取Y轴高八位赋值给DateH
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;//将16位数据展现出来,赋值给Y
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);//读取Z轴高八位赋值给DateH
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;//将16位数据展现出来
	//以下位陀螺仪
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}

