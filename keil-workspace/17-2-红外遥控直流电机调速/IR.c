#include <REGX52.H>
#include "Int0.h"
#include "Timer0.h"

unsigned int IR_time;
unsigned char IR_state;

unsigned char IR_data[4];
unsigned char IR_dataIndex;

unsigned char IR_dataFlag;
unsigned char IR_repeatFlag;
unsigned char IR_address;
unsigned char IR_command;

void IR_init()
{
	// 初始化定时器0
	Timer0_init();
	// 初始化外部中断
	Int0_init();
}

/**
  * @brief  红外遥控获取收到数据帧标志位
  * @param  无
  * @retval 是否收到数据帧，1为收到，0为未收到
  */
unsigned char IR_getDataFlag(void)
{
	if (IR_dataFlag) 
	{
		IR_dataFlag = 0;
		return 1;
	}
	return 0;
}

/**
  * @brief  红外遥控获取收到连发帧标志位
  * @param  无
  * @retval 是否收到连发帧，1为收到，0为未收到
  */
unsigned char IR_getRepeatFlag(void)
{
	if (IR_repeatFlag) 
	{
		IR_repeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IR_getAddress(void)
{
	return IR_address;
}

unsigned char IR_getCommand(void)
{
	return IR_command;
}

// //外部中断0中断函数，下降沿触发执行
void Int0_Routine(void) interrupt 0
{
	if (IR_state == 0) 				// 状态0，空闲状态
	{
		Timer0_setCounter(0);		// 定时计数器清0
		Timer0_run(1);					// 定时器启动
		IR_state = 1;						// 状态置为1
	}
	else if (IR_state == 1) 	// 状态1，等待start信号或repeat信号
	{
		IR_time = Timer0_getCounter(); 	// 获取上一次中断到此次中断的时间
		Timer0_setCounter(0);						// 定时计数器清0
		
		// 如果计时为13.5ms，则接收到了Start信号（判定值在12MHz晶振下为13500，在11.0592MHz晶振下为12442）
		if (IR_time > 12442-500 && IR_time < 12442+500)
		{
			IR_state = 2;					// 状态置为2
		}
		// 如果计时为11.25ms，则接收到了Repeat信号（判定值在12MHz晶振下为11250，在11.0592MHz晶振下为10368）
		else if (IR_time > 10368-500 && IR_time < 10368+500)
		{
			IR_repeatFlag = 1;		// 重复发送标志 置为1;
			Timer0_run(0);				// 定时器停止
			IR_state = 0;					// 状态置为0
		}
		else										// 其他情况（没有出现上面两种情况）
		{
			IR_state = 1;					// 状态置为0
		}
	}
	else if (IR_state == 2) 	// 状态2，接收数据， 一共4个字节的数据
	{
		IR_time = Timer0_getCounter(); 	// 获取上一次中断到此次中断的时间
		Timer0_setCounter(0);						// 定时计数器清0
		// 如果计时为1120us，则接收到了数据0（判定值在12MHz晶振下为1120，在11.0592MHz晶振下为1032）
		if (IR_time > 1032-500 && IR_time < 1032+500)
		{
			IR_data[IR_dataIndex/8] &= ~(0x01<<(IR_dataIndex%8));		// 对应位置设置为0
			IR_dataIndex++;
		}
		// 如果计时为2250us，则接收到了数据1（判定值在12MHz晶振下为2250，在11.0592MHz晶振下为2074）
		else if(IR_time > 2074-500 && IR_time < 2074+500)
		{
			IR_data[IR_dataIndex/8] |= (0x01<<(IR_dataIndex%8));		// 对应位置设置为1
			IR_dataIndex++;
		}
		else 										// 其他情况（没有出现上面两种情况） 接收出错
		{
			IR_dataIndex = 0;			// 数据位置指针清0
			IR_state = 1;					// 状态置为1
		}
		
		
		if (IR_dataIndex >= 32)	//如果接收到了32位数据
		{
			
			IR_dataIndex = 0;
			if ((IR_data[0] == ~IR_data[1]) && (IR_data[2] == ~IR_data[3]))	// 进行数据验证
			{
				IR_address = IR_data[0];	//存储数据
				IR_command = IR_data[2];
				IR_dataFlag = 1;					//设置数据标志位为1，表示拿到数据
			}
			Timer0_run(0);				// 定时器停止
			IR_state = 0;					// 状态置为0
		}
	}
}












