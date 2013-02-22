// (c)2009 by Texas Instruments Incorporated, All Rights Reserved.
/*----------------------------------------------------------------------------+
|                                                                             |
|                              Texas Instruments                              |
|                                                                             |
|                          MSP430 USB-Example (CDC/HID Driver)                |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: types.h, File Version 1.00 2009/12/03                              |
|  Author: RSTO                                                               |
|                                                                             |
|  WHO          WHEN         WHAT                                             |
|  ---          ----------   ------------------------------------------------ |
|  RSTO         2008/09/03   born                                             |
|  RSTO         2009/07/17   Define __data16 for CCS                          |
|                                                                             |
+----------------------------------------------------------------------------*/
#ifndef _TYPES_H_
#define _TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __TI_COMPILER_VERSION__
#define __no_init
#define __data16
#endif

/*----------------------------------------------------------------------------+
| Include files                                                               |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Function Prototype                                                          |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Type Definition & Macro                                                     |
+----------------------------------------------------------------------------*/
typedef char            CHAR;
typedef unsigned char   UCHAR;
typedef int             INT;
typedef unsigned int    UINT;
typedef short           SHORT;
typedef unsigned short  USHORT;
typedef long            LONG;
typedef unsigned long   ULONG;
typedef unsigned long   HANDLE;
typedef char *          PSTR;
typedef int             BOOL;
typedef double          DOUBLE;
typedef unsigned char   BYTE;
typedef unsigned char*  PBYTE;
typedef unsigned int    WORD;
typedef unsigned int*   PWORD;
typedef unsigned long   DWORD;
typedef unsigned long*  PDWORD;

typedef void            VOID;
typedef void*           PVOID;

//----------------------------------------------------------------------------
typedef enum
{
    FALSE,
    TRUE
} tBOOL;

/*----------------------------------------------------------------------------+
| Constant Definition                                                         |
+----------------------------------------------------------------------------*/
#define NULL    (PVOID)0x0000

#define SUCCESS 0
#define FAILURE 1

/*----------------------------------------------------------------------------+
| End of header file                                                          |
+----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif /* _TYPES_H_ */
/*------------------------ Nothing Below This Line --------------------------*/
