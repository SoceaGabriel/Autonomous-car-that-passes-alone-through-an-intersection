#include "general.h"
#include "general_types.h"
#include "hal_encoder.h"
#include "ASW.h"
#include "mcal_interrupts.h"
#include "asw_functions.h"

stari procesare=DETECTARE_DRUM;

void Aplicatie_Intersectie()
{ 
    switch(procesare)
    {
        case DETECTARE_DRUM:
            determinareDrum();
            break;
            
        case PARCURGERE_L:
            parcLinieP();
            break;
            
        case ALEGERE_DRUM:
            determinareOrdineInIntersectie();
            continuareDrum();
            break;
            
        case INTERSECTIE:
            parcIntersectie();
            break;            
        case FINAL_DRUM:
            finalDrum();
            break;
    }
}