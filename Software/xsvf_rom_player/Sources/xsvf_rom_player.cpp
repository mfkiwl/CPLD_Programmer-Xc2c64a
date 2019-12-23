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
#include <old_XSVF_Data.h>
#include "hardware.h"
#include "xsvfPlayer.h"

// Allow access to USBDM methods
using namespace USBDM;

using StatusLED = GpioD<7>;

int main() {

   StatusLED::setOutput(
         PinDriveStrength_High,
         PinDriveMode_PushPull,
         PinSlewRate_Slow);

   waitMS(1000);
   XsvfPlayer_Array xsvf{sizeof(xsvf_data), xsvf_data};

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
      console.writeln("Programming successful");
   }
   else {
      // Failure - Fast blinking
      blinkDelay = 50;
      console.writeln("Programming failed");
   }

   for(;;) {
      StatusLED::toggle();
      waitMS(blinkDelay);
   }
   return 0;
}
