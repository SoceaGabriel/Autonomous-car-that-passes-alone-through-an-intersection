#include "general.h"
#include "general_types.h"
#include "hal_encoder.h"
#include "ASW.h"
#include "mcal_interrupts.h"
 
/*
void Aplication()
{
	int i;
	T_U8 u8Dir=INAINTE;
	T_U8 u8Speed=0;
	T_U16 lf;

	lf=RTE_LF_u8ReadPins();
	if(lf==0b000000)
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
		if(lf==0b111000) //partea dreapta
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
		else if(lf==0b000111) //partea stanga
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
        //else if()
	}
}
 */


void Faza_1()
{
    //Faza 1
    //In faza 1 masinuta trebuie sa mearga in linie dreapta pana cand detecteaza a doua oara toti bitii de 1 (adica a doua banda pusa perpendicular pe drum) si apoi sa se opreasca
	T_U8 u8Dir=INAINTE;
	T_U8 u8Speed=30;
	T_U16 lf;
    T_U16 var=0;
    int i,ok=0;
    
    RTE_vServoSetAngle(90); //setare unghi servomotor
    while(var<=2)
    {
        RTE_vSetMotorSpeed(u8Speed);
		RTE_vSetMotorDir(u8Dir);
        lf=RTE_LF_u8ReadPins();
        if(lf==0b111111 && var==0) //daca a detectat prima banda neagra perpendiculara pe banda principala
        {
            while(lf==0b111111) // parcurge banda pusa perpendicular
            {
                var=1;
            }
        }
        
        if(lf==0b111111 && var==1) //daca a detectat a doua banda neagra perpendiculara pe banda principala
        {
            while(lf==0b111111) //parcurge banda pusa perpendicular
            {
                var=2;
            }
            var=3; //iese din while
            u8Speed=0;
        }
        
        if(var==1 && ok==0) //dupa ce a trecut de prima banda pusa perpendicular
        {
            for(i=30;i>=25;i--) //scade viteza
            {
                RTE_vSetMotorSpeed(u8Speed); 
                __delay_ms(150);
            }
            ok=1;        
        }
        
    }
}

void Faza_2()
{
    //In faza a doua masinuta trebuie sa parcurga curba la dreapta 
    T_U8 u8Dir=INAINTE;
	T_U8 u8Speed=25;
	T_U16 lf;
    T_U16 ok=0;
    T_U16 i;
    RTE_vSetMotorSpeed(u8Speed);
	RTE_vSetMotorDir(u8Dir);
    
    RTE_vServoSetAngle(100); //inclina rotile spre dreapta cu 10 grade si le tine inclinate 1 sec ca sa faca curba spre dreapta
    __delay_ms(1000);
    RTE_vServoSetAngle(90);
    while(ok==0)
    {
        lf=RTE_LF_u8ReadPins();
        T_U16 x=90;
        if(lf<=0b001110)
        {
            while(lf!=0b011100)
            {
                for(i=x;i<=x+5;i++)
                {
                    RTE_vServoSetAngle(i);
                    __delay_ms(10);
                }
                x+=5;
            }
            
        }
        
        if(lf>=0b111000)
        {
            while(lf!=0b011100)
            {
                for(i=x;i<=x-5;i++)
                {
                    RTE_vServoSetAngle(i);
                    __delay_ms(10);
                }
                x=x-5;
            }
        }
        
        if(x==90)
        {
            ok=1;
        }
    }
}

void Faza_3()
{
    //In faza a  treia dupa ce masina a parcurs curba si rotile sunt drepte, trebuie sa mai parcurga inca 20 cm si sa se opreasca
    T_S16 encoder_result = QEI_s16getElapsed();//retinem valoarea encoderului
    T_S16 val=0;
    T_U8 u8Dir=INAINTE;
	T_U8 u8Speed=25;
    
    RTE_vServoSetAngle(90);
    val+=32000-encoder_result;
    while(val<2000)
    {
        RTE_vSetMotorSpeed(u8Speed);
        RTE_vSetMotorDir(u8Dir);
        encoder_result = QEI_s16getElapsed();
        val+=32000-encoder_result;
        if(val>=2000)
        {
            u8Speed=0;
        }
    }
}


void Aplication()
{
    Faza_1();
    Faza_2();
    Faza_3();
}


/*
void Aplication_Obstacol()
{
	T_U8 u8Dir=INAINTE;
    RTE_vSetMotorDir(u8Dir);
    RTE_vServoSetAngle(90);
	T_U8 u8Speed=0;
    
    if(get_FlagObst()==FALSE)
    { 
        u8Speed=30;
        RTE_vSetMotorSpeed(u8Speed);
    }
    else
    {
        u8Speed=0;
        RTE_vSetMotorSpeed(u8Speed);
    }    
}
*/