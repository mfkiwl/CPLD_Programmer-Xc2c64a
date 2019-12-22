/*
 * JtagInterface.h
 *
 *   Wrapper for JTAG pins being used
 */

#ifndef SOURCES_JTAGINTERFACE_H_
#define SOURCES_JTAGINTERFACE_H_

#include "hardware.h"

class JtagInterface {

private:
   using Jtag = USBDM::GpioBField<3,0>;
   using Tms  = USBDM::GpioB<0>;
   using Tdi  = USBDM::GpioB<1>;
   using Tdo  = USBDM::GpioB<2>;
   using Tck  = USBDM::GpioB<3>;
   using Adc  = USBDM::Adc0;
   using Vref = Adc::Channel<15>;

   static constexpr unsigned TMS_MASK = 0b0001;
   static constexpr unsigned TDI_MASK = 0b0010;
   static constexpr unsigned TDO_MASK = 0b0100;
   static constexpr unsigned TCK_MASK = 0b1000;

public:
   /**
    * Enable JTAG interface
    */
   static void enable() {
      using namespace USBDM;

      Jtag::setInOut(
            PinPull_Up, PinDriveStrength_High, PinDriveMode_PushPull,
            PinAction_None, PinFilter_None, PinSlewRate_Fast);
      Jtag::write(0b1111);
      Jtag::setDirection(TMS_MASK|TDI_MASK|TCK_MASK);
   }

   /**
    * Disable JTAG interface
    *
    * @note Pull-ups are still active on pins
    */
   static void disable() {
      Jtag::setIn();
   }

   /**
    * Check for presence of Vref
    *
    * @return true  => Vref present
    * @return false => Vref not present
    */
   static bool checkVref() {
      using namespace USBDM;

      Adc::configure(AdcResolution_10bit_se, AdcClockSource_Bus);
      return Vref::readAnalogue()>(Adc::getSingleEndedMaximum(AdcResolution_10bit_se) * 0.8);
   }

   /**
    * Set TDI pin level
    *
    * @param value
    */
   static void setTDI(bool value) {
      Tdi::write(value);
   }

   /**
    * Set TMS pin level
    *
    * @param value
    */
   static void setTMS(bool value) {
      Tms::write(value);
   }

   /**
    * Cycle TCK pin
    */
   static void clockTCK() {
      Tck::clear();
      Tck::set();
   }

   /**
    * Read TDO pin
    *
    * @return
    */
   static bool getTDO() {
      return Tdo::read();
   }

   /**
    * Cycle TCK / Wait microseconds
    *
    * @param run_test_time Number of clock cycle/microseconds to wait
    */
   static void waitFor(unsigned run_test_time) {
      while(run_test_time-->0) {
         clockTCK();
      }
   }

   /**
    * Wait for microseconds
    *
    * @param microseconds Microseconds to wait
    */
   static void waitUS(unsigned microseconds) {
      USBDM::waitUS(microseconds);
   }
};

#endif /* SOURCES_JTAGINTERFACE_H_ */
