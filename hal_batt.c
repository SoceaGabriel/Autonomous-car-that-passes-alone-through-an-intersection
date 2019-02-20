#include "hal_batt.h"

T_F16 batteryLevel()
{
	T_F16 level=0; //valoarea citita din registru ADC in binar
	T_F16 Vcit=0; //tensiunea citita analogica
	T_F16 Vbatt=0; //tensiunea totala a bateriei
	T_F16 Diferenta=0;
	T_F16 Resolution=0;
	T_F16 ChargeIntervalMax=0,ChargeIntervalMin=0; 
	T_F16 VoltageIntervalMax=0,VoltageIntervalMin=0;
	T_F16 aux=0;
	T_F16 charge=0;
	
	
	ADC_vInit();
	level = ADC_u16Read(0);
	Vcit = (level*Vref)/Vmax;
	Vbatt = Vcit*4;
	// = Tens_max_batt - Vbatt;
	//
	if(Vbatt>=7 && Vbatt<=8.4)
	{
		ChargeIntervalMax=8.4;
		ChargeIntervalMin=7;
		VoltageIntervalMax=100;
		VoltageIntervalMin=20;
	}
	else if(Vbatt>=6.5 && Vbatt<=7)
	{
		ChargeIntervalMax=7;
		ChargeIntervalMin=6.5;
		VoltageIntervalMax=20;
		VoltageIntervalMin=10;
	}
	else if(Vbatt>=6 && Vbatt<=6.5)
	{
		ChargeIntervalMax=6.5;
		ChargeIntervalMin=6;
		VoltageIntervalMax=10;
		VoltageIntervalMin=0;
	}
	
	Diferenta=ChargeIntervalMax-Vbatt;
	Resolution=(ChargeIntervalMax-ChargeIntervalMin)/(VoltageIntervalMax-VoltageIntervalMin);
	aux=Diferenta*Resolution;
	
	charge=100-aux;
	return charge;
}