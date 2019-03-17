#include "encoder.h"
#include "mcal_encoder.h"

T_S16 QEI_s16getElapsed(void)
{
    T_S16 deplasare;
    deplasare=32000-QEI_u16getCount();
    QEI_vResetCount();
    return deplasare;
}

