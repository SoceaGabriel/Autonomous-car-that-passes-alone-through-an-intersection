#include "general.h"
#include "hal_motor.h"

int main()
{
	T_U8 u8Dir=INAINTE;
	T_U8 u8Speed=0;
    vMotorInit();
	while(1)
	{
		vSetMotorSpeed(u8Speed);
		vSetMotorDir(u8Dir);
		__delay_ms(1000);
		u8Speed+=10;
		if(u8Speed>=100)
		{
			u8Speed=0;
			u8Dir=INAPOI;
		}
	}
    return 0;
}  