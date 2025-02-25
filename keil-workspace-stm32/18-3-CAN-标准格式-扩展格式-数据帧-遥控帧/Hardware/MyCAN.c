#include "MyCAN.h"

/*引脚初始化*/
void MyCAN_Init(void)
{	
	// 开启引脚时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 开启can时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	// 引脚配置
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// CAN_RX PA11
	// 在空闲时，CAN_H和CAN_L的电平是相等的，并且都接近于2.5V。这时，CAN_RX引脚处于高阻状态，内部的上拉电阻确保引脚处于合理的逻辑电平状态，以防止引脚浮空。
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				// 高速CAN CAN输入信号
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// CAN_TX PA12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// 内部外设信号输出，所以AF_PP
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 配置CAN_Init
	// 波特率 = APB1时钟频率 / 分频系数 / 一位的Tq数量
  //         = 36MHz / (BRP[9:0]+1) / (1 + (TS1[3:0]+1) + (TS2[2:0]+1))
	// 这里设置的波特率为125K，高速can的最低波特率
	CAN_InitTypeDef CAN_InitStructure;
	CAN_InitStructure.CAN_Prescaler = 48;
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;		// 测试模式， 环回静默模式：用于热自测试，自测的同时不会影响CAN总线
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_2tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
	CAN_InitStructure.CAN_TTCM = DISABLE; // 置1，开启时间触发通信功能；置0，关闭时间触发通信功能
	CAN_InitStructure.CAN_ABOM = DISABLE; // 置1，开启离线自动恢复，进入离线状态后，就自动开启恢复过程；置0，关闭离线自动恢复，软件必须先请求进入然后再退出初始化模式，随后恢复过程才被开启			
	CAN_InitStructure.CAN_AWUM = DISABLE;	// 置0，手动唤醒，软件清零SLEEP，唤醒CAN外设
	CAN_InitStructure.CAN_NART = DISABLE; // 置1，关闭自动重传 	置0，自动重传
	CAN_InitStructure.CAN_RFLM = DISABLE;	// 置1，接收FIFO锁定，FIFO溢出时，新收到的报文会被丢弃；置0，禁用FIFO锁定，FIFO溢出时，FIFO中最后收到的报文被新报文覆盖
	CAN_InitStructure.CAN_TXFP = DISABLE; // 置1，优先级由发送请求的顺序来决定，先请求的先发送；置0，优先级由报文标识符来决定，标识符值小的先发送
	CAN_Init(CAN1, &CAN_InitStructure);
	
	// 配置CAN过滤器
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;	// 接收所有信息，不进行过滤
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;//队列选择
	CAN_FilterInitStructure.CAN_FilterNumber = 0;		//过滤器选择
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		// 屏蔽模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	// 32位
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;						// 开启过滤器
	CAN_FilterInit(&CAN_FilterInitStructure);
}

// 发送
void MyCAN_Transmit(CanTxMsg *TxMessage)
{
	uint32_t Timeout = 0;
	uint8_t TransmitMailbox = CAN_Transmit(CAN1, TxMessage);
	while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CAN_TxStatus_Ok)
	{
		Timeout++;
		if (Timeout > 100000)
		{
			break;
		}
	}
}

// 判断是否接收
uint8_t MyCAN_ReceiveFlag(void)
{
	if (CAN_MessagePending(CAN1, CAN_FIFO0) > 0)
	{
		return 1;
	}
	return 0;
}

void MyCAN_Receive(CanRxMsg *RxMessage)
{
	CAN_Receive(CAN1, CAN_FIFO0, RxMessage);
}

