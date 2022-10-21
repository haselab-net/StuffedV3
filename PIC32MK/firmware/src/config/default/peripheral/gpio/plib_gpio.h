/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for GPIO_RA7 pin ***/
#define GPIO_RA7_Set()               (LATASET = (1<<7))
#define GPIO_RA7_Clear()             (LATACLR = (1<<7))
#define GPIO_RA7_Toggle()            (LATAINV= (1<<7))
#define GPIO_RA7_OutputEnable()      (TRISACLR = (1<<7))
#define GPIO_RA7_InputEnable()       (TRISASET = (1<<7))
#define GPIO_RA7_Get()               ((PORTA >> 7) & 0x1)
#define GPIO_RA7_PIN                  GPIO_PIN_RA7

/*** Macros for GPIO_RB14 pin ***/
#define GPIO_RB14_Set()               (LATBSET = (1<<14))
#define GPIO_RB14_Clear()             (LATBCLR = (1<<14))
#define GPIO_RB14_Toggle()            (LATBINV= (1<<14))
#define GPIO_RB14_OutputEnable()      (TRISBCLR = (1<<14))
#define GPIO_RB14_InputEnable()       (TRISBSET = (1<<14))
#define GPIO_RB14_Get()               ((PORTB >> 14) & 0x1)
#define GPIO_RB14_PIN                  GPIO_PIN_RB14

/*** Macros for GPIO_RB15 pin ***/
#define GPIO_RB15_Set()               (LATBSET = (1<<15))
#define GPIO_RB15_Clear()             (LATBCLR = (1<<15))
#define GPIO_RB15_Toggle()            (LATBINV= (1<<15))
#define GPIO_RB15_OutputEnable()      (TRISBCLR = (1<<15))
#define GPIO_RB15_InputEnable()       (TRISBSET = (1<<15))
#define GPIO_RB15_Get()               ((PORTB >> 15) & 0x1)
#define GPIO_RB15_PIN                  GPIO_PIN_RB15

/*** Macros for GPIO_RG6 pin ***/
#define GPIO_RG6_Set()               (LATGSET = (1<<6))
#define GPIO_RG6_Clear()             (LATGCLR = (1<<6))
#define GPIO_RG6_Toggle()            (LATGINV= (1<<6))
#define GPIO_RG6_OutputEnable()      (TRISGCLR = (1<<6))
#define GPIO_RG6_InputEnable()       (TRISGSET = (1<<6))
#define GPIO_RG6_Get()               ((PORTG >> 6) & 0x1)
#define GPIO_RG6_PIN                  GPIO_PIN_RG6

/*** Macros for GPIO_RG7 pin ***/
#define GPIO_RG7_Set()               (LATGSET = (1<<7))
#define GPIO_RG7_Clear()             (LATGCLR = (1<<7))
#define GPIO_RG7_Toggle()            (LATGINV= (1<<7))
#define GPIO_RG7_OutputEnable()      (TRISGCLR = (1<<7))
#define GPIO_RG7_InputEnable()       (TRISGSET = (1<<7))
#define GPIO_RG7_Get()               ((PORTG >> 7) & 0x1)
#define GPIO_RG7_PIN                  GPIO_PIN_RG7

/*** Macros for GPIO_RB4 pin ***/
#define GPIO_RB4_Set()               (LATBSET = (1<<4))
#define GPIO_RB4_Clear()             (LATBCLR = (1<<4))
#define GPIO_RB4_Toggle()            (LATBINV= (1<<4))
#define GPIO_RB4_OutputEnable()      (TRISBCLR = (1<<4))
#define GPIO_RB4_InputEnable()       (TRISBSET = (1<<4))
#define GPIO_RB4_Get()               ((PORTB >> 4) & 0x1)
#define GPIO_RB4_PIN                  GPIO_PIN_RB4

/*** Macros for GPIO_RA15 pin ***/
#define GPIO_RA15_Set()               (LATASET = (1<<15))
#define GPIO_RA15_Clear()             (LATACLR = (1<<15))
#define GPIO_RA15_Toggle()            (LATAINV= (1<<15))
#define GPIO_RA15_OutputEnable()      (TRISACLR = (1<<15))
#define GPIO_RA15_InputEnable()       (TRISASET = (1<<15))
#define GPIO_RA15_Get()               ((PORTA >> 15) & 0x1)
#define GPIO_RA15_PIN                  GPIO_PIN_RA15

/*** Macros for GPIO_RC12 pin ***/
#define GPIO_RC12_Set()               (LATCSET = (1<<12))
#define GPIO_RC12_Clear()             (LATCCLR = (1<<12))
#define GPIO_RC12_Toggle()            (LATCINV= (1<<12))
#define GPIO_RC12_OutputEnable()      (TRISCCLR = (1<<12))
#define GPIO_RC12_InputEnable()       (TRISCSET = (1<<12))
#define GPIO_RC12_Get()               ((PORTC >> 12) & 0x1)
#define GPIO_RC12_PIN                  GPIO_PIN_RC12

/*** Macros for GPIO_RC15 pin ***/
#define GPIO_RC15_Set()               (LATCSET = (1<<15))
#define GPIO_RC15_Clear()             (LATCCLR = (1<<15))
#define GPIO_RC15_Toggle()            (LATCINV= (1<<15))
#define GPIO_RC15_OutputEnable()      (TRISCCLR = (1<<15))
#define GPIO_RC15_InputEnable()       (TRISCSET = (1<<15))
#define GPIO_RC15_Get()               ((PORTC >> 15) & 0x1)
#define GPIO_RC15_PIN                  GPIO_PIN_RC15

/*** Macros for GPIO_RD8 pin ***/
#define GPIO_RD8_Set()               (LATDSET = (1<<8))
#define GPIO_RD8_Clear()             (LATDCLR = (1<<8))
#define GPIO_RD8_Toggle()            (LATDINV= (1<<8))
#define GPIO_RD8_OutputEnable()      (TRISDCLR = (1<<8))
#define GPIO_RD8_InputEnable()       (TRISDSET = (1<<8))
#define GPIO_RD8_Get()               ((PORTD >> 8) & 0x1)
#define GPIO_RD8_PIN                  GPIO_PIN_RD8

/*** Macros for GPIO_RC10 pin ***/
#define GPIO_RC10_Set()               (LATCSET = (1<<10))
#define GPIO_RC10_Clear()             (LATCCLR = (1<<10))
#define GPIO_RC10_Toggle()            (LATCINV= (1<<10))
#define GPIO_RC10_OutputEnable()      (TRISCCLR = (1<<10))
#define GPIO_RC10_InputEnable()       (TRISCSET = (1<<10))
#define GPIO_RC10_Get()               ((PORTC >> 10) & 0x1)
#define GPIO_RC10_PIN                  GPIO_PIN_RC10

/*** Macros for GPIO_RB7 pin ***/
#define GPIO_RB7_Set()               (LATBSET = (1<<7))
#define GPIO_RB7_Clear()             (LATBCLR = (1<<7))
#define GPIO_RB7_Toggle()            (LATBINV= (1<<7))
#define GPIO_RB7_OutputEnable()      (TRISBCLR = (1<<7))
#define GPIO_RB7_InputEnable()       (TRISBSET = (1<<7))
#define GPIO_RB7_Get()               ((PORTB >> 7) & 0x1)
#define GPIO_RB7_PIN                  GPIO_PIN_RB7

/*** Macros for GPIO_RC13 pin ***/
#define GPIO_RC13_Set()               (LATCSET = (1<<13))
#define GPIO_RC13_Clear()             (LATCCLR = (1<<13))
#define GPIO_RC13_Toggle()            (LATCINV= (1<<13))
#define GPIO_RC13_OutputEnable()      (TRISCCLR = (1<<13))
#define GPIO_RC13_InputEnable()       (TRISCSET = (1<<13))
#define GPIO_RC13_Get()               ((PORTC >> 13) & 0x1)
#define GPIO_RC13_PIN                  GPIO_PIN_RC13

/*** Macros for GPIO_RB9 pin ***/
#define GPIO_RB9_Set()               (LATBSET = (1<<9))
#define GPIO_RB9_Clear()             (LATBCLR = (1<<9))
#define GPIO_RB9_Toggle()            (LATBINV= (1<<9))
#define GPIO_RB9_OutputEnable()      (TRISBCLR = (1<<9))
#define GPIO_RB9_InputEnable()       (TRISBSET = (1<<9))
#define GPIO_RB9_Get()               ((PORTB >> 9) & 0x1)
#define GPIO_RB9_PIN                  GPIO_PIN_RB9

/*** Macros for GPIO_RC6 pin ***/
#define GPIO_RC6_Set()               (LATCSET = (1<<6))
#define GPIO_RC6_Clear()             (LATCCLR = (1<<6))
#define GPIO_RC6_Toggle()            (LATCINV= (1<<6))
#define GPIO_RC6_OutputEnable()      (TRISCCLR = (1<<6))
#define GPIO_RC6_InputEnable()       (TRISCSET = (1<<6))
#define GPIO_RC6_Get()               ((PORTC >> 6) & 0x1)
#define GPIO_RC6_PIN                  GPIO_PIN_RC6

/*** Macros for GPIO_RC7 pin ***/
#define GPIO_RC7_Set()               (LATCSET = (1<<7))
#define GPIO_RC7_Clear()             (LATCCLR = (1<<7))
#define GPIO_RC7_Toggle()            (LATCINV= (1<<7))
#define GPIO_RC7_OutputEnable()      (TRISCCLR = (1<<7))
#define GPIO_RC7_InputEnable()       (TRISCSET = (1<<7))
#define GPIO_RC7_Get()               ((PORTC >> 7) & 0x1)
#define GPIO_RC7_PIN                  GPIO_PIN_RC7

/*** Macros for GPIO_RC8 pin ***/
#define GPIO_RC8_Set()               (LATCSET = (1<<8))
#define GPIO_RC8_Clear()             (LATCCLR = (1<<8))
#define GPIO_RC8_Toggle()            (LATCINV= (1<<8))
#define GPIO_RC8_OutputEnable()      (TRISCCLR = (1<<8))
#define GPIO_RC8_InputEnable()       (TRISCSET = (1<<8))
#define GPIO_RC8_Get()               ((PORTC >> 8) & 0x1)
#define GPIO_RC8_PIN                  GPIO_PIN_RC8

/*** Macros for GPIO_RD5 pin ***/
#define GPIO_RD5_Set()               (LATDSET = (1<<5))
#define GPIO_RD5_Clear()             (LATDCLR = (1<<5))
#define GPIO_RD5_Toggle()            (LATDINV= (1<<5))
#define GPIO_RD5_OutputEnable()      (TRISDCLR = (1<<5))
#define GPIO_RD5_InputEnable()       (TRISDSET = (1<<5))
#define GPIO_RD5_Get()               ((PORTD >> 5) & 0x1)
#define GPIO_RD5_PIN                  GPIO_PIN_RD5

/*** Macros for GPIO_RD6 pin ***/
#define GPIO_RD6_Set()               (LATDSET = (1<<6))
#define GPIO_RD6_Clear()             (LATDCLR = (1<<6))
#define GPIO_RD6_Toggle()            (LATDINV= (1<<6))
#define GPIO_RD6_OutputEnable()      (TRISDCLR = (1<<6))
#define GPIO_RD6_InputEnable()       (TRISDSET = (1<<6))
#define GPIO_RD6_Get()               ((PORTD >> 6) & 0x1)
#define GPIO_RD6_PIN                  GPIO_PIN_RD6

/*** Macros for GPIO_RC9 pin ***/
#define GPIO_RC9_Set()               (LATCSET = (1<<9))
#define GPIO_RC9_Clear()             (LATCCLR = (1<<9))
#define GPIO_RC9_Toggle()            (LATCINV= (1<<9))
#define GPIO_RC9_OutputEnable()      (TRISCCLR = (1<<9))
#define GPIO_RC9_InputEnable()       (TRISCSET = (1<<9))
#define GPIO_RC9_Get()               ((PORTC >> 9) & 0x1)
#define GPIO_RC9_PIN                  GPIO_PIN_RC9

/*** Macros for GPIO_RF0 pin ***/
#define GPIO_RF0_Set()               (LATFSET = (1<<0))
#define GPIO_RF0_Clear()             (LATFCLR = (1<<0))
#define GPIO_RF0_Toggle()            (LATFINV= (1<<0))
#define GPIO_RF0_OutputEnable()      (TRISFCLR = (1<<0))
#define GPIO_RF0_InputEnable()       (TRISFSET = (1<<0))
#define GPIO_RF0_Get()               ((PORTF >> 0) & 0x1)
#define GPIO_RF0_PIN                  GPIO_PIN_RF0

/*** Macros for GPIO_RF1 pin ***/
#define GPIO_RF1_Set()               (LATFSET = (1<<1))
#define GPIO_RF1_Clear()             (LATFCLR = (1<<1))
#define GPIO_RF1_Toggle()            (LATFINV= (1<<1))
#define GPIO_RF1_OutputEnable()      (TRISFCLR = (1<<1))
#define GPIO_RF1_InputEnable()       (TRISFSET = (1<<1))
#define GPIO_RF1_Get()               ((PORTF >> 1) & 0x1)
#define GPIO_RF1_PIN                  GPIO_PIN_RF1

/*** Macros for GPIO_RB10 pin ***/
#define GPIO_RB10_Set()               (LATBSET = (1<<10))
#define GPIO_RB10_Clear()             (LATBCLR = (1<<10))
#define GPIO_RB10_Toggle()            (LATBINV= (1<<10))
#define GPIO_RB10_OutputEnable()      (TRISBCLR = (1<<10))
#define GPIO_RB10_InputEnable()       (TRISBSET = (1<<10))
#define GPIO_RB10_Get()               ((PORTB >> 10) & 0x1)
#define GPIO_RB10_PIN                  GPIO_PIN_RB10

/*** Macros for GPIO_RB11 pin ***/
#define GPIO_RB11_Set()               (LATBSET = (1<<11))
#define GPIO_RB11_Clear()             (LATBCLR = (1<<11))
#define GPIO_RB11_Toggle()            (LATBINV= (1<<11))
#define GPIO_RB11_OutputEnable()      (TRISBCLR = (1<<11))
#define GPIO_RB11_InputEnable()       (TRISBSET = (1<<11))
#define GPIO_RB11_Get()               ((PORTB >> 11) & 0x1)
#define GPIO_RB11_PIN                  GPIO_PIN_RB11

/*** Macros for GPIO_RB12 pin ***/
#define GPIO_RB12_Set()               (LATBSET = (1<<12))
#define GPIO_RB12_Clear()             (LATBCLR = (1<<12))
#define GPIO_RB12_Toggle()            (LATBINV= (1<<12))
#define GPIO_RB12_OutputEnable()      (TRISBCLR = (1<<12))
#define GPIO_RB12_InputEnable()       (TRISBSET = (1<<12))
#define GPIO_RB12_Get()               ((PORTB >> 12) & 0x1)
#define GPIO_RB12_PIN                  GPIO_PIN_RB12

/*** Macros for GPIO_RB13 pin ***/
#define GPIO_RB13_Set()               (LATBSET = (1<<13))
#define GPIO_RB13_Clear()             (LATBCLR = (1<<13))
#define GPIO_RB13_Toggle()            (LATBINV= (1<<13))
#define GPIO_RB13_OutputEnable()      (TRISBCLR = (1<<13))
#define GPIO_RB13_InputEnable()       (TRISBSET = (1<<13))
#define GPIO_RB13_Get()               ((PORTB >> 13) & 0x1)
#define GPIO_RB13_PIN                  GPIO_PIN_RB13

/*** Macros for GPIO_RA10 pin ***/
#define GPIO_RA10_Set()               (LATASET = (1<<10))
#define GPIO_RA10_Clear()             (LATACLR = (1<<10))
#define GPIO_RA10_Toggle()            (LATAINV= (1<<10))
#define GPIO_RA10_OutputEnable()      (TRISACLR = (1<<10))
#define GPIO_RA10_InputEnable()       (TRISASET = (1<<10))
#define GPIO_RA10_Get()               ((PORTA >> 10) & 0x1)
#define GPIO_RA10_PIN                  GPIO_PIN_RA10


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_PORT;

typedef enum
{
    GPIO_INTERRUPT_ON_MISMATCH,
    GPIO_INTERRUPT_ON_RISING_EDGE,
    GPIO_INTERRUPT_ON_FALLING_EDGE,
    GPIO_INTERRUPT_ON_BOTH_EDGES,
}GPIO_INTERRUPT_STYLE;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    GPIO_PIN_RA0 = 0,
    GPIO_PIN_RA1 = 1,
    GPIO_PIN_RA4 = 4,
    GPIO_PIN_RA7 = 7,
    GPIO_PIN_RA8 = 8,
    GPIO_PIN_RA10 = 10,
    GPIO_PIN_RA11 = 11,
    GPIO_PIN_RA12 = 12,
    GPIO_PIN_RA14 = 14,
    GPIO_PIN_RA15 = 15,
    GPIO_PIN_RB0 = 16,
    GPIO_PIN_RB1 = 17,
    GPIO_PIN_RB2 = 18,
    GPIO_PIN_RB3 = 19,
    GPIO_PIN_RB4 = 20,
    GPIO_PIN_RB5 = 21,
    GPIO_PIN_RB6 = 22,
    GPIO_PIN_RB7 = 23,
    GPIO_PIN_RB8 = 24,
    GPIO_PIN_RB9 = 25,
    GPIO_PIN_RB10 = 26,
    GPIO_PIN_RB11 = 27,
    GPIO_PIN_RB12 = 28,
    GPIO_PIN_RB13 = 29,
    GPIO_PIN_RB14 = 30,
    GPIO_PIN_RB15 = 31,
    GPIO_PIN_RC0 = 32,
    GPIO_PIN_RC1 = 33,
    GPIO_PIN_RC2 = 34,
    GPIO_PIN_RC6 = 38,
    GPIO_PIN_RC7 = 39,
    GPIO_PIN_RC8 = 40,
    GPIO_PIN_RC9 = 41,
    GPIO_PIN_RC10 = 42,
    GPIO_PIN_RC11 = 43,
    GPIO_PIN_RC12 = 44,
    GPIO_PIN_RC13 = 45,
    GPIO_PIN_RC15 = 47,
    GPIO_PIN_RD5 = 53,
    GPIO_PIN_RD6 = 54,
    GPIO_PIN_RD8 = 56,
    GPIO_PIN_RE1 = 65,
    GPIO_PIN_RE12 = 76,
    GPIO_PIN_RE13 = 77,
    GPIO_PIN_RE14 = 78,
    GPIO_PIN_RE15 = 79,
    GPIO_PIN_RF0 = 80,
    GPIO_PIN_RF1 = 81,
    GPIO_PIN_RG6 = 102,
    GPIO_PIN_RG7 = 103,
    GPIO_PIN_RG8 = 104,
    GPIO_PIN_RG9 = 105,

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    GPIO_PIN_NONE = -1

} GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xF), (uint32_t)(value) << (pin & 0xF));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xF)) & 0x1);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xF)) & 0x1);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
