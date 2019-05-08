#include "hal_line_follower.h"

void LF_vSetPinsDir (BOOL bDir)
{
	int i;
	for(i=0;i<=5;i++)
	{
		GPIO_u8SetPortPin(PORT_C,i,DIGITAL,bDir);
	}

}
void LF_vWritePins(void)
{
	int i;
	LF_vSetPinsDir(OUTPUT);
	for(i=0;i<=5;i++)
	{
		GPIO_u8WritePortPin(PORT_C,i,1);
	}
}
T_U8 LF_u8ReadPins(void)
{
	T_U8 val=0;
	T_U8 mask=0b111111;
	LF_vWritePins();
	__delay_us(10);
	LF_vSetPinsDir(INPUT);
	__delay_us(250);
	val=GPIO_u16ReadPort(PORT_C);
	val=val & mask;
	return val;
}