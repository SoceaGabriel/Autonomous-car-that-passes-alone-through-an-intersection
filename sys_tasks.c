/* 
 * File:   sys_tasks.h
 * Author: Cristian T. A.
 *
 * Created on August 17, 2018, 1:26 PM
 */

#include "general.h"
#include "sys_tasks.h"

#include "mcal_init.h"
#include "hal_servo.h"
#include "hal_motor.h"
#include "ASW.h"
#include "encoder.h"
#include "asw_com.h"
#include "asw_functions.h"
T_S16 deplasare;
T_U8 drum=0; //drumul pe care trebuie sa mearga (stanga, dreapta sau inainte)

void TASK_Inits()
{
	RTE_vMotorInit();
    MCAL_vInit();
    GPIO_u8SetPortPin(PORT_A, 10, DIGITAL, OUTPUT);	
    setareViteza();
	RTE_vSetMotorDir(INAINTE);
    RTE_vServoSetAngle(90);
    initializareStructAlocat();
    generareDirectieDeMers();
}

void TASK_1ms()
{
	
}

void TASK_5ms()
{
    
}

void TASK_10ms()
{   
   trimitereMesaj(); //trimiterea unui mesaj catre celelalte masini
   Aplicatie_Intersectie();  //aplicatia propriu zisa
}

void TASK_100ms()
{ 
    setareVectorAccidente(); //se pune 1 la indexul masininii cu care masina care executa codul se ciocneste
    COM_vProcessFIFO(); //procesarea mesajelor primite de la celelalte masini
    detectObstacole(); // functia de detectare de obstacole si oprire in caz de obstacol
}

void TASK_500ms()
{ 
    verificareNivelBaterie(); //masina se opreste daca nivelul bateriei e prea scazut
}

void TASK_1000ms()
{
	
}