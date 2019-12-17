/**
 * @file     mcm.h (180.ARM_Peripherals/Project_Headers/mcm.h)
 * @brief    Miscellaneous Control Module
 *
 * @version  V4.12.1.80
 * @date     13 April 2016
 */

#ifndef HEADER_MCM_H
#define HEADER_MCM_H
 /*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
#include "hardware.h"

namespace USBDM {

/**
 * @addtogroup MCM_Group MCM, Miscellaneous Control Module
 * @brief Abstraction for Miscellaneous Control Module
 * @{
 */

/**
 * Type definition for MCM interrupt call back
 */
typedef void (*MCMCallbackFunction)();

/**
 * Template class providing interface to Low Leakage Wake-up Unit
 *
 * @tparam info      Information class for MCM
 *
 * @code
 * using mcm = McmBase_T<McmInfo>;
 *
 *  mcm::configure();
 *
 * @endcode
 */
template <class Info>
class McmBase_T {

protected:
   /** Callback function for ISR */
   static MCMCallbackFunction sCallback;

   /** Callback to catch unhandled interrupt */
   static void unhandledCallback() {
      setAndCheckErrorCode(E_NO_HANDLER);
   }

public:
   /**
    * IRQ handler
    */
   static void irqHandler(void) {
      sCallback();
   }

   /**
    * Set Callback function
    *
    *   @param[in]  callback Callback function to be executed on interrupt\n
    *                        Use nullptr to remove callback.
    */
   static void setCallback(MCMCallbackFunction callback) {
      static_assert(Info::irqHandlerInstalled, "MCM not configured for interrupts");
      if (callback == nullptr) {
         callback = unhandledCallback;
      }
      sCallback = callback;
   }

protected:
   /** Pointer to hardware */
   static __attribute__((always_inline)) volatile MCM_Type &mcm() { return Info::mcm(); }

public:

   /**
    * Basic enable of MCM\n
    * Includes configuring all pins
    */
   static void enable() {
   }

   /**
    * Configure with settings from Configure.usbdmProject.
    */
   static void defaultConfigure() {

      enableNvicInterrupts(Info::irqLevel);
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
};

template<class Info> MCMCallbackFunction McmBase_T<Info>::sCallback = McmBase_T<Info>::unhandledCallback;

#ifdef USBDM_MCM_IS_DEFINED
/**
 * Class representing MCM
 */
class Mcm : public McmBase_T<McmInfo> {};

#endif

/**
 * End MCM_Group
 * @}
 */

} // End namespace USBDM

#endif /* HEADER_MCM_H */
