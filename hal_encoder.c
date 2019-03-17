
#include "hal_encoder.h"

T_S16 QEI_s16getElapsed()
{
    T_S16 result=0; //valoarea cititta din registru
    result=32000-QEI_u16getCount();
    QEI_vResetCount();
    return result;
}