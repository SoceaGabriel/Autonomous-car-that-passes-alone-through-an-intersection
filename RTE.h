#ifndef _RTE_H_
#define _RTE_H_

#include "general.h"
#include "mcal_init.h"
#include "hal_motor.h"
#include "hal_servo.h"
#include "hal_line_follower.h"
#include "sys_schedule.h"




#define RTE_vMotorInit() vMotorInit()
#define RTE_vSetMotorDir(a) vSetMotorDir(a)
#define RTE_vSetMotorSpeed(a) vSetMotorSpeed(a)
#define RTE_vServoSetAngle(a) vSetAngle(a)
#define RTE_LF_vSetPinsDir (a) LF_vSetPinsDir (a)
#define RTE_LF_vWritePins() LF_vWritePins()
#define RTE_LF_u8ReadPins() LF_u8ReadPins()


#define RTE_RF_vCheckIRQ() RF_vCheckIRQ()
#define RTE_RF_vBeginTransmit(b) RF_vBeginTransmit(b)
#define RTE_RF_vBeginReceive() RF_vBeginReceive()
#endif