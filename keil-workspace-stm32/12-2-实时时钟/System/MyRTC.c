#include "MyRTC.h"
#include <time.h>

uint16_t MyRTC_Time[] = {2023, 1, 1, 23, 59, 55};

void MyRTC_SetTime(void);

void MyRTC_init(void)
{
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	// 备份寄存器访问使能
	PWR_BackupAccessCmd(ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		RCC_LSEConfig(RCC_LSE_ON);		// 开启LSE时钟
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET); // 等待LSE准备就绪
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);						// 选择RTCCLK来源为lse
		RCC_RTCCLKCmd(ENABLE);														// RTCCLK使能
		
		RTC_WaitForSynchro();					// 等待同步
		RTC_WaitForLastTask();				// 等待上一次操作完成
		
		RTC_SetPrescaler(32768-1);		// 设置RTC预分频器，预分频后的计数频率为1HZ
		RTC_WaitForLastTask();				// 等待上一次操作完成
		
		
		MyRTC_SetTime();							// 设置时间，调用函数，将MyRTC_Time的值刷新到RTC硬件电路
		
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);	//在备份寄存器写入自己规定的标志位，用于判断RTC是不是第一次执行配置
	}	
	else
	{
		RTC_WaitForSynchro();					// 等待同步
		RTC_WaitForLastTask();				// 等待上一次操作完成
	}
	
}


void MyRTC_SetTime(void)
{
	time_t time_cnt;			//定义秒计数器数据类型
	struct tm time_date;	//定义日期时间数据类型
	
	time_date.tm_year = MyRTC_Time[0] - 1900;
	time_date.tm_mon = MyRTC_Time[1] - 1;
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_hour = MyRTC_Time[3];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_sec = MyRTC_Time[5];
	
	time_cnt = mktime(&time_date) - 8 * 60 * 60; 
	
	RTC_SetCounter(time_cnt);	// 将秒计数器写入到RTC的CNT中
	RTC_WaitForLastTask();		// 等待上一次操作完成
}

void MyRTC_ReadTime(void)
{
	time_t time_cnt;			//定义秒计数器数据类型
	struct tm time_date;	//定义日期时间数据类型
	
	time_cnt = RTC_GetCounter();
	time_date = *localtime(&time_cnt);
	
	MyRTC_Time[0] = time_date.tm_year + 1900;		//将日期时间结构体赋值给数组的时间
	MyRTC_Time[1] = time_date.tm_mon + 1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;
}

