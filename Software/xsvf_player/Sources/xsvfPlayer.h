/*
 * xsvfPlayer.h
 *
 * XSVF player
 * Plays a XSVF sequence on a JTAG interface
 *
 *  Created on: 22 Dec 2019
 *      Author: podonoghue
 */

#ifndef SOURCES_XSVFPLAYER_H_
#define SOURCES_XSVFPLAYER_H_

#include "JtagTables.h"

/// XSVF Command codes
enum XsvfCommand {
   /**
    * End of sequence
    */
   XCOMPLETE    = 0x00,
   /**
    * XTDOMASK value<"length" bits>
    *
    * Set TDO mask
    */
   XTDOMASK     = 0x01,
   /**
    * XSIR length<1 byte> TDIValue<"length" bits>
    *
    * Go to the Shift-IR state and shift in the TDIValue. If the last XRUNTEST time is non-zero, go to
    * the Run-Test/Idle state and wait for the last specified XRUNTEST time. Otherwise, go to the
    * last specified XENDIR state.
    */
   XSIR         = 0x02,
   /**
    * XSDR TDIValue<"length" bits>
    *
    * Go to the Shift-DR state and shift in TDIValue; compare the TDOExpected value from the last
    * XSDRTDO instruction against the TDO value that was shifted out (use the TDOMask that was
    * generated by the last XTDOMASK instruction). Length comes from the XSDRSIZE instruction.
    */
   XSDR         = 0x03,
   /**
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
   XRUNTEST     = 0x04,
   /**
    * XREPEAT times<1 byte>
    * XREPEAT defines the number of times that TDO is tested against the expected value
    * before the ISP operation is considered a failure.
    *
    * NOT IMPLEMENTED - IGNORED
    */
   XREPEAT      = 0x07,
   /**
    * XSDRSIZE length<4 bytes>
    *
    * Specifies the length of all XSDR/XSDRTDO records that follow.
    */
   XSDRSIZE     = 0x08,
   /**
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
   XSDRTDO      = 0x09,
   /**
    * XSETSDRMASKS addressMask<"length" bits> dataMask<"length" bits>
    *
    * NOT IMPLEMENTED - ERROR
    */
   XSETSDRMASKS = 0x0A,
   /**
    * XSDRINC startAddress<"length" bits> numTimes<1 byte>
    *         data[1]<"length2" bits> ...data[numTimes]<"length2" bits>
    *
    * NOT IMPLEMENTED - ERROR
    */
   XSDRINC      = 0x0B,
   /**
    * XSDRB TDIValue<"length" bits>
    *
    * Go to the shift-DR state and shift in the TDI value. Continue to stay in the shift-DR state at the end
    * of the operation. No comparison of TDO value with the last specified TDOExpected is performed.
    */
   XSDRB        = 0x0C,
   /**
    * XSDRC TDIValue<"length" bits>
    *
    * Shift in the TDI value. Continue to stay in the shift-DR state at the end of the operation. No
    * comparison of TDO value with the last specified TDOExpected is performed.
    */
   XSDRC        = 0x0D,
   /**
    * XSDRE TDIValue<"length" bits>
    *
    * Shift in the TDI value. At the end of the operation, go to the XENDDR state. No comparison of
    * TDO value with the last specified TDOExpected is performed.
    */
   XSDRE        = 0x0E,
   /**
    * XSDRTDOB TDIValue<"length" bits> TDOExpected<"length" bits>
    *
    * Go to the shift-DR state and shift in TDI value; compare the TDOExpected value against the
    * TDO value that was shifted out. TDOMask is not applied. All bits of TDO are compared with the
    * TDOExpected. Length comes from the XSDRSIZE instruction.
    * Because this instruction is primarily meant for FPGAs, if the TDO value does not match
    * TDOExpected, the programming is stopped with an error message. At the end of the
    * operations, continue to stay in the SHIFT-DR state.
    */
   XSDRTDOB     = 0x0F,
   /**
    * XSDRTDOC TDIValue<"length" bits> TDOExpected<"length" bits>
    *
    * Shift in the TDI value; compare the TDOExpected value against the TDO value that was shifted
    * out. Length comes from the XSDRSIZE instruction. TDOMask is not applied. All bits of TDO are
    * compared with the TDOExpected.
    * If the TDO value does not match TDOExpected, stop the programming operation with an error
    * message. At the end of the operation, continue to stay in the SHIFT-DR state.
    */
   XSDRTDOC     = 0x10,
   /**
    * XSDRTDOE TDIValue<"length" bits> TDOExpected<"length" bits>
    *
    * Shift in the TDI value; compare the TDOExpected value against the TDO value that was shifted
    * out. Length comes from the last XSDSIZE instruction. TDOMask is not applied. All bits of TDO
    * are compared with the TDOExpected.
    * If the TDO value does not match the TDOExpected, stop the programming operations with an
    * error message. At the end of the operation, go to the XENDDR state.
    */
   XSDRTDOE     = 0x11,
   /**
    * XSTATE state<1 byte>
    *
    * If the state is Test-Logic-Reset, then force the TAP to the Test-Logic-Reset state via the
    * guaranteed TAP reset sequence: hold TMS High and apply a minimum of five TCK cycles. For
    * non-zero state values, if the TAP is already in the specified state, then do nothing. Otherwise,
    * transition the TAP to the next specified state.
    */
   XSTATE       = 0x12,
   /**
    * XENDIR state<1 byte>
    *
    * Set the XSIR end state to Run-Test/Idle or Pause-IR.
    * The default is Run-Test/Idle.
    */
   XENDIR       = 0x13,
   /**
    * XENDDR state<1 byte>
    *
    * Set the XSDR and XSDRTDO end state to Run-Test/Idle or Pause-DR.
    * The default is Run-Test/Idle.
    */
   XENDDR       = 0x14,
   /**
    * XSIR2 length<2 bytes> TDIValue<"length" bits>
    *
    * Go to the Shift-IR state and shift in the TDIValue. If the last XRUNTEST time is non-zero, go to
    * the Run-Test/Idle state and wait for the last specified XRUNTEST time. Otherwise, go to the
    * last specified XENDIR state.
    */
   XSIR2        = 0x15,
   /**
    * XCOMMENT char-string-ending-in-zero
    *
    * The XCOMMENT command specifies an arbitrary length character string that ends with a zero byte.
    */
   XCOMMENT     = 0x16,
   /**
    * XWAIT wait_state<1 byte> end_state<1 byte> wait_time<4 bytes>
    *
    * Go to the TAP wait_state, stay in the TAP wait_state for a minimum of wait_time (microseconds),
    * and finally go to the TAP end_state to complete the command.
    */
   XWAIT        = 0x17,

   /**
    * XSDR_TDO_CAPTURE <size-in-bits> <tdi-value>
    *
    * Capture TDO value
    */
   XSDR_TDOCAP = 0xF0,
};

static constexpr uint8_t Ex_Idle         = 0x00;
static constexpr uint8_t Ex_DR_Pause     = 0x01;
static constexpr uint8_t Ex_IR_Pause     = 0x01;
static constexpr uint8_t IDCODE_COMMAND  = 0x01;
static constexpr uint8_t BYPASS_COMMAND  = 0xFF;
static constexpr uint8_t ENABLE_COMMAND  = 0xE8;
static constexpr uint8_t ERASE_COMMAND   = 0xED;
static constexpr uint8_t INIT_COMMAND    = 0xF0;
static constexpr uint8_t CONLD_COMMAND   = 0xC0;
static constexpr uint8_t VERIFY_COMMAND  = 0xEE;
static constexpr uint8_t PROGRAM_COMMAND = 0xEA;

/// Used for iterating states
inline Xstate &operator++ (Xstate& d) {
   d = static_cast<Xstate>((static_cast<int>(d) + 1));
   return d;
}

class XsvfPlayer {
protected:

   /// Maximum number of bits to shift in/out in a single command
   static constexpr unsigned MAX_BITS  = 2048;

   /// Maximum number of bytes to shift in/out in a single command
   static constexpr unsigned MAX_BYTES = (MAX_BITS+7)/8;

   /// Maximum string length
   static constexpr unsigned MAX_STRING  = 100;

   // Current JTAG state
   Xstate      currentState = Reset;

   // State to move to after XSIR, XSIR2 (either IR_Pause or Idle)
   Xstate      endir_state = Xstate::Idle;

   // State to move to after XSDR, XSDRE, XSDRTDO, XSDRTDOE (either DR_Pause or Idle)
   Xstate      enddr_state = Xstate::Idle;

   // Time to remain in Run-test-idle state
   uint32_t    run_test_time = 0;

   // Number of times to retry TDO tests
   uint32_t    repeat_count = 32;

   // Size for XSDR, XSDRTDO commands
   uint32_t    xsdr_size = 0;

   // TDI Buffer [xsdr_size] - Data to shift in
   uint8_t     tdi_value[MAX_BYTES];

   // TDO Buffer [xsdr_size] - TDO value to check / collect
   uint8_t     tdo_mask[MAX_BYTES];

   // TDO Buffer [xsdr_size] - Mask applied when checking TDO
   uint8_t     tdo_value[MAX_BYTES];

   // '\0' terminated comment string
   char        string_buffer[MAX_STRING] = {};

   // Size of xsvf_data
   unsigned   xsvf_data_size = 0;

   // Error message
   const char *error = nullptr;

   // Count of bytes processed
   unsigned    byteCounter = 0;

   // Count of bits in current shift operation (for debug)
   unsigned    bitCounter = 0;

   /**
    * Get command name as string
    *
    * @param command Command code
    *
    * @return Pointer to static string
    */
   static const char *getXCommandName(XsvfCommand command);

   /**
    * Get state name as string
    *
    * @param state State code
    *
    * @return Pointer to static string
    */
   static const char *getXstateName(Xstate state);

   /**
    * Print buffer contents in binary
    *
    * @param title Title to prefix each line
    * @param size Size of buffer
    * @param buff Buffer to print
    */
   static void printBits(const char* title, unsigned size, const uint8_t *buff);

   /**
    * Print path leading from 'from' to 'to'
    *
    * @param from Starting state
    * @param to   Ending state
    */
   static void printTransition(Xstate from, Xstate to);

   /**
    * Shift in value
    * Assumes in DR_Shift or IR_Shift state
    *
    * @param size             Number of bits to shift
    * @param tdi_value        Buffer for TDI value to shift in
    * @param tdo_value        Buffer for TDO value shifted out
    * @param exit_shift_state Whether to exit IR/DR_Shift at end of shift
    */
   void shiftInOut(unsigned size, uint8_t *tdi_value, uint8_t *tdo_value, bool exit_shift_state);

   /**
    * Shift in value
    * Assumes in DR_Shift or IR_Shift state
    *
    * @param size             Number of bits to shift
    * @param tdi_value        Dummy TDI value to shift in
    * @param tdo_value        Buffer for TDO value shifted out
    * @param exit_shift_state Whether to exit IR/DR_Shift at end of shift
    */
   void shiftOut(unsigned size, bool tdi_value, uint8_t *tdo_value, bool exit_shift_state);

   /**
    * Shift in value
    * Assumes in DR_Shift or IR_Shift state
    *
    * @param size             Number of bits to shift
    * @param tdi_value        TDI value to shift in
    * @param exit_shift_state Whether to exit IR/DR_Shift at end of shift
    */
   void shiftIn(unsigned size, uint8_t *tdi_value, bool exit_shift_state);

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
   bool shiftIn(unsigned size, uint8_t *tdi_value, uint8_t *tdo_value, uint8_t *tdo_mask, bool exit_shift_state);

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
   bool shiftIn(unsigned size, uint8_t *tdi_value, uint8_t *tdo_value, bool exit_shift_state);

   /**
    * Determine the next state based upon current state and TMS value
    * This does not affect the hardware state
    *
    * @param tms  TMS value controlling state transition
    *
    * @return Calculated state
    */
   Xstate calculateNextState(bool tms);

   /**
    * Move to new state.
    * This outputs signals on TMS, TDO, TCLK to change physical state
    *
    * @param to State to move to
    */
   void moveTo(Xstate to, bool isXSTATE=false);

   /**
    * Get bits from  XSVF input
    *
    * @param title   Title for debug
    * @param count   Number if bits (rounded up to multiple of 8)
    * @param buff    Buffer for data
    */
   void getBits(unsigned count, uint8_t buff[MAX_BYTES]);

   /**
    * Get single byte from XSVF input
    *
    * @return Byte obtained
    */
   virtual uint8_t get() = 0;

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
    * Get null terminated string from XSVF input into string buffer.
    * Silently truncates strings that exceed buffer size.
    *
    *  @return Number of character in string (including '\0')
    */
   unsigned getString() {
      char *cp = string_buffer;
      char ch;
      do {
         ch = get();
         if (cp<(string_buffer+sizeof(string_buffer)-1)) {
            *cp++ = ch;
         }
      } while (ch != '\0');
      *cp++ = '\0';
      return cp-string_buffer;
   }

   /**
    * Play a single XSVF command on hardware
    *
    * @return false => Sequence not complete
    * @return false => Sequence completed (XCOMPLETE or no bytes left)
    */
   bool play();

public:
   /**
    * Play XSVF sequence
    *
    * @return true  XSVF sequence completed without error
    * @return false Error detected during XSVF sequence
    */
   bool playAll();

   /**
    * Get error string
    *
    * @return nullptr => No error
    * @return else    => Error description
    */
   const char *getError() const {
      return error;
   }

   /**
    * Get bit count for current shift sequence
    */
   unsigned getBitcount() const {
      return bitCounter;
   }

   /**
    * Get TDO buffer
    *
    * @return pointer to internal buffer
    */
   const uint8_t *getTdoBuff() const {
      return tdo_value;
   }

   /**
    * Constructor
    *
    * @param xsvf_data_size   Size of XSVF data
    */
   XsvfPlayer(unsigned xsvf_data_size) : xsvf_data_size(xsvf_data_size) {
   }

   /**
    * Destructor
    */
   virtual ~XsvfPlayer() {}
};

class XsvfPlayer_Array : public XsvfPlayer {

   // XSVF Data buffer
   const uint8_t *xsvf_data;

   /**
    * Get single byte from XSVF input
    *
    * @return Byte obtained
    */
   virtual uint8_t get() override {
      if (byteCounter>xsvf_data_size) {
         return XCOMPLETE;
      }
      return xsvf_data[byteCounter++];
   }

public:
   /**
    * Constructor
    * Create a XSVF player based on an array
    *
    * @param xsvf_data_size   Size of XSVF data
    * @param xsvf_data        Data array for XSVF sequence to play
    */
   XsvfPlayer_Array(unsigned xsvf_data_size, const uint8_t *xsvf_data) :
      XsvfPlayer(xsvf_data_size), xsvf_data(xsvf_data) {
   }

   ~XsvfPlayer_Array(){}
};

#endif /* SOURCES_XSVFPLAYER_H_ */
