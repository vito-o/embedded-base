#include "MPU6050.h"
#include "MPU6050_Reg.h"
#include "MyI2C.h"

#define MPU6050_ADDRESS  0xD0

// 往寄存器里面写
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

// 从寄存器里面读
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);	// 表示读操作
	MyI2C_ReceiveAck();
	uint8_t data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);												// 1表示给从机非应答，终止从机的数据输出
	
	MyI2C_Stop();
	
	return data;
}


void MPU6050_init(void)
{
	MyI2C_init();
	
	// MPU6050寄存器初始化， 需要对照MPU6050手册的寄存器的描述配置，此处仅配置了部分重要的寄存器
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01); 		// 电源管理寄存器1， 取消睡眠模式，选择时钟源为x轴陀螺仪
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00); 		// 电源管理寄存器2，保持默认值0，所有轴均不带及
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09); 		// 采样率分频寄存器，配置采样率
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06); 				// 配置寄存器， 配置DLPF
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);		// 陀螺仪配置寄存器，选择满量程为 ±2000°/s
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18); 	// 加速度计配置寄存器，选择满量程为±16g
}

// MPU6050获取ID号
uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(
	int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
	int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;								//定义数据高8位和低8位的变量
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);		//读取加速度计X轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);		//读取加速度计X轴的低8位数据
	*AccX = (DataH << 8) | DataL;											//数据拼接，通过输出参数返回
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);		//读取加速度计Y轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);		//读取加速度计Y轴的低8位数据
	*AccY = (DataH << 8) | DataL;											//数据拼接，通过输出参数返回
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);		//读取加速度计Z轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);		//读取加速度计Z轴的低8位数据
	*AccZ = (DataH << 8) | DataL;											//数据拼接，通过输出参数返回
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);			//读取陀螺仪X轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);			//读取陀螺仪X轴的低8位数据
	*GyroX = (DataH << 8) | DataL;										//数据拼接，通过输出参数返回
		
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);			//读取陀螺仪Y轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);			//读取陀螺仪Y轴的低8位数据
	*GyroY = (DataH << 8) | DataL;										//数据拼接，通过输出参数返回
		
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);			//读取陀螺仪Z轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);			//读取陀螺仪Z轴的低8位数据
	*GyroZ = (DataH << 8) | DataL;										//数据拼接，通过输出参数返回
}
