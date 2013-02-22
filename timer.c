//******************************************************************************
// Filename:		timer.c
//
// Description:         Generates period for checking UART buffer and Task Queue
//					
//******************************************************************************

#include <MSP430.h>
#include "USB_API/USB_Common/types.h" 
#include "main.h"

#include "descriptors.h"
#include "uart.h"

//----------------------------------------------------------------------------
// TimerA2 Init 
VOID Init_TimerA2(VOID)
{
        TA2CCTL0 = CCIE;                        // CCR0 interrupt enabled
        TA2CTL = TASSEL_1 + TACLR;              // ACLK, clear TAR
        
        TA2CTL &= ~MC_1;                        // Turn off Timer                      
        TA2CCR0 = 33;              		// Set Timer Period = 1 ms
        TA2CTL |= MC_1;                         // Start Timer
}

//-----------------------------------------------------------------------------
// Timer1 A0 interrupt service routine
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR(void)
{
        #ifdef UART0_INTFNUM
            UartToCdc(UART0_INTFNUM, CDC0_INTFNUM);
        #endif
        #ifdef UART1_INTFNUM
            UartToCdc(UART1_INTFNUM, CDC1_INTFNUM);
        #endif

        //BlinkLed();
}

//==============================================================================
// End of file	 timer.c
//==============================================================================
