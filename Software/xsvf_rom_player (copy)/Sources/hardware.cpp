/**
 * @file      hardware.cpp (generated from MK20D5.usbdmHardware)
 * @version   1.2.0
 * @brief     Pin initialisation for MK20DX128VLF5
 *
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */

#include "hardware.h"

/**
 * Namespace enclosing USBDM classes
 */
namespace USBDM {

/**
 * @addtogroup USBDM_Group USBDM Peripheral Interface
 * @brief Hardware Peripheral Interface and library
 * @{
 */
/**
 * Used to configure pin-mapping before 1st use of peripherals
 */
void mapAllPins() {
#ifdef PCC_PCCn_CGC_MASK
      PCC->PCC_PORTA = PCC_PCCn_CGC_MASK;
      PCC->PCC_PORTB = PCC_PCCn_CGC_MASK;
      PCC->PCC_PORTD = PCC_PCCn_CGC_MASK;
#else
      enablePortClocks(PORTA_CLOCK_MASK|PORTB_CLOCK_MASK|PORTD_CLOCK_MASK);
#endif
      PORTA->GPCHR = 0x0000UL|PORT_GPCHR_GPWE(0x000CUL);
      PORTA->GPCLR = 0x0200UL|PORT_GPCLR_GPWE(0x0006UL);
      PORTA->GPCLR = 0x0700UL|PORT_GPCLR_GPWE(0x0009UL);
      PORTB->GPCLR = 0x0000UL|PORT_GPCLR_GPWE(0x0001UL);
      PORTD->GPCLR = 0x0100UL|PORT_GPCLR_GPWE(0x00CFUL);
}
/** 
 * End group USBDM_Group
 * @}
 */

} // End namespace USBDM

