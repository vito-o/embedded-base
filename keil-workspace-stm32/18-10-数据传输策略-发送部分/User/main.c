#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "MyCAN.h"
#include "Timer.h"

uint8_t key;

uint8_t TimingFlag;	//定时触发
uint8_t TriggerFlag;
uint8_t RequestFlag;
//CanTxMsg TxMsgArray[] = {
///*  标准id    扩展id   标准/扩展格式   数据/遥控帧 数据长度    数据            */
///*   StdId     ExtId         IDE             RTR        DLC         Data[8]          */
//		{0x555, 0x00000000, CAN_Id_Standard, CAN_RTR_Data,   4, {0x11, 0x22, 0x33, 0x44}},
//		{0x000, 0x12345678, CAN_Id_Extended, CAN_RTR_Data,   4, {0xAA, 0xBB, 0xCC, 0xDD}},
//		{0x666, 0x00000000, CAN_Id_Standard, CAN_RTR_Remote, 0, {0x00, 0x00, 0x00, 0x00}},
//		{0x000, 0x0789ABCD, CAN_Id_Extended, CAN_RTR_Remote, 0, {0x00, 0x00, 0x00, 0x00}},
//};
CanTxMsg TxMsg_Timing = {
	.StdId = 0x100,
	.ExtId = 0x00000000,
	.IDE = CAN_Id_Standard,
	.RTR = CAN_RTR_Data,
	.DLC = 4,
	.Data = {0x11, 0x22, 0x33, 0x44},
};
CanTxMsg TxMsg_Trigger = {
	.StdId = 0x200,
	.ExtId = 0x00000000,
	.IDE = CAN_Id_Standard,
	.RTR = CAN_RTR_Data,
	.DLC = 4,
	.Data = {0x11, 0x22, 0x33, 0x44}
};
CanTxMsg TxMsg_Request = {
	.StdId = 0x300,
	.ExtId = 0x00000000,
	.IDE = CAN_Id_Standard,
	.RTR = CAN_RTR_Data,
	.DLC = 4,
	.Data = {0x11, 0x22, 0x33, 0x44}
};

CanRxMsg RxMsg;

int main()
{
	Timer_init();
	OLED_Init();
	Key_init();
	MyCAN_Init();
	
	OLED_ShowString(1, 1, "Tx");
	OLED_ShowString(2, 1, "Tim:"); //定时触发
	OLED_ShowString(3, 1, "Tri:"); //手动触发
	OLED_ShowString(4, 1, "Req:"); //请求触发
	
	while(1)
	{
		// 按键触发， -手动触发
		key = getKey();
		if (key == 1)
		{
			TriggerFlag = 1;
		}
		
		// 定时发送
		if (TimingFlag == 1)
		{
			TimingFlag = 0;
			
			TxMsg_Timing.Data[0]++;
			TxMsg_Timing.Data[1]++;
			TxMsg_Timing.Data[2]++;
			TxMsg_Timing.Data[3]++;
			
			MyCAN_Transmit(&TxMsg_Timing);

			OLED_ShowHexNum(2, 6, 	TxMsg_Timing.Data[0], 2);
			OLED_ShowHexNum(2, 9, 	TxMsg_Timing.Data[1], 2);
			OLED_ShowHexNum(2, 12, 	TxMsg_Timing.Data[2], 2);
			OLED_ShowHexNum(2, 15, 	TxMsg_Timing.Data[3], 2);
		}
		
		// 触发发送
		if (TriggerFlag == 1) 
		{
			TriggerFlag = 0;
			
			TxMsg_Trigger.Data[0]++;
			TxMsg_Trigger.Data[1]++;
			TxMsg_Trigger.Data[2]++;
			TxMsg_Trigger.Data[3]++;
			
			MyCAN_Transmit(&TxMsg_Trigger);	
			
			OLED_ShowHexNum(3, 6, 	TxMsg_Trigger.Data[0], 2);
			OLED_ShowHexNum(3, 9, 	TxMsg_Trigger.Data[1], 2);
			OLED_ShowHexNum(3, 12, 	TxMsg_Trigger.Data[2], 2);
			OLED_ShowHexNum(3, 15, 	TxMsg_Trigger.Data[3], 2);
		}
		
		// 请求发送
		if (MyCAN_ReceiveFlag())
		{
			MyCAN_Receive(&RxMsg);
			
			if (RxMsg.IDE == CAN_Id_Standard && RxMsg.RTR == CAN_RTR_Remote && RxMsg.StdId == 0x300)
			{
				RequestFlag = 1;
			}
			if (RxMsg.IDE == CAN_Id_Standard && RxMsg.RTR == CAN_RTR_Data && RxMsg.StdId == 0x3FF)
			{
				RequestFlag = 1;
			}
		}
		
		if (RequestFlag == 1) 
		{
			RequestFlag = 0;
			
			TxMsg_Request.Data[0]++;
			TxMsg_Request.Data[1]++;
			TxMsg_Request.Data[2]++;
			TxMsg_Request.Data[3]++;
			
			MyCAN_Transmit(&TxMsg_Request);	
			
			OLED_ShowHexNum(4, 6, 	TxMsg_Request.Data[0], 2);
			OLED_ShowHexNum(4, 9, 	TxMsg_Request.Data[1], 2);
			OLED_ShowHexNum(4, 12, 	TxMsg_Request.Data[2], 2);
			OLED_ShowHexNum(4, 15, 	TxMsg_Request.Data[3], 2);
		}
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TimingFlag = 1;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

