#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0_init(void);
void Timer0_setCounter(unsigned int val);
unsigned int Timer0_getCounter();
void Timer0_run(unsigned char flag);

#endif