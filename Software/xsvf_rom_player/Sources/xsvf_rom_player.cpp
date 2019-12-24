/*
 ============================================================================
 * @file    xsvf_rom_player.cpp
 *
 * Stand-alone XSVF player
 * Plays a XSVF sequence hard-programmed in a C array.
 *
 *  Created on: 22 Dec 2019
 *      Author: podonoghue
 ============================================================================
 */
#include "cpld_tester_xsvf.h"
#include "hardware.h"
#include "xsvfPlayer.h"
#include "JtagInterface.h"

// Allow access to USBDM methods
using namespace USBDM;

using StatusLED = GpioD<7>;

// Create player
XsvfPlayer_Array xsvf{sizeof(cpld_tester_xsvf), cpld_tester_xsvf};

int main() {

   StatusLED::setOutput(
         PinDriveStrength_High,
         PinDriveMode_PushPull,
         PinSlewRate_Slow);

   waitMS(100);

   unsigned blinkDelay;

   console.writeln("Waiting for Vref");
   while (!JtagInterface::checkVref()) {
      __asm__("nop");
   }
   waitMS(100);
   console.writeln("Vref present - programming");

   StatusLED::on();
   bool success = xsvf.playAll();
   StatusLED::off();

   if (success) {
      // Success - Slow blinking
      blinkDelay = 500;
      console.writeln("Sequence completed");
   }
   else {
      // Failure - Fast blinking
      blinkDelay = 50;
      console.writeln("Sequence failed");
   }

   for(;;) {
      StatusLED::toggle();
      waitMS(blinkDelay);
   }
   return 0;
}
