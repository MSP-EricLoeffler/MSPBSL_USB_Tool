#include <MSP430.h>
#include "USB_API/USB_Common/types.h"
#include "USB_API/USB_Common/device.h"
#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/usb.h"        // USB-specific functions
#include "USB_API/USB_CDC_API/UsbCdc.h"

#include "uart.h"

void Port_Mapping(void);

//----------------------------------------------------------------------------
VOID Init_Clock(VOID)
{
	#if defined (__MSP430F563x_F663x)
		while(BAKCTL & LOCKIO)                    // Unlock XT1 pins for operation
      	BAKCTL &= ~(LOCKIO);                    // enable XT1 pins
     	// Workaround for USB7
    	UCSCTL6 &= ~XT1OFF;
    #endif
    if (USB_PLL_XT == 2)
    {
    	#if defined (__MSP430F552x) || defined (__MSP430F550x)
        	P5SEL |= 0x0C;                        // enable XT2 pins for F5529
		#elif defined (__MSP430F563x_F663x)
			P7SEL |= 0x0C;
		#endif
        // Use the REFO oscillator to source the FLL and ACLK
        UCSCTL3 = (UCSCTL3 & ~(SELREF_7)) | (SELREF__REFOCLK);
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK);
        
        // MCLK will be driven by the FLL (not by XT2), referenced to the REFO
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768);  // Start the FLL, at the freq indicated by the config constant USB_MCLK_FREQ
        
        //XT2_Start(XT2DRIVE_3);                                        // Start the "USB crystal"
    }
    else
    {
    	#if defined (__MSP430F552x) || defined (__MSP430F550x)
        P5SEL |= 0x10;                    // enable XT1 pins
		#endif 
        // Use the REFO oscillator to source the FLL and ACLK
//        UCSCTL3 = SELREF__REFOCLK;             
//        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__REFOCLK); 
        
      	P5SEL |= 0x30;                        // enable XT1 pins for F5509
        LFXT_Start(XT1DRIVE_3);
        // Use the LFXT1 oscillator to source the FLL and ACLK
        UCSCTL3 = SELA__XT1CLK;             
        UCSCTL4 = (UCSCTL4 & ~(SELA_7)) | (SELA__XT1CLK); 

        
        // MCLK will be driven by the FLL (not by XT2), referenced to the REFO
        Init_FLL(USB_MCLK_FREQ/1000, USB_MCLK_FREQ/32768); // set FLL (DCOCLK)
        
        //XT1_Start(XT1DRIVE_3);                                       // Start the "USB crystal"
    }
}

//----------------------------------------------------------------------------
VOID Init_Ports(VOID)
{
    // Drive all I/O's as output-low, making sure there's no shoot-through current.  There 
    // should be no floating I/Os, to prevent unnecessary current draw during USB suspend.  
    PAOUT   =   0x0000;
    PASEL   =   0x0000;
    PAREN   =   0xF0FF;
    PADIR   =   0x0F00;

    PBOUT   =   0x0000;
    PBSEL   =   0x0000;
    PBREN   =   0xFFFF;

    PCOUT   =   0x0000;
    PCSEL   =   0x0000;
    PCREN   =   0xFFFF;

    #ifndef __MSP430F550x
    PDOUT   =   0x0000;      //	If using a device other than: 
    PDSEL   =   0x0000;	     //	F5510, F5529, F5638, or F6638 
    PDREN   =   0xF0FF;
    PDDIR   =   0xFFFF;      //	you may need to comment out these lines 
    #endif 

    
    #if defined (__MSP430F563x_F663x)
    P9OUT   =   0x00;
    P9SEL   =   0x00;
    P9REN   =   0xFF;
    #endif

    PJDIR   =   0xFFFF;
    PJOUT   =   0x0000;
    
    P1DIR |= 0x03;   // for LEDs
}



//----------------------------------------------------------------------------
VOID Init_StartUp(VOID)
{
    WDTCTL = WDTPW + WDTHOLD;	    // Stop watchdog timer

    __disable_interrupt();               // Disable global interrupts
    
    Init_Ports();                        // Init ports (do first ports because clocks do change ports)
    SetVCore(3);                         // USB core requires the VCore set to 1.8 volt, independ of CPU clock frequency
    Init_Clock();

    __enable_interrupt();                // enable global interrupts
    
    Port_Mapping();
    
    #ifdef UART0_INTFNUM
    InitUart0(9600);
    #endif
    
    #ifdef UART1_INTFNUM
    InitUart1(9600);
    #endif
}

//----------------------------------------------------------------------------
VOID ConfigUSB(VOID)
{
    USB_init();                     // Init USB

    // Enable various USB event handling routines

    USB_setEnabledEvents(kUSB_VbusOnEvent+kUSB_VbusOffEvent+kUSB_receiveCompletedEvent
                          +kUSB_dataReceivedEvent+kUSB_UsbSuspendEvent+kUSB_UsbResumeEvent+kUSB_UsbResetEvent);
    
    
    // See if we're already attached physically to USB, and if so, connect to it
    // Normally applications don't invoke the event handlers, but this is an exception.  
  
    if (USB_connectionInfo() & kUSB_vbusPresent)
    {
        if (USB_enable() == kUSB_succeed)
        {
            USB_reset();
            USB_connect();
        }
    }
	
}

//----------------------------------------------------------------------------
void Port_Mapping(void)
{
  // Disable Interrupts before altering Port Mapping registers
  __disable_interrupt();     
  // Enable Write-access to modify port mapping registers
  PMAPPWD = 0x02D52;                        
  
  #ifdef PORT_MAP_RECFG                    
  // Allow reconfiguration during runtime
  PMAPCTL = PMAPRECFG;                     
  #endif  
  
    #ifdef __MSP430F550x
  //P4MAP0 = PM_UCA0RXD;
  //P4MAP1 = PM_UCA0TXD;
  P4MAP4 = PM_UCA0TXD;
  P4MAP5 = PM_UCA0RXD;
  //P4MAP7 = PM_MCLK;
    #endif 
    #ifdef __MSP430F563x_F663x
  P2MAP0 = PM_UCA0TXD;
  P2MAP1 = PM_UCA0RXD;
    #endif 

  // Disable Write-Access to modify port mapping registers
  PMAPPWD = 0;                              
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}
//----------------------------------------------------------------------------
//End of file.
//----------------------------------------------------------------------------
