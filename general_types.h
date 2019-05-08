/* 
 * File:   general_types.h
 * Author: Cristian T. A.
 *
 * Created on August 1, 2018, 11:13 AM
 */

#ifndef GENERAL_TYPES_H
#define	GENERAL_TYPES_H

typedef unsigned char   T_U8;
typedef  char           T_S8;
typedef unsigned short  T_U16;
typedef short           T_S16;
typedef float           T_F16;
typedef enum _BOOL{FALSE=0, TRUE=1, UNDEFINED=2} BOOL; 

typedef struct carInfo
{
    T_U8 ID;
    T_U8 POZ;
    T_U8 DRUM;
    T_U8 R_I;
    BOOL alocat;
}carInfo; 

//Automatul de stari ale aplicatiei
typedef enum AutomatStari {DETECTARE_DRUM, PARCURGERE_L, ALEGERE_DRUM, INTERSECTIE, FINAL_DRUM} stari;

#endif	/* GENERAL_TYPES_H */

