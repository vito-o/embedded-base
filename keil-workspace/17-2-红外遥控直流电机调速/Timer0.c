#include <REGX52.H>

void Timer0_init(void)
{	
	//设置定时器模式，
	// 在前4位不变的情况下，改变后四位	
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	//在初始化时，TF0的状态可能不确定，可能是以下两种情况：
	//  随机值： 如果定时器之前被使用过，TF0可能已经被置1。
	//  误触发： 如果程序启用了定时器中断功能，而TF0为1，会立刻触发一次中断。
	//为了避免这些问题，初始化时手动将TF0清零是良好的编程习惯。这样可以确保：
	TF0 = 0; //溢出中断标致
	TR0 = 0; //为0时， 停止time0计数
	
	TH0 = 0;
	TL0 = 0;
}

/**
  * @brief  定时器0设置计数器值
  * @param  Value，要设置的计数器值，范围：0~65535
  * @retval 无
  */
void Timer0_setCounter(unsigned int val)
{
	TH0 = val/256;
	TL0 = val%256;
}

/**
  * @brief  定时器0获取计数器值
  * @param  无
  * @retval 计数器值，范围：0~65535
  */
unsigned int Timer0_getCounter()
{
	return (TH0<<8)|TL0;
}

/**
  * @brief  定时器0启动停止控制
  * @param  Flag 启动停止标志，1为启动，0为停止
  * @retval 无
  */
void Timer0_run(unsigned char flag)
{
	TR0 = flag;
}