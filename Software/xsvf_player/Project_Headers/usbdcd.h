/**
 * @file     usbdcd.h (180.ARM_Peripherals/Project_Headers/usbdcd.h)
 * @brief    USB Device Charger Detection
 *
 * @version  V4.12.1.230
 * @date     13 April 2016
 */

#ifndef HEADER_USBDCD_H_
#define HEADER_USBDCD_H_
 /*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
#include "derivative.h"
#include "hardware.h"

namespace USBDM {

/**
 * @addtogroup USBDCD_Group USBDCD, USB Device Charger Detection
 * @brief Abstraction for USB Device Charger Detection
 * @{
 */

/**
 * Disables watchdog test mode until next reset
 */
enum UsbdcdClockUnit {
   UsbdcdClockUnit_kHz = USBDCD_CLOCK_CLOCK_UNIT(0), //!< Frequency in kHz
   UsbdcdClockUnit_MHz = USBDCD_CLOCK_CLOCK_UNIT(1), //!< Frequency in MHz
};

/**
 * Charger Detection Sequence Status.
 * Indicates the status of the charger detection sequence.
 */
enum UsbdcdSeqStatus {
   UsbdcdSeqStatus_Idle         = 0b00, //!< The module is either not enabled, or the module is enabled but the data pins have not yet been detected.
   UsbdcdSeqStatus_PinsDetected = 0b01, //!< Data pin contact detection is complete
   UsbdcdSeqStatus_PortDetected = 0b10, //!< Charging port detection is complete.
   UsbdcdSeqStatus_TypeDetected = 0b11, //!< Charger type detection is complete.
};

/**
 * Charger Detection Sequence Results.
 * Reports how the charger detection is attached.
 */
enum UsbdcdSeqResult {
   UsbdcdSeqResult_Unknown          = 0b00, //!< No results to report.
   UsbdcdSeqResult_StandardHost     = 0b01, //!< Attached to a standard host. Must comply with USB 2.0 by drawing only 2.5 mA (max) until connected.
   UsbdcdSeqResult_ChargingPort     = 0b10, //!< Attached to a charging port. The exact meaning depends on bit 18:
   UsbdcdSeqResult_DedicatedCharger = 0b11, //!< Attached to a dedicated charger.
};

/**
 * USBDCD status
 */
union UsbdcdStatus {
   uint32_t mask;
   struct {
      unsigned :16;
      UsbdcdSeqResult usbdcdSeqResult:2;
      UsbdcdSeqStatus usbdcdSeqStatus:2;
      bool            error:1;
      bool            timeout:1;
      bool            active:1;
      unsigned        :9;
   };
};
/**
 * Type definition for USBDCD interrupt call back
 */
typedef void (*USBDCDCallbackFunction)();

/**
 * Template class representing the Watchdog Monitor
 *
 * The USB Device Charger Detection (USBDCD) module works with the USB transceiver to
 * detect whether the USB device is attached to a charging port, either a dedicated
 * charging port or a charging host.
 * System software coordinates the detection activities of the module and controls
 * an off-chip integrated circuit that performs the battery charging.
 *
 * @tparam info      Information class for USBDCD
 */
template<class Info>
class UsbdcdBase_T {

protected:
   /**
    * Callback to catch unhandled interrupt
    */
   static void unhandledCallback() {
      setAndCheckErrorCode(E_NO_HANDLER);
   }

   /** Callback function for ISR */
   static USBDCDCallbackFunction callback;

public:
   /**
    * Hardware instance pointer.
    *
    * @return Reference to USBDCD hardware
    */
   static __attribute__((always_inline)) volatile USBDCD_Type &usbdcd() { return Info::usbdcd(); }

   /**
    * Get USBDCD status.
    *
    * @return Status value
    */
   static UsbdcdStatus getStatus() {
      union {
         uint32_t       a;
         UsbdcdStatus   b;
      } x;
      x.a = usbdcd().STATUS;
      return (x.b);
   }

   /**
    * IRQ handler
    */
   static void irqHandler() {
      // Call handler
      callback();
   }

   /**
    * Set callback function.
    *
    * @param[in]  theCallback Callback function to execute on interrupt
    *
    * @note It is expected that the callback will clear the status flag that triggered the interrupt. See getStatus().
    */
   static void setCallback(USBDCDCallbackFunction theCallback) {
      static_assert(Info::irqHandlerInstalled, "USBDCD not configure for interrupts - Modify Configure.usbdm");
      if (theCallback == nullptr) {
         theCallback = unhandledCallback;
      }
      callback = theCallback;
   }

public:

   /**
    * Basic enable USBDCD.
    */
   static void enable() {

      // Enable clock to interface
      Info::enableClock();
   }

   /**
    * Enable with default settings.
    * Includes configuring all pins
    */
   static void defaultConfigure() {
      enable();
      softwareReset();
   }

   /**
    * Configure
    *
    * Sets default clock settings based on SystemBusClock
    */
   static __attribute__((always_inline)) void configure() {
      enable();
      softwareReset();
      setClock(SystemBusClock/1000000, UsbdcdClockUnit_MHz);
   }

   /**
    *
    * @param freq
    * @param usbdcdClockUnit
    */
   static void setClock(unsigned freq, UsbdcdClockUnit usbdcdClockUnit) {
      usbdcd().CLOCK = USBDCD_CLOCK_CLOCK_SPEED(freq)|usbdcdClockUnit;
   }

   /**
    * Disable interface to USBDCD
    */
   static void disable() {
      Info::disableClock();
   }

   /**
    * Enable interrupts in NVIC
    */
   static void enableNvicInterrupts() {
      NVIC_EnableIRQ(Info::irqNums[0]);
   }

   /**
    * Enable and set priority of interrupts in NVIC
    * Any pending NVIC interrupts are first cleared.
    *
    * @param[in]  nvicPriority  Interrupt priority
    */
   static void enableNvicInterrupts(uint32_t nvicPriority) {
      enableNvicInterrupt(Info::irqNums[0], nvicPriority);
   }

   /**
    * Disable interrupts in NVIC
    */
   static void disableNvicInterrupts() {
      NVIC_DisableIRQ(Info::irqNums[0]);
   }

   /**
    * Enable/disable interrupts
    *
    * @param[in]  enable        True => enable, False => disable
    *
    * @note This is a protected operation which requires unlock
    */
   static void enableInterrupt(bool enable=true) {
      if (enable) {
         usbdcd().CONTROL |= USBDCD_CONTROL_IE_MASK;
      }
      else {
         usbdcd().CONTROL &= ~USBDCD_CONTROL_IE_MASK;
      }
   }

   /**
    * Clear interrupt flag
    */
   static void clearInterrupt() {
      usbdcd().CONTROL |= USBDCD_CONTROL_IACK_MASK;
   }

   /**
    * Start detection sequence
    */
   static void startDetection() {
      usbdcd().CONTROL |= USBDCD_CONTROL_START_MASK;
   }

   /**
    * Software reset
    */
   static void softwareReset() {
      usbdcd().CONTROL |= USBDCD_CONTROL_SR_MASK;
   }
};

template<class Info> USBDCDCallbackFunction UsbdcdBase_T<Info>::callback = UsbdcdBase_T<Info>::unhandledCallback;

#if defined(USBDM_USBDCD0_IS_DEFINED)
class Usbdcd0 : public UsbdcdBase_T<Usbdcd0Info> {};
#endif

/**
 * End USBDCD_Group
 * @}
 */
} // End namespace USBDM

#endif /* HEADER_USBDCD_H_ */
