#include "general.h"
#include "hal_servo.h"

void vSetAngle(T_U8 u8Angle)
{
	if(u8Angle<60)
	{
		u8Angle=60;
	}
	if(u8Angle>120)
	{
		u8Angle=120;
	}
	T_F16 duty=OFFSET + GAIN*(u8Angle-MIN_ANGLE);
	PWM1_vSetDuty(duty,1);
}