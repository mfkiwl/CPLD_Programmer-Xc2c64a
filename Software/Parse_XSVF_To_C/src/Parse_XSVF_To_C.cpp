/*
 ============================================================================
 * @file    xsvf_Parse.cpp
 *  Created on: 10/1/2016
 *      Author: podonoghue
 ============================================================================
 */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "XSVF_Data.h"
#include "JtagTables.h"

/// Maximum number of bits to shift in/out in a single command
static constexpr unsigned MAX_BITS  = 2048;

/// Maximum number of bytes to shift in/out in a single command
static constexpr unsigned MAX_BYTES = (MAX_BITS+7)/8;

/// Maximum string length
static constexpr unsigned MAX_STRING  = 100;

/// Command codes
enum Command {
   XCOMPLETE    = 0x00,
   XTDOMASK     = 0x01,
   XSIR         = 0x02,
   XSDR         = 0x03,
   XRUNTEST     = 0x04,
   XREPEAT      = 0x07,
   XSDRSIZE     = 0x08,
   XSDRTDO      = 0x09,
   XSETSDRMASKS = 0x0a,
   XSDRINC      = 0x0b,
   XSDRB        = 0x0c,
   XSDRC        = 0x0d,
   XSDRE        = 0x0e,
   XSDRTDOB     = 0x0f,
   XSDRTDOC     = 0x10,
   XSDRTDOE     = 0x11,
   XSTATE       = 0x12,
   XENDIR       = 0x13,
   XENDDR       = 0x14,
   XSIR2        = 0x15,
   XCOMMENT     = 0x16,
   XWAIT        = 0x17,
};

#if 0
/**
 * Get command name as string
 *
 * @param command Command code
 *
 * @return Pointer to static string
 */
static const char *getCommandName(Command command) {
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
#endif

/// Used for iterating states
inline Xstate &operator++ (Xstate& d) {
   d = static_cast<Xstate>((static_cast<int>(d) + 1));
   return d;
}

/**
 * Get state name as string
 *
 * @param state State code
 *
 * @return Pointer to static string
 */
const char *getXstateName(Xstate state) {
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

//static constexpr uint8_t Ex_Idle        = 0x00;
//static constexpr uint8_t Ex_DR_Pause    = 0x01;
//static constexpr uint8_t Ex_IR_Pause    = 0x01;
static constexpr uint8_t IDCODE_COMMAND = 0x01;
static constexpr uint8_t BYPASS_COMMAND = 0xFF;
static constexpr uint8_t ENABLE_COMMAND = 0xE8;
static constexpr uint8_t ERASE_COMMAND  = 0xED;
static constexpr uint8_t INIT_COMMAND   = 0xF0;
static constexpr uint8_t CONLD_COMMAND  = 0xC0;
static constexpr uint8_t VERIFY_COMMAND = 0xEE;

class JtagInterface {

public:
   /**
    * Enable JTAG interface
    */
   static void enable() {
   }

   /**
    * Disable JTAG interface
    */
   static void jtagDisable() {
   }

   /**
    * Check for presence of Vref
    *
    * @return true  => Vref present
    * @return false => Vref not present
    */
   static bool checkVref() {
      return true;
   }

   /**
    * Set TDI pin level
    *
    * @param value
    */
   static void setTDI(bool value) {
      (void) value;
   }

   /**
    * Set TMS pin level
    *
    * @param value
    */
   static void setTMS(bool value) {
      (void) value;
   }

   /**
    * Cycle TCK pin
    */
   static void clockTCK() {
   }

   /**
    * Read TDO pin
    *
    * @return
    */
   static bool getTDO() {
      return 0;
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
      (void)microseconds;
   }
};

class Xsvf {
   FILE *fp_input;
   FILE *fp_output;

   // Current JTAG state
   Xstate      currentState            = Reset;

   // State to move to after XSIR, XSIR2 (either IR_Pause or Idle)
   Xstate      endir_state            = Xstate::Idle;

   // State to move to after XSDR, XSDRE, XSDRTDO, XSDRTDOE (either DR_Pause or Idle)
   Xstate      enddr_state            = Xstate::Idle;

   // Time to remain in Run-test-idle state
   uint32_t    run_test_time          = 0;

   // Number of times to retry TDO tests
   uint32_t    repeat_count           = 32;

   // Size for XSDR, XSDRTDO commands
   uint32_t    xsdr_size              = 0;

   // TDI Buffer [xsdr_size] - Data to shift in
   uint8_t     tdi_value[MAX_BYTES];

   // TDO Buffer [xsdr_size] - TDO value to check
   uint8_t     tdo_mask[MAX_BYTES];

   // TDO Buffer [xsdr_size] - Mask applied when checking TDO
   uint8_t     tdo_value[MAX_BYTES];

   // '\0' terminated comment string
   char        string_buffer[MAX_STRING] = {};

   // Count of bytes processed
   unsigned    byteCounter = 0;

   // Error message
   const char *error       = nullptr;

private:
   /**
    * Print buffer contents in binary
    *
    * @param title Title to prefix each line
    * @param size Size of buffer
    * @param buff Buffer to print
    */
   void printBits(const char* title, unsigned numBits, const uint8_t *buff) {
      unsigned size = (numBits+7)/8;
      unsigned index = 8*size;
      bool doHeader = true;
      unsigned byteCount = 0;
      while(size-->0) {
         if (doHeader) {
            fprintf(fp_output, "   /* %-10s %4d:*/ ", title, (index>numBits)?numBits:index);
         }
         index -= 8;
         fprintf(fp_output, "0x%02X, ", *buff++);
         doHeader = (++byteCount == 8);
         if (doHeader) {
            byteCount = 0;
            fprintf(fp_output, "\n");
         }
      }
      fprintf(fp_output, "\n");
   }

   /**
    * Shift in value
    * Assumes in DR_Shift or IR_Shift state
    *
    * @param size             Number of bits to shift
    * @param tdi_value        TDI value to shift in
    * @param exit_shift_state Whether to exit IR/DR_Shift at end of shift
    */
   void shiftIn(unsigned size, uint8_t *tdi_value, bool exit_shift_state) {
      assert((currentState == IR_Shift) || (currentState == DR_Shift));
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
   bool shiftIn(unsigned size, uint8_t *tdi_value, uint8_t *tdo_value, uint8_t *tdo_mask, bool exit_shift_state) {

      assert((currentState == IR_Shift) || (currentState == DR_Shift));
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
   bool shiftIn(unsigned size, uint8_t *tdi_value, uint8_t *tdo_value, bool exit_shift_state) {

      assert((currentState == IR_Shift) || (currentState == DR_Shift));
      if (exit_shift_state) {
         currentState = (currentState==IR_Shift)?IR_Exit1:DR_Exit1;
      }
      return true;
   }

public:
   /**
    * Get error string
    *
    * @return nullptr => No error
    * @return else    => Error description
    */
   const char *getError() {
      return error;
   }

   /**
    * Determine the next state based upon current state and TMS value
    * This does not affect the hardware state
    *
    * @param tms  TMS value controlling state transition
    *
    * @return Calculated state
    */
   Xstate calculateNextState(bool tms) {
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
   void moveTo(Xstate to, bool doPrint) {
//      fprintf(fp_output, "moveTo(%s) ", getXstateName(to));
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
         if (tms<0) {
            fprintf(fp_output, "// %s -> %s - ", getXstateName(currentState), getXstateName(to));
            assert(tms>=0);
         }
         JtagInterface::setTMS(tms);
         JtagInterface::clockTCK();
         currentState = calculateNextState(tms);
         if (doPrint) {
            fprintf(fp_output, "-%s", getXstateName(currentState));
         }
      } while(currentState != to);
   }

   /**
    * Print path leading from 'from' to 'to'
    *
    * @param from Starting state
    * @param to   Ending state
    */
   void printTransition(Xstate from, Xstate to) {
      fprintf(fp_output, getXstateName(from));
      Xstate currentState = from;
      do {
         Xstate last = currentState;
         int8_t tms = tapTransitions[currentState][to];
         if (tms < 0) {
            fprintf(fp_output, "(Failed)\n");
            return;
         }
         currentState = stateTable[currentState][tms];
         fprintf(fp_output, "->{%s,%d}", getXstateName(currentState),tms?'1':'0');
         if ((currentState == last) && (currentState != to)) {
            fprintf(fp_output, "(Failed - loop)\n");
            return;
         }
      } while (currentState != to);
      fprintf(fp_output, "\n");
   }

   /**
    * Get single byte from XSVF input
    *
    * @return Byte obtained
    */
   uint8_t get() {
      if (byteCounter>sizeof(xsvf_data)) {
         return XCOMPLETE;
      }
      byteCounter++;
      return fgetc(fp_input);
   }

   /**
    * Get bits from  XSVF input
    *
    * @param title   Title for debug
    * @param count   Number if bits (rounded up to multiple of 8)
    * @param buff    Buffer for data
    */
   void getBits(unsigned count, uint8_t buff[MAX_BYTES]) {
      unsigned byteCount = (count+7)/8;
      assert(byteCount <= MAX_BYTES);
      unsigned index = 0;
      while(byteCount-->0) {
         buff[index++] = get();
      }
   }

   /**
    * Obtain a 1 byte integer from XSVF input
    *
    * @return Value obtained
    */
   uint32_t get1Byte() {
      uint32_t value = 0;
      value = get();
      return value;
   }

   /**
    * Obtain a 2 byte integer from XSVF input
    *
    * @return Value obtained
    */
   uint32_t get2Bytes() {
      uint32_t value = 0;
      value = get();
      value = (256*value) + get();
      return value;
   }

   /**
    * Obtain a 4 byte integer from XSVF input
    *
    * @return Value obtained
    */
   uint32_t get4Bytes() {
      uint32_t value = 0;
      value = get();
      value = (256*value) + get();
      value = (256*value) + get();
      value = (256*value) + get();
      return value;
   }

   /**
    * Get null terminated string from XSVF input
    * Silently truncates strings that exceed buffer size.
    *
    *  @return null-terminated C string
    */
   const char *getString() {
      char *cp = string_buffer;
      char ch;
      do {
         ch = get();
         if (cp<(string_buffer+sizeof(string_buffer)-1)) {
            *cp++ = ch;
         }
      } while (ch != 0);
      *cp++ = '\0';
      return string_buffer;
   }

   /**
    * Parse a single XSVF command
    *
    * @return false => Sequence not complete
    * @return false => Sequence completes
    */
   bool parse() {
      uint32_t value;
      Command command = (Command)get1Byte();

      fprintf(fp_output, "   /* %-10s      */", getXstateName(currentState));
//      fprintf(fp_output, "   /* %10d      */", byteCounter);

      switch(command) {
         case XCOMPLETE   :
            fprintf(fp_output, " XCOMPLETE,\n");
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
            fprintf(fp_output, " XREPEAT, %d,\n", repeat_count);
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
            fprintf(fp_output, " XRUNTEST, BYTES32(%d), // cycle/ms\n", run_test_time);
            break;

         case XSDRSIZE :
            /*
             * XSDRSIZE length<4 bytes>
             *
             * Specifies the length of all XSDR/XSDRTDO records that follow.
             */
            xsdr_size = get4Bytes();
            fprintf(fp_output, " XSDRSIZE, BYTES32(%d),\n", xsdr_size);
            break;

         case XTDOMASK :
            /*
             * XTDOMASK value<"length" bits>
             *
             * Set TDO mask
             */
            fprintf(fp_output, " XTDOMASK, // (%d bits)\n", xsdr_size);
            getBits(xsdr_size, tdo_mask);
            printBits("tdo_mask", xsdr_size, tdo_mask);
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
            fprintf(fp_output, " XSTATE, %s,\n", getXstateName(state));
            moveTo(state, false);
         }
            break;

         case XENDIR :
            /*
             * XENDIR state<1 byte>
             *
             * Set the XSIR end state to Run-Test/Idle or Pause-IR.
             * The default is Run-Test/Idle.
             */
            value = get1Byte();
            endir_state = value?IR_Pause:Idle;
            fprintf(fp_output, " XENDIR, %s,\n", value?"Ex_IR_Pause":"Ex_Idle");
            break;

         case XENDDR :
            /*
             * XENDDR state<1 byte>
             *
             * Set the XSDR and XSDRTDO end state to Run-Test/Idle or Pause-DR.
             * The default is Run-Test/Idle.
             */
            value = get1Byte();
            enddr_state = value?DR_Pause:Idle;
            fprintf(fp_output, " XENDDR, %s,\n", value?"Ex_DR_Pause":"Ex_Idle");
            break;

         case XCOMMENT :
            /*
             * XCOMMENT char-string-ending-in-zero
             *
             * The XCOMMENT command specifies an arbitrary length character string that ends with a zero byte.
             */
            fprintf(fp_output, " XCOMMENT(%s)\n", getString());
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

            fprintf(fp_output, " XWAIT, %s, %s, BYTES32(%d), // ", getXstateName(wait_state), getXstateName(end_state), wait_time);
            moveTo(wait_state, true);
            moveTo(end_state,  true);
            fprintf(fp_output, "\n");
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
            fprintf(fp_output, " XSIR, %d, // ", value);
            moveTo(IR_Shift, true);
            getBits(value, tdi_value);
            shiftIn(value, tdi_value, true);
            if (run_test_time != 0) {
               moveTo(Idle, true);
               JtagInterface::waitFor(run_test_time);
            }
            else {
               moveTo(endir_state, true);
               if (endir_state == IR_Pause) {
                  assert((currentState == IR_Pause));
               }
            }
            fprintf(fp_output, "\n");
            if (value == 8) {
               switch(tdi_value[0]) {
                  case IDCODE_COMMAND : fprintf(fp_output, "   /*                 */ IDCODE_COMMAND,\n");       break;
                  case BYPASS_COMMAND : fprintf(fp_output, "   /*                 */ BYPASS_COMMAND,\n");       break;
                  case ENABLE_COMMAND : fprintf(fp_output, "   /*                 */ ENABLE_COMMAND,\n");       break;
                  case ERASE_COMMAND  : fprintf(fp_output, "   /*                 */ ERASE_COMMAND,\n");        break;
                  case INIT_COMMAND   : fprintf(fp_output, "   /*                 */ INIT_COMMAND,\n");         break;
                  case CONLD_COMMAND  : fprintf(fp_output, "   /*                 */ CONLD_COMMAND,\n");        break;
                  case VERIFY_COMMAND : fprintf(fp_output, "   /*                 */ VERIFY_COMMAND,\n");       break;
                  default             : fprintf(fp_output, "   /*                 */ 0x%2X,\n", tdi_value[0]);  break;
               }
            }
            else {
               printBits("tdi_value", value, tdi_value);
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
            fprintf(fp_output, " XSIR2(%d) -> %s", value, getXstateName(endir_state));
            getBits(value, tdi_value);
            printBits("tdi_value", value, tdi_value);
            moveTo(IR_Shift, true);
            shiftIn(value, tdi_value, true);
            if (run_test_time != 0) {
               moveTo(Idle, true);
               JtagInterface::waitFor(run_test_time);
            }
            else {
               moveTo(endir_state, true);
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
            fprintf(fp_output, " XSDR(%d) -> %s\n", xsdr_size, getXstateName(endir_state));
            getBits(xsdr_size, tdi_value);
            printBits("tdi_value", xsdr_size, tdi_value);

            moveTo(DR_Shift, true);
            shiftIn(xsdr_size, tdi_value, tdo_value, tdo_mask, true);
            if (run_test_time != 0) {
               moveTo(Idle, true);
               JtagInterface::waitFor(run_test_time);
            }
            else {
               moveTo(endir_state, true);
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
            fprintf(fp_output, " XSDRTDO, // (%d bits)", xsdr_size);
            getBits(xsdr_size, tdi_value);
            getBits(xsdr_size, tdo_value);
            moveTo(DR_Shift, true);
            if (!shiftIn(xsdr_size, tdi_value, tdo_value, tdo_mask, true)) {
               error = "Unexpected TDO value";
               return true;
            }
            if (run_test_time != 0) {
               moveTo(Idle, true);
               JtagInterface::waitFor(run_test_time);
            }
            else {
               moveTo(enddr_state, true);
            }
            fprintf(fp_output, "\n");
            printBits("tdi_value", xsdr_size, tdi_value);
            printBits("tdo_value", xsdr_size, tdo_value);
            break;

         case XSDRB :
            /*
             * XSDRB TDIValue<"length" bits>
             *
             * Go to the shift-DR state and shift in the TDI value. Continue to stay in the shift-DR state at the end
             * of the operation. No comparison of TDO value with the last specified TDOExpected is performed.
             */
            fprintf(fp_output, " XSDRB(%d)\n", xsdr_size);
            getBits(xsdr_size, tdi_value);
            printBits("tdi_value", xsdr_size, tdi_value);
            moveTo(DR_Shift, true);
            shiftIn(xsdr_size, tdi_value, false);
            break;

         case XSDRC :
            /*
             * XSDRC TDIValue<"length" bits>
             *
             * Shift in the TDI value. Continue to stay in the shift-DR state at the end of the operation. No
             * comparison of TDO value with the last specified TDOExpected is performed.
             */
            fprintf(fp_output, " XSDRC(%d)\n", xsdr_size);
            getBits(xsdr_size, tdi_value);
            printBits("tdi_value", xsdr_size, tdi_value);
            shiftIn(xsdr_size, tdi_value, false);
            break;

         case XSDRE :
            /*
             * XSDRE TDIValue<"length" bits>
             *
             * Shift in the TDI value. At the end of the operation, go to the XENDDR state. No comparison of
             * TDO value with the last specified TDOExpected is performed.
             */
            fprintf(fp_output, " XSDRE(%d)\n", xsdr_size);
            assert(currentState==DR_Shift);
            getBits(xsdr_size, tdi_value);
            printBits("tdi_value", xsdr_size, tdi_value);
            shiftIn(xsdr_size, tdi_value, true);
            moveTo(enddr_state, true);
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
            fprintf(fp_output, " XSDRTDOB(%d)\n", xsdr_size);
            getBits(xsdr_size, tdi_value);
            printBits("tdi_value", xsdr_size, tdi_value);
            getBits(xsdr_size, tdo_value);
            printBits("tdo_value", xsdr_size, tdo_value);

            moveTo(DR_Shift, true);
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
            fprintf(fp_output, " XSDRTDOC(%d)\n", xsdr_size);
            getBits(xsdr_size, tdi_value);
            printBits("tdi_value", xsdr_size, tdi_value);
            getBits(xsdr_size, tdo_value);
            printBits("tdo_value", xsdr_size, tdo_value);
            assert(currentState==DR_Shift);
            if (!shiftIn(xsdr_size, tdi_value, tdo_value, false)) {
               error = "TDO not matched";
               return true;
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
            fprintf(fp_output, " XSDRTDOC(%d)\n", xsdr_size);
            getBits(xsdr_size, tdi_value);
            printBits("tdi_value", xsdr_size, tdi_value);
            getBits(xsdr_size, tdo_value);
            printBits("tdo_value", xsdr_size, tdo_value);
            assert(currentState==DR_Shift);
            if (!shiftIn(xsdr_size, tdi_value, tdo_value, true)) {
               error = "TDO not matched";
               return true;
            }
            moveTo(enddr_state, true);
            break;

         default :
            error = "Unknown command";
            return true;
      }
      return false;
   }

public:
   /**
    * Parse XSVF sequence
    */
   void parseAll() {
      static const char *header =
            "#include <stdint.h>\n"
            "#include \"XSVF_Data.h\"\n"
            "#include \"JtagTables.h\"\n"
            "\n"
            "/// Command codes               \n"
            "enum Command {                  \n"
            "   XCOMPLETE    = 0x00,         \n"
            "   XTDOMASK     = 0x01,         \n"
            "   XSIR         = 0x02,         \n"
            "   XSDR         = 0x03,         \n"
            "   XRUNTEST     = 0x04,         \n"
            "   XREPEAT      = 0x07,         \n"
            "   XSDRSIZE     = 0x08,         \n"
            "   XSDRTDO      = 0x09,         \n"
            "   XSETSDRMASKS = 0x0a,         \n"
            "   XSDRINC      = 0x0b,         \n"
            "   XSDRB        = 0x0c,         \n"
            "   XSDRC        = 0x0d,         \n"
            "   XSDRE        = 0x0e,         \n"
            "   XSDRTDOB     = 0x0f,         \n"
            "   XSDRTDOC     = 0x10,         \n"
            "   XSDRTDOE     = 0x11,         \n"
            "   XSTATE       = 0x12,         \n"
            "   XENDIR       = 0x13,         \n"
            "   XENDDR       = 0x14,         \n"
            "   XSIR2        = 0x15,         \n"
            "   XCOMMENT     = 0x16,         \n"
            "   XWAIT        = 0x17,         \n"
            "};                              \n"
            "\n"
            "#define BYTES32(x) (0xFF&((x)>>24)),(0xFF&((x)>>16)),(0xFF&((x)>>8)),(0xFF&(x))\n"
            "   \n"
            "   static constexpr uint8_t Ex_Idle        = 0x00;\n"
            "   static constexpr uint8_t Ex_DR_Pause    = 0x01;\n"
            "   static constexpr uint8_t Ex_IR_Pause    = 0x01;\n"
            "   static constexpr uint8_t IDCODE_COMMAND = 0x01;\n"
            "   static constexpr uint8_t BYPASS_COMMAND = 0xFF;\n"
            "   static constexpr uint8_t ENABLE_COMMAND = 0xE8;\n"
            "   static constexpr uint8_t ERASE_COMMAND  = 0xED;\n"
            "   static constexpr uint8_t INIT_COMMAND   = 0xF0;\n"
            "   static constexpr uint8_t CONLD_COMMAND  = 0xC0;\n"
            "   static constexpr uint8_t VERIFY_COMMAND = 0xEE;\n"
            "   \n"
            "   const uint8_t xsvf_data[] = {\n"
            ;

      static const char *trailer =
            "};";

      fprintf(fp_output, header);

      bool complete = false;
      while (!complete) {
         complete = parse();
      }
      const char *errorMessage = getError();
      fprintf(fp_output, "// Processed %d bytes\n", byteCounter);
      if (errorMessage != nullptr) {
         fprintf(fp_output, "// Error = %s", errorMessage);
      }
      // Move to EOF
      get();
      if (!feof(fp_input)) {
         fprintf(fp_output, "// Not at end-of-file !!\n");
      }
      fprintf(fp_output, trailer);
   }

   /**
    * Constructor
    */
   Xsvf(const char *fileName) {

      fp_input = fopen("CPLD_Tester.xsvf", "rb");
      assert(fp_input != nullptr);
      fp_output = fopen("XSVF_Data.cpp", "wt");
      assert(fp_output != nullptr);
      fprintf(fp_output, "// Created from : \'%s\'\n\n", fileName);

      fseek(fp_input, 0L, SEEK_END);
      unsigned long size = ftell(fp_input);
      rewind(fp_input);

      JtagInterface::enable();
      FILE *of = fopen("XSVF_Data.h", "wt");
      fprintf(of,
            "/*\n"
            " * XSVF_Data2.h\n"
            " *\n"
            " *  Created on: 16 Dec 2019\n"
            " *      Author: podonoghue\n"
            " */\n"
            "\n"
            "#ifndef SOURCES_XSVF_DATA_H_\n"
            "#define SOURCES_XSVF_DATA_H_\n"
            "\n"
            "#include <stdint.h>\n"
            "\n"
            "extern const uint8_t xsvf_data[%lu];\n"
            "\n"
            "#endif /* SOURCES_XSVF_DATA_H_ */\n",
            size
      );
      fclose(of);
   }

   ~Xsvf() {
      fclose(fp_input);
      fclose(fp_output);
   }

};

#if 0
static void listPaths() {
   // List stable-state transitions
   Xsvf::printTransition(Reset, Reset);
   Xsvf::printTransition(Reset, Idle);
   Xsvf::printTransition(Reset, DR_Pause);
   Xsvf::printTransition(Reset, IR_Pause);

   Xsvf::printTransition(Idle, Reset);
   Xsvf::printTransition(Idle, Idle);
   Xsvf::printTransition(Idle, DR_Pause);
   Xsvf::printTransition(Idle, IR_Pause);

   Xsvf::printTransition(DR_Pause, Reset);
   Xsvf::printTransition(DR_Pause, Idle);
   Xsvf::printTransition(DR_Pause, DR_Pause);
   Xsvf::printTransition(DR_Pause, IR_Pause);

   Xsvf::printTransition(IR_Pause, Reset);
   Xsvf::printTransition(IR_Pause, Idle);
   Xsvf::printTransition(IR_Pause, DR_Pause);
   Xsvf::printTransition(IR_Pause, IR_Pause);

   Xsvf::// List consecutive state transitions
   Xsvf::printTransition(Reset,     Idle);
   Xsvf::printTransition(Reset,     Reset);
   Xsvf::printTransition(Idle,      Idle);
   Xsvf::printTransition(Idle,      DR_Select);
   Xsvf::printTransition(DR_Select, DR_Capture);
   Xsvf::printTransition(DR_Select, IR_Select);
   Xsvf::printTransition(DR_Capture,DR_Shift);
   Xsvf::printTransition(DR_Capture,DR_Exit1);
   Xsvf::printTransition(DR_Shift,  DR_Shift);
   Xsvf::printTransition(DR_Shift,  DR_Exit1);
   Xsvf::printTransition(DR_Exit1,  DR_Pause);
   Xsvf::printTransition(DR_Exit1,  DR_Update);
   Xsvf::printTransition(DR_Pause,  DR_Pause);
   Xsvf::printTransition(DR_Pause,  DR_Exit2);
   Xsvf::printTransition(DR_Exit2,  DR_Shift);
   Xsvf::printTransition(DR_Exit2,  DR_Update);
   Xsvf::printTransition(DR_Update, Idle);
   Xsvf::printTransition(DR_Update, DR_Select);

   Xsvf::printTransition(IR_Select, IR_Capture);
   Xsvf::printTransition(IR_Select, Reset);
   Xsvf::printTransition(IR_Capture,IR_Shift);
   Xsvf::printTransition(IR_Capture,IR_Exit1);
   Xsvf::printTransition(IR_Shift,  IR_Shift);
   Xsvf::printTransition(IR_Shift,  IR_Exit1);
   Xsvf::printTransition(IR_Exit1,  IR_Pause);
   Xsvf::printTransition(IR_Exit1,  IR_Update);
   Xsvf::printTransition(IR_Pause,  IR_Pause);
   Xsvf::printTransition(IR_Pause,  IR_Exit2);
   Xsvf::printTransition(IR_Exit2,  IR_Shift);
   Xsvf::printTransition(IR_Exit2,  IR_Update);
   Xsvf::printTransition(IR_Update, Idle);
   Xsvf::printTransition(IR_Update, DR_Select);
}
#endif

int main() {
   const char *filename = "cpld_tester.xsvf";
   Xsvf xsvf(filename);


   xsvf.parseAll();

   return 0;
}
