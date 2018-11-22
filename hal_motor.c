#include "mcal_pwm.h"
#include "mcal_gpio.h"
#include "general.h"
#include "hal_motor.h"

void vMotorInit(void)
{
	GPIO_u8SetPortPin(PORT_A,9,DIGITAL,INAINTE);
	PWM1_vInit();

}
void vSetMotorDir(BOOL u8Dir)
{
	GPIO_u8WritePortPin(PORT_A,9,u8Dir);
}
void vSetMotorSpeed(T_U8 u8Speed)
{
	if(u8Speed>100)
	{
		u8Speed=100;
	}
	PWM1_vSetDuty(u8Speed,2);
}
