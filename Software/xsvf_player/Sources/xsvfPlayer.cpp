/*
 ============================================================================
 * @file    xsvf_player.cpp
 *
 * XSVF player
 * Plays a XSVF sequence hard-programmed in a C array.
 *
 *  Created on: 10/1/2016
 *      Author: podonoghue
 ============================================================================
 */
#include "hardware.h"
#include "utilities.h"
#include "JtagInterface.h"
#include "JtagTables.h"
#include "xsvfPlayer.h"

// Allow access to USBDM methods
using namespace USBDM;

/**
 * Get command name as string
 *
 * @param command Command code
 *
 * @return Pointer to static string
 */
const char *XsvfPlayer::getCommandName(XsvfCommand command) {
   static const char* commands[] = {
         "XCOMPLETE",     // 0x00
         "XTDOMASK",      // 0x01
         "XSIR",          // 0x02
         "XSDR",          // 0x03
         "XRUNTEST",      // 0x04
         "Illegal",
         "Illegal",
         "XREPEAT",       // 0x07
         "XSDRSIZE",      // 0x08
         "XSDRTDO",       // 0x09
         "XSETSDRMASKS",  // 0x0a
         "XSDRINC",       // 0x0b
         "XSDRB",         // 0x0c
         "XSDRC",         // 0x0d
         "XSDRE",         // 0x0e
         "XSDRTDOB",      // 0x0f
         "XSDRTDOC",      // 0x10
         "XSDRTDOE",      // 0x11
         "XSTATE",        // 0x12
         "XENDIR",        // 0x13
         "XENDDR",        // 0x14
         "XSIR2",         // 0x15
         "XCOMMENT",      // 0x16
         "XWAIT",         // 0x17
   };

   const char *cmdName = "Illegal";
   if (((unsigned)command)<(sizeof(commands)/sizeof(commands[0]))) {
      cmdName = commands[command];
   }
   return (cmdName);
}

/**
 * Get state name as string
 *
 * @param state State code
 *
 * @return Pointer to static string
 */
const char *XsvfPlayer::getXstateName(Xstate state) {
   static const char* names[] = {
         "Reset",
         "Idle",
         "DR_Select",
         "DR_Capture",
         "DR_Shift",
         "DR_Exit1",
         "DR_Pause",
         "DR_Exit2",
         "DR_Update",
         "IR_Select",
         "IR_Capture",
         "IR_Shift",
         "IR_Exit1",
         "IR_Pause",
         "IR_Exit2",
         "IR_Update",
   };
   const char *name = "Illegal";
   if (((unsigned)state)<(sizeof(names)/sizeof(names[0]))) {
      name = names[state];
   }
   return (name);
}

/**
 * Print buffer contents in binary
 *
 * @param title Title to prefix each line
 * @param size	Size of buffer
 * @param buff	Buffer to print
 */
void XsvfPlayer::printBits(const char* title, unsigned size, const uint8_t *buff) {
   (void)title;
   (void)buff;
   unsigned index = 0;
   size = (size+7)/8;
   bool doHeader = true;
   while(size-->0) {
      if (doHeader) {
         console.setWidth(4).setPadding(Padding_LeadingZeroes);
         console.WRITE(title).WRITE("=").WRITE(index,Radix_16).WRITE(":");
      }
      index+= 8;
      console.setWidth(2).setPadding(Padding_LeadingZeroes);
      console.WRITE(*buff++,Radix_16);
      doHeader = (index%256) == 0;
      if (doHeader) {
         console.WRITELN();
      }
   }
   console.WRITELN();
   console.resetFormat();
}

/**
 * Shift in value
 * Assumes in DR_Shift or IR_Shift state
 *
 * @param size             Number of bits to shift
 * @param tdi_value        Dummy TDI value to shift in
 * @param tdo_value        Buffer for TDO value shifted out
 * @param exit_shift_state Whether to exit IR/DR_Shift at end of shift
 */
void XsvfPlayer::shiftOut(unsigned size, bool tdi_value, uint8_t *tdo_value, bool exit_shift_state) {

   usbdm_assert((currentState == IR_Shift) || (currentState == DR_Shift), "Illegal state for shift operation");

   unsigned sizeInBytes = (size+7)/8;

   // Start at Least Significant bit
   uint8_t mask = 0b1;

   // Start at Least Significant byte
   tdo_value += sizeInBytes-1;

   JtagInterface::setTMS(0);
   while(size-->0) {
      if (mask == 0b1) {
         *tdo_value = 0;
      }
      if (size == 0) {
         // Last bit - move to
         JtagInterface::setTMS(exit_shift_state);
      }
      JtagInterface::setTDI(tdi_value);
      JtagInterface::clockTCK();
      if (JtagInterface::getTDO()) {
         *tdo_value |= mask;
      }
      mask <<= 1;
      if (mask == 0) {
         mask = 0b1;
         tdo_value--;
      }
   }
   if (exit_shift_state) {
      currentState = (currentState==IR_Shift)?IR_Exit1:DR_Exit1;
   }
}

/**
 * Shift in value
 * Assumes in DR_Shift or IR_Shift state
 *
 * @param size             Number of bits to shift
 * @param tdi_value        TDI value to shift in
 * @param exit_shift_state Whether to exit IR/DR_Shift at end of shift
 */
void XsvfPlayer::shiftIn(unsigned size, uint8_t *tdi_value, bool exit_shift_state) {

   usbdm_assert((currentState == IR_Shift) || (currentState == DR_Shift), "Illegal state for shift operation");

   unsigned sizeInBytes = (size+7)/8;

   // Start at Least Significant bit
   uint8_t mask = 0b1;

   // Start at Least Significant byte
   tdi_value += sizeInBytes-1;

   JtagInterface::setTMS(0);
   while(size-->0) {
      if (size == 0) {
         // Last bit - move to
         JtagInterface::setTMS(exit_shift_state);
      }
      JtagInterface::setTDI(*tdi_value&mask);
      JtagInterface::clockTCK();
      mask <<= 1;
      if (mask == 0) {
         mask = 0b1;
         tdi_value--;
      }
   }
   if (exit_shift_state) {
      currentState = (currentState==IR_Shift)?IR_Exit1:DR_Exit1;
   }
}

/**
 * Shift in value
 * Assumes in DR_Shift or IR_Shift state
 *
 * @param size             Number of bits to shift
 * @param tdi_value        TDI value to shift in
 * @param tdo_value        TDO value to check
 * @param tdo_mask         TDO mask value applied to check
 * @param exit_shift_state Whether to exit IR/DR_Shift at end of shift
 *
 * @return true  => TDO value matched
 * @return false => TDO value did not match
 */
bool XsvfPlayer::shiftIn(unsigned size, uint8_t *tdi_value, uint8_t *tdo_value, uint8_t *tdo_mask, bool exit_shift_state) {

   usbdm_assert((currentState == IR_Shift) || (currentState == DR_Shift), "Illegal state for shift operation");

   unsigned sizeInBytes = (size+7)/8;

   // Start at Least Significant bit
   uint8_t mask = 0b1;

   // Start at Least Significant byte
   tdi_value += sizeInBytes-1;
   tdo_value += sizeInBytes-1;
   tdo_mask  += sizeInBytes-1;

   JtagInterface::setTMS(0);
   while(size-->0) {
      if (size == 0) {
         // Last bit - move to
         JtagInterface::setTMS(exit_shift_state);
      }
      JtagInterface::setTDI(*tdi_value&mask);
      JtagInterface::clockTCK();
      if (*tdo_mask&mask) {
         bool expected = *tdo_value&mask;
         if (JtagInterface::getTDO() != expected) {
            return false;
         }
      }
      mask <<= 1;
      if (mask == 0) {
         mask = 0b1;
         tdi_value--;
         tdo_value--;
         tdo_mask--;
      }
   }
   if (exit_shift_state) {
      currentState = (currentState==IR_Shift)?IR_Exit1:DR_Exit1;
   }
   return true;
}

/**
 * Shift in value
 * Assumes in DR_Shift or IR_Shift state
 *
 * @param size             Number of bits to shift
 * @param tdi_value        TDI value to shift in
 * @param tdo_value        TDO value to check
 * @param exit_shift_state Whether to exit IR/DR_Shift at end of shift
 *
 * @return true  => TDO value matched
 * @return false => TDO value did not match
 */
bool XsvfPlayer::shiftIn(unsigned size, uint8_t *tdi_value, uint8_t *tdo_value, bool exit_shift_state) {

   usbdm_assert((currentState == IR_Shift) || (currentState == DR_Shift), "Illegal state for shift operation");

   unsigned sizeInBytes = (size+7)/8;

   // Start at Least Significant bit
   uint8_t mask = 0b1;

   // Start at Least Significant byte
   tdi_value += sizeInBytes-1;
   tdo_value += sizeInBytes-1;

   JtagInterface::setTMS(0);
   while(size-->0) {
      if (size == 0) {
         // Last bit - move to
         JtagInterface::setTMS(exit_shift_state);
      }
      JtagInterface::setTDI(*tdi_value&mask);
      JtagInterface::clockTCK();

      bool expected = *tdo_value&mask;
      if (JtagInterface::getTDO() != expected) {
         return false;
      }
      mask <<= 1;
      if (mask == 0) {
         mask = 0b1;
         tdi_value--;
         tdo_value--;
      }
   }
   if (exit_shift_state) {
      currentState = (currentState==IR_Shift)?IR_Exit1:DR_Exit1;
   }
   return true;
}

/**
 * Determine the next state based upon current state and TMS value
 * This does not affect the hardware state
 *
 * @param tms  TMS value controlling state transition
 *
 * @return Calculated state
 */
Xstate XsvfPlayer::calculateNextState(bool tms) {
   Xstate nextState = stateTable[currentState][tms];
   //      console.WRITE("->{").WRITE(getXstateName(nextState)).WRITE(",").WRITE(tms?'1':'0').WRITELN("}");
   return nextState;
}

/**
 * Move to new state.
 * This outputs signals on TMS, TDO, TCLK to change physical state
 *
 * @param to State to move to
 */
void XsvfPlayer::moveTo(Xstate to) {
   console.WRITE("moveTo(").WRITE(getXstateName(to)).WRITELN(")");

   if (to == Reset) {
      // Force SM to reset state
      // TMS=1, 5*TCK
      JtagInterface::setTMS(1);
      JtagInterface::clockTCK();
      JtagInterface::clockTCK();
      JtagInterface::clockTCK();
      JtagInterface::clockTCK();
      JtagInterface::clockTCK();
      //         console.WRITELN("->{??,1}->{??,1}->{??,1}->{??,1}->{Reset,1}");
      currentState = Reset;
   }
   if (currentState == to) {
      // Do nothing
      return;
   }
   // Follow sequence
   do {
      int8_t tms = tapTransitions[currentState][to];
      usbdm_assert(tms>=0, "Illegal state transition");
      JtagInterface::setTMS(tms);
      JtagInterface::clockTCK();
      currentState = calculateNextState(tms);
   } while(currentState != to);
}

/**
 * Print path leading from 'from' to 'to'
 *
 * @param from Starting state
 * @param to   Ending state
 */
void XsvfPlayer::printTransition(Xstate from, Xstate to) {
   console.WRITE(getXstateName(from));
   Xstate currentState = from;
   do {
      Xstate last = currentState;
      int8_t tms = tapTransitions[currentState][to];
      if (tms < 0) {
         console.WRITE("(Failed)\n");
         return;
      }
      currentState = stateTable[currentState][tms];
      console.WRITE("->{").WRITE(getXstateName(currentState)).WRITE(",").WRITE(tms?'1':'0').WRITELN("}");
      if ((currentState == last) && (currentState != to)) {
         console.WRITE("(Failed - loop)\n");
         return;
      }
   } while (currentState != to);
   console.WRITELN();
}

/**
 * Get bits from  XSVF input
 *
 * @param title   Title for debug
 * @param count   Number if bits (rounded up to multiple of 8)
 * @param buff    Buffer for data
 */
void XsvfPlayer::getBits(unsigned count, uint8_t buff[MAX_BYTES], const char* title) {
   unsigned byteCount = (count+7)/8;
   usbdm_assert(byteCount <= MAX_BYTES, "");
   unsigned index = 0;
   while(byteCount-->0) {
      buff[index++] = get();
   }
   if (title != nullptr) {
      printBits(title, count, buff);
   }
}

/**
 * Play a single XSVF command on hardware
 *
 * @return false => Sequence not complete
 * @return false => Sequence completes
 */
bool XsvfPlayer::play() {
   uint32_t value;
   XsvfCommand command = (XsvfCommand)get1Byte();

   //console.WRITELN(getCommandName(command));
   console.WRITELN(getXstateName(currentState)).WRITE(":");

   switch(command) {
      case XCOMPLETE   :
         console.WRITELN("XCOMPLETE");
         return true;

      case XREPEAT :
         /*
          * XREPEAT times<1 byte>
          * XREPEAT defines the number of times that TDO is tested against the expected value
          * before the ISP operation is considered a failure.
          *
          * NOT IMPLEMENTED - IGNORED
          */
         repeat_count = get1Byte();
         console.WRITE("XREPEAT(").WRITE(repeat_count).WRITELN(")");
         break;

      case XSETSDRMASKS :
         /*
          * XSETSDRMASKS addressMask<"length" bits> dataMask<"length" bits>
          *
          * NOT IMPLEMENTED - ERROR
          */
         error = "XSETSDRMASKS not supported";
         return true;
         break;

      case XSDRINC :
         /*
          * XSDRINC startAddress<"length" bits> numTimes<1 byte>
          *         data[1]<"length2" bits> ...data[numTimes]<"length2" bits>
          *
          * NOT IMPLEMENTED - ERROR
          */
         error = "XSDRINC not supported";
         break;

      case XRUNTEST :
         /*
          * XRUNTEST number<4 bytes>
          *
          * When the current XENDDR or XENDIR state is Run-Test/Idle (see XENDDR and XENDIR
          * commands), XRUNTEST defines the minimum number of TCK cycles to be applied in the
          * Run-Test/Idle state and the minimum number of microseconds the device should be in the
          * Run-Test/Idle state after each visit to the SDR (or SIR) state.
          * The single XRUNTEST number is a specification for both the minimum number of TCK cycles and
          * minimum number of microseconds to wait.
          * After transitioning from SDR (or SIR) to the Run-Test/Idle state, the
          * XSVF interpreter must apply the minimum number of TCK cycles and also must stay within the
          * Run-Test/Idle state for a minimum number of microseconds as specified by the last
          * XRUNTEST command.
          * If no prior XRUNTEST command exists, then the XSVF interpreter assumes an initial XRUNTEST number of zero.
          */
         run_test_time = get4Bytes();
         console.WRITE("XRUNTEST(").WRITE(run_test_time).WRITELN(" cycle or ms)");
         break;

      case XSDRSIZE :
         /*
          * XSDRSIZE length<4 bytes>
          *
          * Specifies the length of all XSDR/XSDRTDO records that follow.
          */
         xsdr_size = get4Bytes();
         console.WRITE("XSDRSIZE(").WRITE(xsdr_size).WRITELN(")");
         break;

      case XTDOMASK :
         /*
          * XTDOMASK value<"length" bits>
          *
          * Set TDO mask
          */
         console.WRITE("XTDOMASK(").WRITE(xsdr_size).WRITELN(")");
         getBits(xsdr_size, tdo_mask, "tdo_mask");
         break;

      case XSTATE :
         /*
          * XSTATE state<1 byte>
          *
          * If the state is Test-Logic-Reset, then force the TAP to the Test-Logic-Reset state via the
          * guaranteed TAP reset sequence: hold TMS High and apply a minimum of five TCK cycles. For
          * non-zero state values, if the TAP is already in the specified state, then do nothing. Otherwise,
          * transition the TAP to the next specified state.
          */
      {
         Xstate state = static_cast<Xstate>(get1Byte());
         console.WRITE("XSTATE(").WRITE( getXstateName(state)).WRITELN(")");
         moveTo(state);
      }
      break;

      case XENDIR :
         /*
          * XENDIR state<1 byte>
          *
          * Set the XSIR end state to Run-Test/Idle or Pause-IR.
          * The default is Run-Test/Idle.
          */
         endir_state = get1Byte()?IR_Pause:Idle;
         console.WRITE("XENDIR(").WRITE( getXstateName(endir_state)).WRITELN(")");
         break;

      case XENDDR :
         /*
          * XENDDR state<1 byte>
          *
          * Set the XSDR and XSDRTDO end state to Run-Test/Idle or Pause-DR.
          * The default is Run-Test/Idle.
          */
         enddr_state = get1Byte()?DR_Pause:Idle;
         console.WRITE("XENDDR(").WRITE( getXstateName(enddr_state)).WRITELN(")");
         break;

      case XCOMMENT :
         /*
          * XCOMMENT char-string-ending-in-zero
          *
          * The XCOMMENT command specifies an arbitrary length character string that ends with a zero byte.
          */
         console.WRITE("XCOMMENT(").WRITE(getString()).WRITELN(")");
         break;

      case XWAIT :
         /*
          * XWAIT wait_state<1 byte> end_state<1 byte> wait_time<4 bytes>
          *
          * Go to the TAP wait_state, stay in the TAP wait_state for a minimum of wait_time (microseconds),
          * and finally go to the TAP end_state to complete the command.
          */
      {
         // State to wait in
         Xstate      wait_state = static_cast<Xstate>(get1Byte());
         // State to move to afterwards
         Xstate      end_state  = static_cast<Xstate>(get1Byte());
         // Time to spend in wait_state
         uint32_t    wait_time  = get4Bytes();

         console.WRITE("XWAIT(").WRITE(getXstateName(wait_state)).WRITE(", ").WRITE(getXstateName(end_state)).WRITE(", ").WRITE(wait_time).WRITELN(")");
         moveTo(wait_state);
         JtagInterface::waitUS(wait_time);
         moveTo(end_state);
      }
      break;

      case XSIR :
         /*
          * XSIR length<1 byte> TDIValue<"length" bits>
          *
          * Go to the Shift-IR state and shift in the TDIValue. If the last XRUNTEST time is non-zero, go to
          * the Run-Test/Idle state and wait for the last specified XRUNTEST time. Otherwise, go to the
          * last specified XENDIR state.
          */
         value = get1Byte();
         console.WRITE("XSIR(").WRITE(value).WRITE(") -> ").WRITELN(getXstateName(endir_state));
         getBits(value, tdi_value, "tdi_value");
         moveTo(IR_Shift);
         shiftIn(value, tdi_value, true);
         if (run_test_time != 0) {
            moveTo(Idle);
            JtagInterface::waitFor(run_test_time);
         }
         else {
            moveTo(endir_state);
            if (endir_state == IR_Pause) {
               usbdm_assert((currentState == IR_Pause), "Illegal state");
            }
         }
         break;

      case XSIR2 :
         /*
          * XSIR2 length<2 bytes> TDIValue<"length" bits>
          *
          * Go to the Shift-IR state and shift in the TDIValue. If the last XRUNTEST time is non-zero, go to
          * the Run-Test/Idle state and wait for the last specified XRUNTEST time. Otherwise, go to the
          * last specified XENDIR state.
          */
         value = get2Bytes();
         console.WRITE("XSIR2(").WRITE(value).WRITELN(")");
         getBits(value, tdi_value, "tdi_value");
         moveTo(IR_Shift);
         shiftIn(value, tdi_value, true);
         if (run_test_time != 0) {
            moveTo(Idle);
            JtagInterface::waitFor(run_test_time);
         }
         else {
            moveTo(endir_state);
         }
         break;

      case XSDR :
         /*
          * XSDR TDIValue<"length" bits>
          *
          * Go to the Shift-DR state and shift in TDIValue; compare the TDOExpected value from the last
          * XSDRTDO instruction against the TDO value that was shifted out (use the TDOMask that was
          * generated by the last XTDOMASK instruction). Length comes from the XSDRSIZE instruction.
          */
         console.WRITE("XSDR(").WRITE(xsdr_size).WRITELN(")");
         getBits(xsdr_size, tdi_value, "tdi_value");

         moveTo(DR_Shift);
         shiftIn(xsdr_size, tdi_value, tdo_value, tdo_mask, true);
         if (run_test_time != 0) {
            moveTo(Idle);
            JtagInterface::waitFor(run_test_time);
         }
         else {
            moveTo(endir_state);
         }

         break;

      case XSDRTDO :
         /*
          * TDIValue<"length" bits> TDOExpected<"length" bits>
          *
          * Go to the Shift-DR state and shift in TDIValue; compare the TDOExpected value against the
          * TDO value that was shifted out (use the TDOMask which was generated by the last
          * XTDOMASK instruction). Length comes from the XSDRSIZE instruction.
          * If the TDO value does not match TDOExpected, perform the exception-handling sequence
          * described in the XC9500 programming algorithm section. If TDO is wrong more than the
          * maximum number of times specified by the XREPEAT instruction, then the ISP operation is
          * determined to have failed.
          * If the last XRUNTEST time is zero, then go to XENDDR state. Otherwise, go to the
          * Run_Test/Idle state and wait for the XRUNTEST time.
          * The TDOExpected Value is used in all successive XSDR instructions until the next XSDR
          * instruction is given.
          */
         console.WRITE("XSDRTDO(").WRITE(xsdr_size).WRITELN(")");
         getBits(xsdr_size, tdi_value, "tdi_value");
         getBits(xsdr_size, tdo_value, "tdo_value");
         moveTo(DR_Shift);
         if (!shiftIn(xsdr_size, tdi_value, tdo_value, tdo_mask, true)) {
            error = "Unexpected TDO value";
            return true;
         }
         if (run_test_time != 0) {
            moveTo(Idle);
            JtagInterface::waitFor(run_test_time);
         }
         else {
            moveTo(enddr_state);
         }
         break;

      case XSDRB :
         /*
          * XSDRB TDIValue<"length" bits>
          *
          * Go to the shift-DR state and shift in the TDI value. Continue to stay in the shift-DR state at the end
          * of the operation. No comparison of TDO value with the last specified TDOExpected is performed.
          */
         console.WRITE("XSDRB(").WRITE(xsdr_size).WRITELN(")");
         getBits(xsdr_size, tdi_value, "tdi_value");
         moveTo(DR_Shift);
         shiftIn(xsdr_size, tdi_value, false);
         break;

      case XSDRC :
         /*
          * XSDRC TDIValue<"length" bits>
          *
          * Shift in the TDI value. Continue to stay in the shift-DR state at the end of the operation. No
          * comparison of TDO value with the last specified TDOExpected is performed.
          */
         console.WRITE("XSDRC(").WRITE(xsdr_size).WRITELN(")");
         getBits(xsdr_size, tdi_value, "tdi_value");
         shiftIn(xsdr_size, tdi_value, false);
         break;

      case XSDRE :
         /*
          * XSDRE TDIValue<"length" bits>
          *
          * Shift in the TDI value. At the end of the operation, go to the XENDDR state. No comparison of
          * TDO value with the last specified TDOExpected is performed.
          */
         console.WRITE("XSDRE(").WRITE(xsdr_size).WRITELN(")");
         usbdm_assert(currentState==DR_Shift, "In wrong state");
         getBits(xsdr_size, tdi_value, "tdi_value");
         shiftIn(xsdr_size, tdi_value, true);
         moveTo(enddr_state);
         break;

      case XSDRTDOB :
         /*
          * XSDRTDOB TDIValue<"length" bits> TDOExpected<"length" bits>
          *
          * Go to the shift-DR state and shift in TDI value; compare the TDOExpected value against the
          * TDO value that was shifted out. TDOMask is not applied. All bits of TDO are compared with the
          * TDOExpected. Length comes from the XSDRSIZE instruction.
          * Because this instruction is primarily meant for FPGAs, if the TDO value does not match
          * TDOExpected, the programming is stopped with an error message. At the end of the
          * operations, continue to stay in the SHIFT-DR state.
          */
         console.WRITE("XSDRTDOB(").WRITE(xsdr_size).WRITELN(")");
         getBits(xsdr_size, tdi_value, "tdi_value");
         getBits(xsdr_size, tdo_value, "tdo_value");
         moveTo(DR_Shift);
         if (!shiftIn(xsdr_size, tdi_value, tdo_value, false)) {
            error = "TDO not matched";
            return true;
         }
         break;

      case XSDRTDOC :
         /*
          * XSDRTDOC TDIValue<"length" bits> TDOExpected<"length" bits>
          *
          * Shift in the TDI value; compare the TDOExpected value against the TDO value that was shifted
          * out. Length comes from the XSDRSIZE instruction. TDOMask is not applied. All bits of TDO are
          * compared with the TDOExpected.
          * If the TDO value does not match TDOExpected, stop the programming operation with an error
          * message. At the end of the operation, continue to stay in the SHIFT-DR state.
          */
         console.WRITE("XSDRTDOC(").WRITE(xsdr_size).WRITELN(")");
         getBits(xsdr_size, tdi_value, "tdi_value");
         getBits(xsdr_size, tdo_value, "tdo_value");
         usbdm_assert(currentState==DR_Shift, "In wrong state");
         if (!shiftIn(xsdr_size, tdi_value, tdo_value, false)) {
            error = "TDO not matched";
            return true;
         }
         break;

      case XSDR_TDO_CAPTURE:
         /*
          * XSDR_TDO_CAPTURE <length> TDIValue<1 bits>
          *
          * Shift in the fixed TDI value while capturing the TDO values.
          * Length is as specified.
          * Go to the last specified XENDIR state.
          */
      {
         uint8_t size      = get1Byte();
         uint8_t tdiValue  = get1Byte();
         console.WRITE("XSDR_TDO_CAPTURE(").WRITE(size).WRITE(", ").WRITE(tdiValue).WRITELN(")");
         moveTo(DR_Shift);
         shiftOut(size, tdiValue, tdo_value, true);
      }
      break;

      case XSDRTDOE :
         /*
          * XSDRTDOE TDIValue<"length" bits> TDOExpected<"length" bits>
          *
          * Shift in the TDI value; compare the TDOExpected value against the TDO value that was shifted
          * out. Length comes from the last XSDSIZE instruction. TDOMask is not applied. All bits of TDO
          * are compared with the TDOExpected.
          * If the TDO value does not match the TDOExpected, stop the programming operations with an
          * error message. At the end of the operation, go to the XENDDR state.
          */
         console.WRITE("XSDRTDOE(").WRITE(xsdr_size).WRITELN(")");
         getBits(xsdr_size, tdi_value, "tdi_value");
         getBits(xsdr_size, tdo_value, "tdo_value");
         usbdm_assert(currentState==DR_Shift, "In wrong state");
         if (!shiftIn(xsdr_size, tdi_value, tdo_value, true)) {
            error = "TDO not matched";
            return true;
         }
         moveTo(enddr_state);
         break;

      default :
         error = "Unknown command";
         return true;
   }
   return false;
}

/**
 * Play XSVF sequence
 *
 * @return true  No errors detected during programming (programming not verified!)
 * @return false Error detected during programming
 */
bool XsvfPlayer::playAll() {

   bool complete = false;
   JtagInterface::enable();

   moveTo(Reset);
   while (!complete) {
      complete = play();
   }
   JtagInterface::disable();
   const char *errorMessage = getError();
   console.WRITE("Processed ").WRITE(byteCounter).WRITELN(" bytes");
   if (errorMessage != nullptr) {
      console.WRITE("Error =  ").WRITELN(errorMessage);
      return false;
   }
   return true;
}
