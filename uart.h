#ifndef UART_H_
#define UART_H_

#include "USB_config/descriptors.h"


// Enable/disable UART Bridge
// Comment definition for disabling the channel
#define UART0_INTFNUM 0
#if CDC_NUM_INTERFACES >= 2
#define UART1_INTFNUM 1
#endif

#if defined (__MSP430F6638__)
#define CLR_DTR0 P2OUT |= 0x04
#define SET_DTR0 P2OUT &= ~0x04
#define CLR_RTS0 P2OUT |= 0x08
#define SET_RTS0 P2OUT &= ~0x08
#define CLR_DTR1 P8OUT |= 0x01
#define SET_DTR1 P8OUT &= ~0x01
#define CLR_RTS1 P8OUT |= 0x02
#define SET_RTS1 P8OUT &= ~0x02
#endif

#if defined (__MSP430F5509__)
#define SET_DTR0 P4OUT |= 0x08
#define CLR_DTR0 P4OUT &= ~0x08
#define CLR_RTS0 {P4OUT |= 0x04 ;P2OUT &= ~0x01;}
#define SET_RTS0 {P4OUT &= ~0x04;P2OUT |= 0x01;}
#endif

#define RESET_HIGH {PJOUT |= BIT1;}
#define RESET_LOW  {PJOUT &= ~BIT1;}
#define TEST_HIGH  {PJOUT |= BIT2;}
#define TEST_LOW   {PJOUT &= ~BIT2;}
#define RESET_PIN BIT1
#define TEST_PIN  BIT2
#define TCK_PIN   BIT3

// Maximal host system delay
#define MAX_SYS_DELAY   20  // ms

// Size of Rx/Tx UART Buffers
// Value should be big enough to cover max system delay
#define RX_BUFFER_SIZE  1280            // max_baud * SYS_DELAY ms/1000/ 8bit          
#define TX_BUFFER_SIZE  MAX_PACKET_SIZE // Don't modyfy this value!!!

// Initialize UART
BYTE InitUart0(ULONG lBaudrate); 
BYTE InitUart1(ULONG lBaudrate);

// Transfers data from the UART buffer to USB_CDC.
BYTE UartToCdc(BYTE uartNum, BYTE cdcNum);

// Transfers data from the USB_CDC buffer to UART.
BYTE CdcToUart(BYTE cdcNum, BYTE uartNum);  

void newInvoke( BYTE invokeParam );
//#define INVOKE_DELAY 30000
#define INVOKE_DELAY 1000

#endif //UART_H_
