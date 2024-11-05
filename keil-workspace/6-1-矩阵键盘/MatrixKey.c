#include <REGX52.H>
#include "Delay.h"

unsigned char MatrixKey()
{
	unsigned char keyNumber = 0;
	//先列后行扫描
	
	P1   = 0xFF;
	P1_3 = 0; //第一列
	if (P1_7==0) {Delay(20);while(P1_7==0)Delay(20);keyNumber=1;}
	if (P1_6==0) {Delay(20);while(P1_6==0)Delay(20);keyNumber=5;}
	if (P1_5==0) {Delay(20);while(P1_5==0)Delay(20);keyNumber=9;}
	if (P1_4==0) {Delay(20);while(P1_4==0)Delay(20);keyNumber=13;}
	
	P1   = 0xFF;
	P1_2 = 0;	//第二列
	if (P1_7==0) {Delay(20);while(P1_7==0)Delay(20);keyNumber=2;}
	if (P1_6==0) {Delay(20);while(P1_6==0)Delay(20);keyNumber=6;}
	if (P1_5==0) {Delay(20);while(P1_5==0)Delay(20);keyNumber=10;}
	if (P1_4==0) {Delay(20);while(P1_4==0)Delay(20);keyNumber=14;}
	
	P1   = 0xFF;
	P1_1 = 0;	//第三列
	if (P1_7==0) {Delay(20);while(P1_7==0)Delay(20);keyNumber=3;}
	if (P1_6==0) {Delay(20);while(P1_6==0)Delay(20);keyNumber=7;}
	if (P1_5==0) {Delay(20);while(P1_5==0)Delay(20);keyNumber=11;}
	if (P1_4==0) {Delay(20);while(P1_4==0)Delay(20);keyNumber=15;}
	
	P1   = 0xFF;
	P1_0 = 0;	//第四列
	if (P1_7==0) {Delay(20);while(P1_7==0)Delay(20);keyNumber=4;}
	if (P1_6==0) {Delay(20);while(P1_6==0)Delay(20);keyNumber=8;}
	if (P1_5==0) {Delay(20);while(P1_5==0)Delay(20);keyNumber=12;}
	if (P1_4==0) {Delay(20);while(P1_4==0)Delay(20);keyNumber=16;}
	
	return keyNumber;
}