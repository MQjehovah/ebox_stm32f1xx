/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

//STM32 RUN IN eBox
#include "ebox.h"


uint32_t xx;

EXTIx ex(&PA8,EXTI_Trigger_Falling);//创建一个检测下降沿的外部中断对象

void exit()//中断调用用户事件
{
	xx++;
	uart1.printf("\r\nxx = %d",xx);
}
void setup()
{
	ebox_init();
	uart1.begin(9600);
	ex.begin();//初始化外部中断配置
	ex.attachInterrupt(exit);//绑定中断用户事件
	ex.interrupt(ENABLE);//开启中断
}


int main(void)
{
	setup();
	while(1)
	{
		;
	}


}




