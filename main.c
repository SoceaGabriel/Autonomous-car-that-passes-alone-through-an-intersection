#include "general.h"
#include "mcal_init.h"
#include "hal_motor.h"
#include "hal_servo.h"
#include "sys_schedule.h"

int main()
{
	T_U8 u8Dir=INAINTE;
	T_U8 u8Speed=0;
    vMotorInit();
	TASK_Inits();
	//TASK_vSchedule();
	/*
	while(1)
	{
		vSetMotorSpeed(u8Speed);
		vSetMotorDir(u8Dir);
		__delay_ms(100);
		u8Speed+=10;
		if(u8Speed>=100)
		{
			u8Speed=0;
			u8Dir=INAPOI;
			
		}
	}
	*/
		int i,j;
		u8Speed=0;
		u8Dir=INAINTE;
		for(i=60;i<=120;i++)
		{
			u8Speed+=2;
			if(u8Speed>=10)
			{
				u8Speed=10;		
			}
			vSetMotorSpeed(u8Speed);
			vSetMotorDir(u8Dir);
			vSetAngle(i);
			__delay_ms(80);
		}
		u8Speed=0;
		u8Dir=INAPOI;
		for(j=120;j>=60;j--)
		{
			u8Speed+=2;
			if(u8Speed>=10)
			{
				u8Speed=10;		
			}
			vSetMotorSpeed(u8Speed);
			vSetMotorDir(u8Dir);
			vSetAngle(j);
			__delay_ms(80);
		}
		u8Speed=0;
		u8Dir=INAINTE;
		for(i=60;i<=120;i++)
		{
			u8Speed+=2;
			if(u8Speed>=10)
			{
				u8Speed=10;		
			}
			vSetMotorSpeed(u8Speed);
			vSetMotorDir(u8Dir);
			vSetAngle(i);
			__delay_ms(80);
		}
	while(1)
	{
		
	}

	
    return 0;
}  