#include"asw_functions.h"
#include "general.h"
#include "general_types.h"
#include "RTE.h"
#include "mcal_interrupts.h"
#include "hal_encoder.h" 
#include "hal_motor.h"
#include "asw_com.h"
#include "hal_batt.h"
#include "ASW.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

T_U8 flag_culoare=0, bDrumDetectat=0; //variabile folosite in functia de determinare drum
T_U16 setSpeed=0; //variabila care retine viteza random a unei masini
T_U8 bParcurs=0; //variabila care este setata pe 1 atunci cand s-a terimat starea 2
T_U8 id=0; //pe ce drum se afla masina (0,1,2 sau 3)
T_U8 poz=0; //a cata masina a ajuns in intersectie (0,1,2 sau 3)
T_U8 flag_intersectie=0; //flagul care seteaza daca toti bitii sunt 1
T_U8 count_drt=0, flag_drt=0, fl_for_drt=0;
T_U8 count_stg=0, flag_stg=0, fl_for_stg=0;
T_U8 cont_int=0; //variabila care contorizeaza nr de intersectii de linii
carInfo carInf[4]; //instanta a structurii care contine informatiile despre masini
T_U8 vectAccident[4];
T_S16 valEncoder=0;
extern T_U8 drum; //drumul pe care trebuie sa mearga (stanga, dreapta sau inainte)
extern stari procesare; //variabila care contine starea aplicatiei la momentul curent
extern BOOL bObstDetected;

/*Pasul 0 - generare viteza random si setare viteza*/
T_U16 generareViteza()
{
    T_S16 rndd = QEI_s16getElapsed();
    T_U16 speed = (rndd % 20) +10;
    return speed;
}

void setareViteza()
{
   setSpeed=generareViteza();
   RTE_vSetMotorSpeed(setSpeed);
}

/*Pasul 0.1 - Detectare obstacole*/
void detectObstacole()
{
    if(bObstDetected==TRUE)
    {
        RTE_vSetMotorSpeed(0);
    }
    else
    {
        RTE_vSetMotorSpeed(setSpeed);
    }
}

/*Pasul 1 - Aflam pe ce drum suntem*/
void determinareDrum()
{   
    T_U8 lf=RTE_LF_u8ReadPins();
    if((lf!=0b111111) && (bDrumDetectat==0))
    {
         if((lf==0b000000) && (flag_culoare==0))
         {
            id++;
            flag_culoare=1;
         }
         else if(lf!=0b000000)
         {
            flag_culoare=0;
         }
         
    }
    else
    {
        bDrumDetectat=1;
        procesare = PARCURGERE_L;
    }
}

/*Pasul 2 - Parcurgere linie perpendiculara pe drum*/
void parcLinieP()
{
    
     T_U8 lf;
     lf=RTE_LF_u8ReadPins();
    if((lf==0b111111) && (bParcurs==0))
    {
        bParcurs=0;
    }
    else
    {
        bParcurs=1;
        procesare=ALEGERE_DRUM;
    }
}

/*Pasul 3.1 - Verificare nivel baterie*/
void verificareNivelBaterie()
{
    T_F16 nivel=batteryLevel();
    if(nivel<70)
    {
        RTE_vSetMotorSpeed(0);
    }
}

/*Pasul 3.2 - Determinare ordine in intersectie*/
void initializareStructAlocat()
{
    int i;
    //initializare structura: alocat
    for(i=0;i<4;i++)
    {
        carInf[i].alocat=FALSE;
    }
    
    //initializare vector de accidente
    for(i=0;i<=4;i++)
    {
        vectAccident[i]=0;
    }
}

/*Functie de determinare a ordinii in tintersectie si de setare a elementelor structurii cu indexul curent*/
void determinareOrdineInIntersectie()
{
    T_U8 lf=RTE_LF_u8ReadPins();
    int i;
    static int ok=0;
    if(lf==0b111111)
    {
        for(i=0;i<=3;i++)
        {
            if(carInf[i].alocat==FALSE && ok==0)
            {
                carInf[i].alocat=TRUE;
                carInf[i].POZ=i;
                carInf[i].ID=id;
                carInf[i].DRUM=drum;
                carInf[i].R_I=0;
                poz=i;
                ok=1;
            }
        }
    }
}

/*Pasul 3.3 - Generate directie de mers*/
void generareDirectieDeMers()
{
     T_S16 rndd = QEI_s16getElapsed();
     drum = rndd%2;
}

/*Pasul 3.4 - Trimitere mesaj*/
T_U8 continutMesaj(T_U8 ID,T_U8 POZ, T_U8 DRUM, T_U8 R_I)
{
    T_U8 u8Message = 0;    
    u8Message = (R_I<<7) | (DRUM<<5) | (POZ<<2) | ID;
    
    return u8Message;
}

void trimitereMesaj()
{
    T_U8 i=carInf[poz].ID;
    T_U8 d=carInf[poz].DRUM;
    T_U8 r=carInf[poz].R_I;
    T_U8 mesaj=continutMesaj(i,poz,d,r);
    COM_vSendMessage(mesaj);
}

/*Pasul 3.5 - cazuri accidente*/
T_U8 determinarePozitie2Masini(T_U8 ID_1,T_U8 ID_2)
{
    if(abs(ID_1-ID_2)==1) return 1; //returneaza 1 atunci cand masinile sunt perpendiculare una fata de alta
    else if(abs(ID_1-ID_2)==2) return 2; //returneaza 2 atunci cand masinile sunt paralele una fata de alta
    else return 0;
}

BOOL cazParalelAccident(T_U8 DRUM_1,T_U8 DRUM_2)
{
    if((DRUM_1==DIR_STANGA &&(DRUM_2==DIR_INAINTE || DRUM_2==DIR_DREAPTA)) || (DRUM_1==DIR_STANGA &&(DRUM_2==DIR_INAINTE || DRUM_2==DIR_DREAPTA)))
        return TRUE;
    else return FALSE;
}
BOOL cazPerpendicularAccident(T_U8 DRUM_1,T_U8 DRUM_2)
{
    if((DRUM_2==DIR_INAINTE && (DRUM_1==DIR_INAINTE || DRUM_1==DIR_STANGA || DRUM_1==DIR_DREAPTA)) || (DRUM_2==DIR_STANGA && (DRUM_1==DIR_INAINTE || DRUM_1==DIR_STANGA)))
        return TRUE;
    else return FALSE;
}

BOOL determinareCazuriAccident(T_U8 ID_1,T_U8 ID_2,T_U8 DRUM_1,T_U8 DRUM_2)
{
    T_U8 pozMasini=determinarePozitie2Masini(ID_1,ID_2);
    BOOL accident=FALSE;
    switch(pozMasini)
    {
        case 1: accident=cazPerpendicularAccident(DRUM_1,DRUM_2);
            break;
        case 2: accident=cazParalelAccident(DRUM_1,DRUM_2);
            break;
    }
    return accident;
}

/*trebuie apelat in sys_tasks.c*/
void setareVectorAccidente()
{
    int i;
    for(i=0;i<=poz-1;i++)
    {
        if(determinareCazuriAccident(carInf[i].ID, id, carInf[i].DRUM, drum)==TRUE)
        {
            vectAccident[i]=1;
        }
        if(vectAccident[i]==1 && carInf[poz].R_I==1)
        {
            vectAccident[i]=0;
        }
    }
}

BOOL existaAccidente()
{
    T_U8 i, exista=0;
    for(i=0;i<4;i++)
    {
        if(vectAccident[i]==1)
        {
            exista=1;
        }
    }
    if(exista==1) return TRUE;
    else return FALSE;
}

/*Pasul 3.6 - Stabilire daca masina sta pe loc sau isi continua drumul*/
void continuareDrum()
{
    if(existaAccidente()==TRUE)
    {
        RTE_vSetMotorSpeed(0);
    }
    else
    {
        RTE_vSetMotorSpeed(setSpeed);
        procesare=INTERSECTIE;
    }
}

/*Pasul 4.1 - Cazul DIR_INAINTE */
T_U8 numarareBiti(T_U8 lf)
{
    T_U8 nr=0;
    while(lf)
    {
        if(lf%2==1) nr++;
        lf/=2;
    }
    return nr;
}

void parcIntersectieInainte()
{
    T_U8 nr_cifre_lf=0; //variabila care numara bitii de 1 returnati de LF
    T_U8 lf=0;
    T_U8 i;
    if(cont_int<5)  
    {
        lf=RTE_LF_u8ReadPins();
        nr_cifre_lf=numarareBiti(lf);
        if(nr_cifre_lf==2 || nr_cifre_lf==3)
        {
            //ne asiguram ca masinutele merg drept, pe linie
            if(lf==0b000111 || lf==0b000011 || lf==0b000001)
            {
                for(i=90;i<95;i++)
                {
                    RTE_vServoSetAngle(i);
                    __delay_ms(20);
                }
                RTE_vServoSetAngle(90);
            }
            if(lf==0b111000 || lf==0b110000 || lf==0b100000)
            {
                for(i=90;i>85;i--)
                {
                    RTE_vServoSetAngle(i);
                    __delay_ms(20);
                }
                RTE_vServoSetAngle(90);
            }
        }
        if((nr_cifre_lf==6) && (flag_intersectie==0))
        {
            cont_int++;
            flag_intersectie=1;
        }
        else if(nr_cifre_lf!=6)
        {
            flag_intersectie=0;
        }
        
    }
    else
    {
        procesare=FINAL_DRUM;
    }
    
}

/*Pasul 4.2 - Cazul DIR_DREAPTA*/
T_U8 numarareBitiContinuitate(T_U8 lf)
{
    T_U8 nr1=0,ok=0;
    while(lf)
    {
        if(lf%2==1) nr1++;    //110111  100111 111001 110111 111011 110011    110  10101
        else if((lf%2==0) && (nr1>0) && (lf/2%2==1)) ok=1;
        lf/=2;
    }
    if(ok==1)return 0;
    return nr1;
}

void parcIntersectieDreapta()
{
    T_U8 lf=RTE_LF_u8ReadPins();
    int i;
    //verificare daca masinuta a terminat de parcurs curba
    if(count_drt<2)
    {
        //numara de 2 ori pana sa termine de parcurs curba
        if((numarareBitiContinuitate(lf)>3) && (flag_drt==0))
        {
            count_drt++;
            flag_drt=1;
        }
        else if(numarareBitiContinuitate(lf)<=3)
        {
            flag_drt=0;
        }
        //ne asiguram ca masinuta vireaza dreapta
        if(fl_for_drt==0)
        {
            for(i=90;i<100;i++) 
            {
                RTE_vServoSetAngle(i);
                __delay_ms(80);
            }
            fl_for_drt=1;
            RTE_vServoSetAngle(90);
        }
        //verificam ca masinuta sa urmareasca curba
        if(lf==0b000111 || lf==0b000011 || lf==0b000001)
        {
            for(i=90;i<100;i++)
            {
                RTE_vServoSetAngle(i);
                __delay_ms(20);
            }
            RTE_vServoSetAngle(90);
        }
        if(lf==0b111000 || lf==0b110000 || lf==0b100000)
        {
            for(i=90;i>80;i--)
            {
                RTE_vServoSetAngle(i);
                __delay_ms(20);
            }
            RTE_vServoSetAngle(90);
        }
        
    }
    else
    {
        procesare=FINAL_DRUM;
    }
   
}

/*Pasul 4.2 - Cazul DIR_STANGA*/
void parcIntersectieStanga()
{
    T_U8 lf=RTE_LF_u8ReadPins();
    T_U8 nr_cifre_lf=numarareBiti(lf);
    T_U8 i;
    
    if(count_stg<4)
    {
        //ne asiguram ca masinuta vireaza stanga
        if(fl_for_stg==0)
        {
            for(i=90;i<100;i++) 
            {
                RTE_vServoSetAngle(i);
                __delay_ms(80);
            }
            fl_for_stg=1;
            RTE_vServoSetAngle(90);
        }
        
        //cand lf are toti bitii de 1 (6 biti de 1) atunci se incrementeaza count_stg o singura data
        if((nr_cifre_lf==6) && (flag_stg==0))
        {
            count_stg++;
            flag_stg=1;
        }
        else if(nr_cifre_lf!=6)
        {
            flag_stg=0;
        }
        //verificam ca masinuta sa urmareasca curba
        if(nr_cifre_lf==2 || nr_cifre_lf==3)
        {
            if(lf==0b000111 || lf==0b000011 || lf==0b000001)
            {
                for(i=90;i<100;i++)
                {
                    RTE_vServoSetAngle(i);
                    __delay_ms(20);
                }
                RTE_vServoSetAngle(90);
            }
            if(lf==0b111000 || lf==0b110000 || lf==0b100000)
            {
                for(i=90;i>80;i--)
                {
                    RTE_vServoSetAngle(i);
                    __delay_ms(20);
                }
                RTE_vServoSetAngle(90);
            }
        }
    }
    else
    {
        procesare=FINAL_DRUM;
    }
}

/*Pasul 4. - Parcurgere intersectie*/
void parcIntersectie()
{
    switch(drum)
    {
        case DIR_INAINTE:
            parcIntersectieInainte();
            break;
        case DIR_DREAPTA:
            parcIntersectieDreapta();
            break;
        case DIR_STANGA:
            parcIntersectieStanga();
            break;
    }
}

/*Pasul 5 - Finalizare traiectorie*/
void finalDrum()
{
    T_U8 lf=0, nr_cifre_lf=0;
    int i;
    T_S16 val = QEI_s16getElapsed();
    valEncoder += val;
    if(valEncoder<2000)
    {
        lf=RTE_LF_u8ReadPins();
        nr_cifre_lf=numarareBiti(lf);
        if(nr_cifre_lf==2 || nr_cifre_lf==3)
        {
            //ne asiguram ca masinutele merg drept, pe linie
            if(lf==0b000111 || lf==0b000011 || lf==0b000001)
            {
                for(i=90;i<95;i++)
                {
                    RTE_vServoSetAngle(i);
                    __delay_ms(20);
                }
                RTE_vServoSetAngle(90);
            }
            if(lf==0b111000 || lf==0b110000 || lf==0b100000)
            {
                for(i=90;i>85;i--)
                {
                    RTE_vServoSetAngle(i);
                    __delay_ms(20);
                }
                RTE_vServoSetAngle(90);
            }
        }
    }
    else
    {
        RTE_vSetMotorSpeed(0);
        carInf[poz].R_I=1;
    }
}