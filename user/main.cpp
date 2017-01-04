/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

//STM32 RUN IN eBox
#include "ebox.h"
#include "math.h"
#include "os.h"




// œµÕ≥≈‰÷√<<<<<<<<<<<<<<<<<<<<<<<<<
#define OS_TICKS_PER_SEC 1000




// »ŒŒÒœ‡πÿ<<<<<<<<<<<<<<<<<<<<<<<<<<
#define STARTUP_TASK_PRIO 5
#define STARTUP_TASK_STK_SIZE 256
static OS_TCB START_TASK_TCB;
static CPU_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		 
//°>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Pwm pwm1(&PB8);
float x;
uint16_t y;

void setup()
{
    ebox_init();
	  uart1.begin(115200);
    pwm1.begin(1000, 500);
    pwm1.set_oc_polarity(1);
    set_systick_user_event_per_sec(OS_TICKS_PER_SEC);
		// use OS_CPU_SysTickHandler in os_cpu_c.c
    attach_systick_user_event(OS_CPU_SysTickHandler);
}
void Task_LED(void *p_arg)
{
    (void)p_arg;                		// 'p_arg' ?????,?????????
		OS_ERR p_err;
    while (1)
    {
				x = x + PI * 0.01;
        if(x >= PI)x = 0;
        y = 2000 - (sin(x) + 1) * 1000;
        pwm1.set_duty(y);
        OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_DLY,&p_err);
			// BUG: printf ø’º‰≤ª◊„
			//uart1.printf("millis:%ld, CPU:%d\n", millis(), );
			//uart1.print("abcd");
    }
}
int main(void)
{
		OS_ERR err;
	
    setup();
    OSInit(&err);
    //OSTaskCreate(Task_LED, (void *)0,
    //           &startup_task_stk[STARTUP_TASK_STK_SIZE - 1], STARTUP_TASK_PRIO);
		
		OSTaskCreate (  (OS_TCB        *)&START_TASK_TCB,
                    (CPU_CHAR      *)"start_up_task",
                    (OS_TASK_PTR    )&Task_LED,
                    (void          *)NULL,
                    (int            )STARTUP_TASK_PRIO,
                    (CPU_STK       *)&startup_task_stk[STARTUP_TASK_STK_SIZE - 1],
                    (CPU_STK_SIZE   )STARTUP_TASK_STK_SIZE / 10,
                    (CPU_STK_SIZE   )STARTUP_TASK_STK_SIZE,
                    (OS_MSG_QTY     )0,
                    (OS_TICK        )0,
                    (void          *)NULL,
                    (OS_OPT         )OS_OPT_TASK_NONE,
                    (OS_ERR        *)&err);
										
    OSStart(&err);
										
    return 0;
}




