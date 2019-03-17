#include "general.h"
#include "mcal_init.h"
#include "hal_motor.h"
#include "hal_servo.h"
#include "hal_line_follower.h"
#include "sys_schedule.h"
#include "sys_tasks.h"

// FICD
#pragma config ICS = PGD2               // Comm Channel Select (Communicate on PGC2/EMUC2 and PGD2/EMUD2)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG is Enabled)

#include <xc.h>

int main()
{
	TASK_Inits();
	TASK_vSchedule();
	//initializari
	/*
	T_U8 u8Dir=INAINTE;
	T_U8 u8Speed=0;
    
	*/

	//DC Motor
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


	//ServoMotor
	/*
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
	*/

	//Line Follower
	/*
	u8Speed=0;
	u8Dir=INAINTE;
	T_U16 lf;
	while(1)
	{
		lf=LF_u8ReadPins();
		if(lf==1)
		{
			u8Speed=30;
			u8Dir=INAINTE;
			vSetMotorSpeed(u8Speed);
			vSetMotorDir(u8Dir);
		}
		else
		{
			u8Speed=30;
			u8Dir=INAPOI;
			vSetMotorSpeed(u8Speed);
			vSetMotorDir(u8Dir);
		}
	}
	*/
	
    return 0;
}  