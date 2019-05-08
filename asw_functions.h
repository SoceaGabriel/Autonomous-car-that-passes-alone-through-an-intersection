/* 
 * File:   asw_functions.h
 * Author: Gabi Socea & Malina Buga
 * Created on March 27, 2019, 6:11 PM
 */
#include "general_types.h"
#ifndef ASW_FUNCTIONS_H
#define	ASW_FUNCTIONS_H
/*Pasul 0 - Generare viteza random si setare viteza*/
T_U16 generareViteza();
void setareViteza();

/*Pasul 0.1 - Detectare obstacole*/
void detectObstacole();

/*Pasul 1 - Aflam pe ce drum suntem*/
void determinareDrum();

/*Pasul 2 - Parcurgere linie perpendiculara pe drum*/
void parcLinieP();

/*Pasul 3.1 - Verificare nivel baterie*/
void verificareNivelBaterie();

/*Pasul 3.2 - Determinare ordine in intersectie*/
void initializareStructAlocat();
void determinareOrdineInIntersectie();

/*Pasul 3.3 - Generate directie de mers*/
void generareDirectieDeMers();

/*Pasul 3.4 - Trimitere mesaj*/
T_U8 continutMesaj(T_U8 ID,T_U8 POZ, T_U8 DRUM, T_U8 R_I);
void trimitereMesaj();

/*Pasul 3.5 - cazuri accidente*/
T_U8 determinarePozitie2Masini(T_U8 ID_1,T_U8 ID_2);
BOOL cazParalelAccident(T_U8 DRUM_1,T_U8 DRUM_2);
BOOL cazPerpendicularAccident(T_U8 DRUM_1,T_U8 DRUM_2);
BOOL determinareCazuriAccident(T_U8 ID_1,T_U8 ID_2,T_U8 DRUM_1,T_U8 DRUM_2);
void setareVectorAccidente();
BOOL existaAccidente();

/*Pasul 3.6 - Stabilire daca masina sta pe loc sau isi continua drumul*/
void continuareDrum();

/*Pasul 4.1 - Cazul DIR_INAINTE */
T_U8 numarareBiti(T_U8 lf);
void parcIntersectieInainte();

/*Pasul 4.2 - Cazul DIR_DREAPTA*/
T_U8 numarareBitiContinuitate(T_U8 lf);
void parcIntersectieDreapta();

/*Pasul 4.2 - Cazul DIR_STANGA*/
void parcIntersectieStanga();

/*Pasul 4.3 - Parcurgere intersectie*/
void parcIntersectie();

/*Pasul 5 - Finalizare traiectorie*/
void finalDrum();

#endif	/* ASW_FUNCTIONS_H */

