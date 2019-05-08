#include "general.h"
#include "mcal_init.h"
#include "hal_motor.h"
#include "hal_servo.h"
#include "hal_line_follower.h"
#include "sys_schedule.h"
#include "sys_tasks.h"

// FICD
#pragma config ICS = PGD2               // Comm Channel Select (Communicate on PGC2/EMUC2 and PGD2/EMUD2)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG is Enabled)

#include <xc.h>

int main()
{
	TASK_Inits();
	TASK_vSchedule();
    
    return 0;
}  