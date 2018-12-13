#include "general.h"
#include "ASW.h"
 

void Aplication()
{
	int i;
	T_U8 u8Dir=INAINTE;
	T_U8 u8Speed=0;
	T_U16 lf;

	lf=RTE_LF_u8ReadPins();
	if(lf==0)
	{
		RTE_vServoSetAngle(90);
		u8Speed=0;
		u8Dir=INAINTE;
		RTE_vSetMotorSpeed(u8Speed);
		RTE_vSetMotorDir(u8Dir);
	}
	else
	{
		RTE_vServoSetAngle(90);
		u8Speed=30;
		u8Dir=INAINTE;
		RTE_vSetMotorSpeed(u8Speed);
		RTE_vSetMotorDir(u8Dir);
		if(lf==0b111000)
		{
			for(i=60;i<=120;i++)
			{
				RTE_vServoSetAngle(i);
				__delay_ms(80);
				u8Speed=25;
				u8Dir=INAINTE;
				RTE_vSetMotorSpeed(u8Speed);
				RTE_vSetMotorDir(u8Dir);
			}
		}
		else if(lf==0b000111)
		{
				for(i=120;i>=60;i--)
			{
				RTE_vServoSetAngle(i);
				__delay_ms(80);
				u8Speed=25;
				u8Dir=INAINTE;
				RTE_vSetMotorSpeed(u8Speed);
				RTE_vSetMotorDir(u8Dir);
			}
		}
	}
}