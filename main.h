// (c)2009 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example (CDC/HID Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: main.h, v1.18 2009/06/11                                           |
|  Author: RSTO                                                               |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
+----------------------------------------------------------------------------*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include "USB_API/USB_Common/device.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
Call all needed Init_...() functions.
  Needed Init_...() functions depends on build settings.
*/
  
// Macro definition
#define SetPinOut(px,py)  P##px##DIR |= (1<<py)
#define SetPinIn(px,py)   P##px##DIR &= ~(1<<py)
#define SetPin(px,py)     P##px##OUT |= (1<<py)
#define ClearPin(px, py)  P##px##OUT &= ~(1<<py)
#define TogglePin(px, py) P##px##OUT ^= (1<<py)

#define SelectPin(px,py)  P##px##SEL |= (1<<py)
#define ResetPin(px,py)   P##px##SEL &= ~(1<<py)
  
#define Delay(time)       \
{                         \
    ULONG count = time;   \
    while(--count);       \
}  

VOID BlinkLed(VOID);
  
#ifdef __cplusplus
}
#endif
#endif /* _MAIN_H_ */
/*------------------------ Nothing Below This Line --------------------------*/

