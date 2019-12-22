/*
 ============================================================================
 * @file    xsf_usb_player.cpp
 *
 * Stand-alone XSVF player
 * Plays a XSVF sequence hard-programmed in a C array.
 *
 *  Created on: 22 Dec 2019
 *      Author: podonoghue
 ============================================================================
 */
#include "hardware.h"
#include "xsvfPlayer.h"
#include "usb.h"
#include "UsbCommandMessage.h"

// Allow access to USBDM methods
using namespace USBDM;

using StatusLED = GpioD<7>;

//#define BYTES32(x) (0xFF&((x)>>24)),(0xFF&((x)>>16)),(0xFF&((x)>>8)),(0xFF&(x))

/**
 * Read IDCODE from CPLD
 *
 * @param idcode  IDCODE as 32-bit integer
 *
 * @return false  => Success. IDCODE has value
 * @return true   => Failed to read IDCODE
 */
bool readIdcode(uint32_t &idcode) {
   static const uint8_t idcode_message[] = {
         XSTATE,           Reset,
         XSTATE,           Idle,       // Move to IDLE state
         XENDIR,           false,      // Set exit to IDLE state (XSIR)
         XENDDR,           false,      // Set exit to IDLE state (XSDR_TDO_CAPTURE)
         XSIR,             8,     1,   // Select IDCODE register (Register #1)
         XSDR_TDO_CAPTURE, 32,    0,   // Read IDCODE register
         XSTATE,           Reset,
         XCOMPLETE,
   };

   XsvfPlayer_Array xsvf(sizeof(idcode_message), idcode_message);
   if (xsvf.playAll()) {
      uint8_t const *idcodeBuff = xsvf.getTdoBuff();

      idcode = (idcodeBuff[0]<<24)+(idcodeBuff[1]<<16)+(idcodeBuff[2]<<8)+idcodeBuff[3];
      return true;
   }
   else {
      console.write("Failed to read IDCODE, rc = ").writeln(xsvf.getError());
      return false;
   }
}

class XsvfPlayer_USB : public XsvfPlayer {

private:
   //
   XsvfBlockCommandMessage command = {
         /* command;    */ UsbCommand_Nop, // Command to execute
         /* byteLength; */ 0,              // Size of data
         /* data[];     */ {},             // Data
   };

   // Count of bytes processed
   unsigned blockByteCounter = 0;

   // Outstanding ACK needed
   bool doResponse = false;

   bool getBlock() {
      if (doResponse) {
         static const SimpleResponseMessage response {
            /* response.status     */ UsbCommandStatus_OK,
            /* response.byteLength */ 0,
         };
         Usb0::sendBulkData(sizeof(response), (uint8_t *)&response, 1000);
      }
      // Need to ACK future requests
      doResponse = true;

      // Reset data index
      blockByteCounter = 0;

      uint16_t size = sizeof(command);
      ErrorCode rc = Usb0::receiveBulkData(size, (uint8_t *)&command);
      if (rc != E_NO_ERROR) {
         command.byteLength = 0;
         error = "Failed to read XSVF block from host";
         return false;
      }
      if (command.command != UsbCommand_XSVF_data) {
         error = "Unexpected USB packet type";
         return false;
      }
      //      writeCommandMessage(*(UsbCommandMessage *)&command);
      return true;
   }

   /**
    * Get single byte from XSVF input
    *
    * @return Byte obtained
    */
   uint8_t get() {
      if (byteCounter>xsvf_data_size) {
         return XCOMPLETE;
      }
      if (blockByteCounter >= command.byteLength) {
         if (!getBlock()) {
            return XCOMPLETE;
         }
      }
      byteCounter++;
      return command.data[blockByteCounter++];
   }

public:
   static bool doReceiveXsvf(unsigned xsvf_size) {

      XsvfPlayer_USB xsvf{xsvf_size};

      SimpleResponseMessage   response;
      response.status       = UsbCommandStatus_OK;
      response.byteLength   = 0;
      Usb0::sendBulkData(sizeof(response), (uint8_t *)&response, 1000);

      if (xsvf.playAll()) {
         // Success
         console.writeln("Programming successful");
         return true;
      }
      else {
         // Failure
         console.write("Programming failed, rc = ").writeln(xsvf.getError());
         return false;
      }
   }

   XsvfPlayer_USB(unsigned xsvf_data_size) : XsvfPlayer(xsvf_data_size) {
   }

   ~XsvfPlayer_USB() {
   }
};

/**
 * Report command to console
 *
 * @param message Command message to describe
 */
static void writeCommandMessage(UsbCommandMessage &message) {
   console.WRITE(getCommandName(message.command));
   if (message.byteLength>0) {
   }
   else {
   }
   console.WRITELN();
}


int main() {

   console.writeln("Starting");

   StatusLED::setOutput(
         PinDriveStrength_High,
         PinDriveMode_PushPull,
         PinSlewRate_Slow);

   // Start USB
   UsbImplementation::initialise();
   checkError();

   for(;;) {
      // Wait for USB connection
      while(!UsbImplementation::isConfigured()) {
         __WFI();
      }
      UsbCommandMessage command;
      ResponseMessage   response;
      for(;;) {
         uint16_t size = sizeof(command);
         ErrorCode rc = Usb0::receiveBulkData(size, (uint8_t *)&command);
         if (rc != E_NO_ERROR) {
            continue;
         }
         writeCommandMessage(command);

         // Default to OK small response
         unsigned responseSize = sizeof(SimpleResponseMessage);
         response.byteLength   = 0;
         response.status       = UsbCommandStatus_OK;

         switch(command.command) {
            default:
               response.status = UsbCommandStatus_Failed;
               console.write("Unexpected command: ").writeln(command.command);
               break;
            case UsbCommand_Nop:
               break;
            case UsbCommand_Identify:
               if (!JtagInterface::checkVref()) {
                  response.status = UsbCommandStatus_Failed;
                  console.writeln("No target Vref");
                  break;
               }
               if (!readIdcode(response.idcode)) {
                  response.status = UsbCommandStatus_Failed;
                  break;
               }
               response.byteLength = 4;
               responseSize        = sizeof(ResponseIdentifyMessage);
               console.write("IDCODE = 0x").writeln(response.idcode, Radix_16);
               break;
            case UsbCommand_CheckVref:
               if (!JtagInterface::checkVref()) {
                  response.status = UsbCommandStatus_Failed;
                  console.writeln("No target Vref");
                  break;
               }
               console.writeln("Target Vref present");
               break;
            case UsbCommand_XSVF:
               if (!JtagInterface::checkVref()) {
                  response.status = UsbCommandStatus_Failed;
                  console.writeln("No target Vref");
                  break;
               }
               if (!XsvfPlayer_USB::doReceiveXsvf(command.xsvfSize)) {
                  response.status = UsbCommandStatus_Failed;
               }
               break;
         }
         Usb0::sendBulkData(responseSize, (uint8_t *)&response, 1000);
      }
   }
   return 0;
}
