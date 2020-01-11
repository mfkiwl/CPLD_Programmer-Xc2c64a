// Created from : 'cpld_tester'

#include <stdint.h>
#include "cpld_tester_xsvf.h"
#include "JtagTables.h"

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

#define BYTES32(x) ((uint8_t)((x)>>24)),((uint8_t)((x)>>16)),((uint8_t)((x)>>8)),((uint8_t)(x))

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

const uint8_t cpld_tester_xsvf[22928] = {
   /* Reset           */ XREPEAT, 0,
   /* Reset           */ XENDIR, Ex_Idle,
   /* Reset           */ XENDDR, Ex_Idle,
   /* Reset           */ XSTATE, Reset, // *** Reset ***
   /* Reset           */ XSTATE, Idle,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ IDCODE_COMMAND, // 0x01
   /* Idle            */ XSDRSIZE, BYTES32(32),
   /* Idle            */ XTDOMASK,
   /* tdo_mask     32:*/ 0x0F, 0xFF, 0x8F, 0xFF, 
   /* Idle            */ XRUNTEST, BYTES32(0), // cycle/ms
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(32)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00000000 00000000 00000000 00000000  
   /* tdi_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0xF6, 0xE5, 0xF0, 0x93, 
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ IDCODE_COMMAND, // 0x01
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(32)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00000000 00000000 00000000 00000000  
   /* tdi_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0xF6, 0xE5, 0xF0, 0x93, 
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ IDCODE_COMMAND, // 0x01
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(32)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00000000 00000000 00000000 00000000  
   /* tdi_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0xF6, 0xE5, 0xF0, 0x93, 
   /* Idle            */ XREPEAT, 0,
   /* Idle            */ XREPEAT, 0,
   /* Idle            */ XENDIR, Ex_Idle,
   /* Idle            */ XENDDR, Ex_Idle,
   /* Idle            */ XSTATE, Reset, // *** Reset ***
   /* Reset           */ XSTATE, Idle,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSDRSIZE, BYTES32(1),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      1:*/ 0x00, 
   /* Idle            */ XRUNTEST, BYTES32(0), // cycle/ms
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(1)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 0  
   /* tdi_value     1:*/ 0x00, 
   /* tdo_value     1:*/ 0x00, 
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ IDCODE_COMMAND, // 0x01
   /* Idle            */ XSDRSIZE, BYTES32(32),
   /* Idle            */ XTDOMASK,
   /* tdo_mask     32:*/ 0x0F, 0xFF, 0x8F, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(32)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00000000 00000000 00000000 00000000  
   /* tdi_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0xF6, 0xE5, 0xF0, 0x93, 
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ IDCODE_COMMAND, // 0x01
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(32)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00000000 00000000 00000000 00000000  
   /* tdi_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0xF6, 0xE5, 0xF0, 0x93, 
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ ENABLE_COMMAND, // 0xE8
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ ERASE_COMMAND, // 0xED
   /* IR_Pause        */ XENDIR, Ex_Idle,
   /* IR_Pause        */ XSTATE, IR_Exit2,
   /* IR_Exit2        */ XSTATE, IR_Update,
   /* IR_Update       */ XSTATE, DR_Select,
   /* DR_Select       */ XSTATE, DR_Capture,
   /* DR_Capture      */ XSTATE, DR_Exit1,
   /* DR_Exit1        */ XSTATE, DR_Pause,
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XSTATE, DR_Exit2,
   /* DR_Exit2        */ XSTATE, DR_Update,
   /* DR_Update       */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100000), // -Wait(100000)
   /* Idle            */ XSTATE, DR_Select,
   /* DR_Select       */ XSTATE, DR_Capture,
   /* DR_Capture      */ XSTATE, DR_Exit1,
   /* DR_Exit1        */ XSTATE, DR_Pause,
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(5000), // -Wait(5000)
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(1), // -DR_Exit2-DR_Update-Idle-Wait(1)
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* IR_Pause        */ XSTATE, IR_Exit2,
   /* IR_Exit2        */ XSTATE, IR_Update,
   /* IR_Update       */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(20), // -Wait(20)
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* IR_Pause        */ XSTATE, IR_Exit2,
   /* IR_Exit2        */ XSTATE, IR_Update,
   /* IR_Update       */ XSTATE, DR_Select,
   /* DR_Select       */ XSTATE, DR_Capture,
   /* DR_Capture      */ XSTATE, DR_Exit1,
   /* DR_Exit1        */ XSTATE, DR_Update,
   /* DR_Update       */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(800), // -Wait(800)
   /* Idle            */ XENDIR, Ex_Idle,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ CONLD_COMMAND, // 0xC0
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ CONLD_COMMAND, // 0xC0
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ ENABLE_COMMAND, // 0xE8
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ PROGRAM_COMMAND, // 0xEA
   /* IR_Pause        */ XSDRSIZE, BYTES32(281),
   /* IR_Pause        */ XTDOMASK,
   /* tdo_mask    281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask    224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask    160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask     96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask     32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* IR_Pause        */ XSDRTDO, // -IR_Exit2-IR_Update-DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 10111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111011 11111111 10111111 11111111 11101111 10111110 11111110 
   // tdi_value   128: 01111000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11011111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11000000 0  
   /* tdi_value   281:*/ 0x00, 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0x1E, 0x7F, 0x7D, 0xF7, 0xFF, 
   /* tdi_value    96:*/ 0xFD, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFD, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XENDIR, Ex_Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11011111 01111111 11111111 11111111 01111101 11111111 11111111 11111110 
   // tdi_value   128: 00110110 01111111 11111111 11111110 11111011 11111111 11111111 11111111 
   // tdi_value   192: 11111111 10111110 11111011 11101111 11011111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00000000 1  
   /* tdi_value   281:*/ 0x01, 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 
   /* tdi_value   224:*/ 0xF7, 0xDF, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 
   /* tdi_value   160:*/ 0x7F, 0xFF, 0xFE, 0x6C, 0x7F, 0xFF, 0xFF, 0xBE, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFE, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01000001 1  
   /* tdi_value   281:*/ 0x01, 0x82, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 10111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111011 11111111 10111111 11111111 11101111 10111110 11111110 
   // tdi_value   128: 01111000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111110 11111011 11101111 11011111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11000001 0  
   /* tdi_value   281:*/ 0x00, 0x83, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 
   /* tdi_value   224:*/ 0xF7, 0xDF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0x1E, 0x7F, 0x7D, 0xF7, 0xFF, 
   /* tdi_value    96:*/ 0xFD, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFD, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 10111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111011 11111111 10111111 11111111 11101111 10111110 11111100 
   // tdi_value   128: 01111010 01111111 11111111 11111111 11111111 11111111 11111110 11111011 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00000011 0  
   /* tdi_value   281:*/ 0x00, 0xC0, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x7F, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0x5E, 0x3F, 0x7D, 0xF7, 0xFF, 
   /* tdi_value    96:*/ 0xFD, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFD, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01000011 1  
   /* tdi_value   281:*/ 0x01, 0xC2, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 10111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111011 11111111 10111111 11111111 11101111 11011110 11111110 
   // tdi_value   128: 01100110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 10111110 11111011 11101111 11011111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11000010 1  
   /* tdi_value   281:*/ 0x01, 0x43, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 
   /* tdi_value   224:*/ 0xF7, 0xDF, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0x66, 0x7F, 0x7B, 0xF7, 0xFF, 
   /* tdi_value    96:*/ 0xFD, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFD, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00000010 0  
   /* tdi_value   281:*/ 0x00, 0x40, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11011111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111011 11111111 11011111 11111111 11110111 10111111 01111110 
   // tdi_value   128: 01001110 01111111 11111111 11111111 11111111 11101111 10111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01000110 0  
   /* tdi_value   281:*/ 0x00, 0x62, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF7, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0x72, 0x7E, 0xFD, 0xEF, 0xFF, 
   /* tdi_value    96:*/ 0xFB, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFB, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111101 11110111 11111111 11111101 11110111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111110 
   // tdi_value   128: 00011110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11101111 11111111 11111111 11111111 11111110 11111011 11101111 11111111 
   // tdi_value   256: 11111111 10010011 11000110 1  
   /* tdi_value   281:*/ 0x01, 0x63, 0xC9, 0xFF, 0xFF, 0xF7, 0xDF, 0x7F, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0x78, 0x7F, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xBF, 0xFF, 0xEF, 
   /* tdi_value    32:*/ 0xBF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01011111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 01111110 
   // tdi_value   128: 11111010 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111011 11000111 1  
   /* tdi_value   281:*/ 0x01, 0xE3, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0x5F, 0x7E, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFA, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111111 01000111 0  
   /* tdi_value   281:*/ 0x00, 0xE2, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11000101 0  
   /* tdi_value   281:*/ 0x00, 0xA3, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111011 11000101 1  
   /* tdi_value   281:*/ 0x01, 0xA3, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111111 01000100 1  
   /* tdi_value   281:*/ 0x01, 0x22, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111101 11111111 10111111 11111111 11110111 10111111 11111110 
   // tdi_value   128: 01101100 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11101111 11011111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11000100 0  
   /* tdi_value   281:*/ 0x00, 0x23, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 
   /* tdi_value   224:*/ 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0x36, 0x7F, 0xFD, 0xEF, 0xFF, 
   /* tdi_value    96:*/ 0xFD, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111011 11001100 0  
   /* tdi_value   281:*/ 0x00, 0x33, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111111 01001100 1  
   /* tdi_value   281:*/ 0x01, 0x32, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11001101 1  
   /* tdi_value   281:*/ 0x01, 0xB3, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111011 11001101 0  
   /* tdi_value   281:*/ 0x00, 0xB3, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111111 01001111 0  
   /* tdi_value   281:*/ 0x00, 0xF2, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11001111 1  
   /* tdi_value   281:*/ 0x01, 0xF3, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111011 11001110 1  
   /* tdi_value   281:*/ 0x01, 0x73, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11101001 10100111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111111 01001110 0  
   /* tdi_value   281:*/ 0x00, 0x72, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xE5, 0x97, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 00111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11001010 0  
   /* tdi_value   281:*/ 0x00, 0x53, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFC, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 10111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00001010 1  
   /* tdi_value   281:*/ 0x01, 0x50, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFD, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10111110 01011111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01001011 1  
   /* tdi_value   281:*/ 0x01, 0xD2, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFA, 0x7D, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 00111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11001011 0  
   /* tdi_value   281:*/ 0x00, 0xD3, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFC, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 01110111 01111111 11111111 11111111 11111011 11111111 11111111 11111111 
   // tdi_value   192: 11111111 10111110 11111011 11101111 11011111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00001001 0  
   /* tdi_value   281:*/ 0x00, 0x90, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 
   /* tdi_value   224:*/ 0xF7, 0xDF, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7D, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 01111101 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111011 11101111 11011111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01001001 1  
   /* tdi_value   281:*/ 0x01, 0x92, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 
   /* tdi_value   224:*/ 0xF7, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 01111111 10111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111011 11111111 10111111 11111111 11101111 10111110 11111110 
   // tdi_value   128: 11111010 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11001000 1  
   /* tdi_value   281:*/ 0x01, 0x13, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0x5F, 0x7F, 0x7D, 0xF7, 0xFF, 
   /* tdi_value    96:*/ 0xFD, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFD, 0xFE, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00001000 0  
   /* tdi_value   281:*/ 0x00, 0x10, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFF, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01011000 0  
   /* tdi_value   281:*/ 0x00, 0x1A, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7D, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11011000 1  
   /* tdi_value   281:*/ 0x01, 0x1B, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00011001 1  
   /* tdi_value   281:*/ 0x01, 0x98, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01011001 0  
   /* tdi_value   281:*/ 0x00, 0x9A, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11011011 0  
   /* tdi_value   281:*/ 0x00, 0xDB, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00011011 1  
   /* tdi_value   281:*/ 0x01, 0xD8, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01011010 1  
   /* tdi_value   281:*/ 0x01, 0x5A, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11011010 0  
   /* tdi_value   281:*/ 0x00, 0x5B, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111011 11011110 0  
   /* tdi_value   281:*/ 0x00, 0x7B, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFF, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111111 01011110 1  
   /* tdi_value   281:*/ 0x01, 0x7A, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7D, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11011111 1  
   /* tdi_value   281:*/ 0x01, 0xFB, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111011 11011111 0  
   /* tdi_value   281:*/ 0x00, 0xFB, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFF, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111111 01011101 0  
   /* tdi_value   281:*/ 0x00, 0xBA, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7D, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11011101 1  
   /* tdi_value   281:*/ 0x01, 0xBB, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFF, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110110 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111011 11011100 1  
   /* tdi_value   281:*/ 0x01, 0x3B, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFF, 0x6F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10111111 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 01011100 0  
   /* tdi_value   281:*/ 0x00, 0x3A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0xFD, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11010100 0  
   /* tdi_value   281:*/ 0x00, 0x2B, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111101 11110111 11111111 11111111 11111111 
   // tdi_value    64: 11011111 11111111 11111111 11111111 11111111 11111111 11111111 11111110 
   // tdi_value   128: 10111110 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00010100 1  
   /* tdi_value   281:*/ 0x01, 0x28, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0x7D, 0x7F, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0xEF, 
   /* tdi_value    32:*/ 0xBF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01010101 1  
   /* tdi_value   281:*/ 0x01, 0xAA, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11010101 0  
   /* tdi_value   281:*/ 0x00, 0xAB, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00010111 0  
   /* tdi_value   281:*/ 0x00, 0xE8, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01010111 1  
   /* tdi_value   281:*/ 0x01, 0xEA, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11011111 11111101 11110111 11011111 11111110 
   // tdi_value   128: 00011110 01111111 11111111 11111110 11111011 11111111 10111110 11111011 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11010110 1  
   /* tdi_value   281:*/ 0x01, 0x6B, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x7D, 0xFF, 0xDF, 
   /* tdi_value   160:*/ 0x7F, 0xFF, 0xFE, 0x78, 0x7F, 0xFB, 0xEF, 0xBF, 
   /* tdi_value    96:*/ 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00010110 0  
   /* tdi_value   281:*/ 0x00, 0x68, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 01011111 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111011 11111111 11111110 11111011 11101111 11111111 
   // tdi_value   256: 11111111 10100000 01010010 0  
   /* tdi_value   281:*/ 0x00, 0x4A, 0x05, 0xFF, 0xFF, 0xF7, 0xDF, 0x7F, 
   /* tdi_value   224:*/ 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFE, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10000011 11010010 1  
   /* tdi_value   281:*/ 0x01, 0x4B, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 11010011 1  
   /* tdi_value   281:*/ 0x01, 0xCB, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00010011 0  
   /* tdi_value   281:*/ 0x00, 0xC8, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10000011 11010001 0  
   /* tdi_value   281:*/ 0x00, 0x8B, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 11010001 1  
   /* tdi_value   281:*/ 0x01, 0x8B, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00010000 1  
   /* tdi_value   281:*/ 0x01, 0x08, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11010000 0  
   /* tdi_value   281:*/ 0x00, 0x0B, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00110000 0  
   /* tdi_value   281:*/ 0x00, 0x0C, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01110000 1  
   /* tdi_value   281:*/ 0x01, 0x0E, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10000011 11110001 1  
   /* tdi_value   281:*/ 0x01, 0x8F, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 11110001 0  
   /* tdi_value   281:*/ 0x00, 0x8F, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00110011 0  
   /* tdi_value   281:*/ 0x00, 0xCC, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10000011 11110011 1  
   /* tdi_value   281:*/ 0x01, 0xCF, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 11110010 1  
   /* tdi_value   281:*/ 0x01, 0x4F, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00110010 0  
   /* tdi_value   281:*/ 0x00, 0x4C, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10000011 11110110 0  
   /* tdi_value   281:*/ 0x00, 0x6F, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 10011111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 11110110 1  
   /* tdi_value   281:*/ 0x01, 0x6F, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00110111 1  
   /* tdi_value   281:*/ 0x01, 0xEC, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11110111 0  
   /* tdi_value   281:*/ 0x00, 0xEF, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00110101 0  
   /* tdi_value   281:*/ 0x00, 0xAC, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01110101 1  
   /* tdi_value   281:*/ 0x01, 0xAE, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11110100 1  
   /* tdi_value   281:*/ 0x01, 0x2F, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00110100 0  
   /* tdi_value   281:*/ 0x00, 0x2C, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01111100 0  
   /* tdi_value   281:*/ 0x00, 0x3E, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11111100 1  
   /* tdi_value   281:*/ 0x01, 0x3F, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00111101 1  
   /* tdi_value   281:*/ 0x01, 0xBC, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01111101 0  
   /* tdi_value   281:*/ 0x00, 0xBE, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10000011 11111111 0  
   /* tdi_value   281:*/ 0x00, 0xFF, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 11111111 1  
   /* tdi_value   281:*/ 0x01, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00111110 1  
   /* tdi_value   281:*/ 0x01, 0x7C, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11111110 0  
   /* tdi_value   281:*/ 0x00, 0x7F, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00111010 0  
   /* tdi_value   281:*/ 0x00, 0x5C, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01111010 1  
   /* tdi_value   281:*/ 0x01, 0x5E, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110010 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10010011 11111011 1  
   /* tdi_value   281:*/ 0x01, 0xDF, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x4F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00111011 0  
   /* tdi_value   281:*/ 0x00, 0xDC, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 10000001 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10100000 01111001 0  
   /* tdi_value   281:*/ 0x00, 0x9E, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x81, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11110000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10000011 11111001 1  
   /* tdi_value   281:*/ 0x01, 0x9F, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x0F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 11111000 1  
   /* tdi_value   281:*/ 0x01, 0x1F, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7F, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00111110 01111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10011111 00111000 0  
   /* tdi_value   281:*/ 0x00, 0x1C, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFE, 0x7C, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11101000 0  
   /* tdi_value   281:*/ 0x00, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11101000 1  
   /* tdi_value   281:*/ 0x01, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* IR_Pause        */ XSTATE, IR_Exit2,
   /* IR_Exit2        */ XSTATE, IR_Update,
   /* IR_Update       */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(20), // -Wait(20)
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* IR_Pause        */ XSTATE, IR_Exit2,
   /* IR_Exit2        */ XSTATE, IR_Update,
   /* IR_Update       */ XSTATE, DR_Select,
   /* DR_Select       */ XSTATE, DR_Capture,
   /* DR_Capture      */ XSTATE, DR_Exit1,
   /* DR_Exit1        */ XSTATE, DR_Update,
   /* DR_Update       */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(800), // -Wait(800)
   /* Idle            */ XENDIR, Ex_Idle,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ CONLD_COMMAND, // 0xC0
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ CONLD_COMMAND, // 0xC0
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ ENABLE_COMMAND, // 0xE8
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ ENABLE_COMMAND, // 0xE8
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ VERIFY_COMMAND, // 0xEE
   /* IR_Pause        */ XENDDR, Ex_DR_Pause,
   /* IR_Pause        */ XSDRSIZE, BYTES32(7),
   /* IR_Pause        */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* IR_Pause        */ XSDRTDO, // -IR_Exit2-IR_Update-DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0000000  
   /* tdi_value     7:*/ 0x00, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XENDIR, Ex_Idle,
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x1E, 0x7F, 0x7D, 0xF7, 0xFF, 0xFD, 
   /* tdo_value    88:*/ 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFD, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0000001  
   /* tdi_value     7:*/ 0x40, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xF7, 
   /* tdo_value   216:*/ 0xDF, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0x7F, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x6C, 0x7F, 0xFF, 0xFF, 0xBE, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFE, 0xFB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0000011  
   /* tdi_value     7:*/ 0x60, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0000010  
   /* tdi_value     7:*/ 0x20, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xF7, 
   /* tdo_value   216:*/ 0xDF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x1E, 0x7F, 0x7D, 0xF7, 0xFF, 0xFD, 
   /* tdo_value    88:*/ 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFD, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0000110  
   /* tdi_value     7:*/ 0x30, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xDF, 0x7F, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x5E, 0x3F, 0x7D, 0xF7, 0xFF, 0xFD, 
   /* tdo_value    88:*/ 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFD, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0000111  
   /* tdi_value     7:*/ 0x70, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0000101  
   /* tdi_value     7:*/ 0x50, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xF7, 
   /* tdo_value   216:*/ 0xDF, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x66, 0x7F, 0x7B, 0xF7, 0xFF, 0xFD, 
   /* tdo_value    88:*/ 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFD, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0000100  
   /* tdi_value     7:*/ 0x10, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0001100  
   /* tdi_value     7:*/ 0x18, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF7, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x72, 0x7E, 0xFD, 0xEF, 0xFF, 0xFB, 
   /* tdo_value    88:*/ 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFB, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0001101  
   /* tdi_value     7:*/ 0x58, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xF7, 0xDF, 0x7F, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x78, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xEF, 0xBF, 0xFF, 0xEF, 0xBF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0001111  
   /* tdi_value     7:*/ 0x78, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0x5F, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFA, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0001110  
   /* tdi_value     7:*/ 0x38, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0001010  
   /* tdi_value     7:*/ 0x28, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0001011  
   /* tdi_value     7:*/ 0x68, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0001001  
   /* tdi_value     7:*/ 0x48, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0001000  
   /* tdi_value     7:*/ 0x08, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xF7, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x36, 0x7F, 0xFD, 0xEF, 0xFF, 0xFD, 
   /* tdo_value    88:*/ 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0011000  
   /* tdi_value     7:*/ 0x0C, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0011001  
   /* tdi_value     7:*/ 0x4C, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0011011  
   /* tdi_value     7:*/ 0x6C, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0011010  
   /* tdi_value     7:*/ 0x2C, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0011110  
   /* tdi_value     7:*/ 0x3C, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0011111  
   /* tdi_value     7:*/ 0x7C, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0011101  
   /* tdi_value     7:*/ 0x5C, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0011100  
   /* tdi_value     7:*/ 0x1C, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x1F, 0xF8, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xE5, 0x97, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0010100  
   /* tdi_value     7:*/ 0x14, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x1F, 0x80, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFC, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0010101  
   /* tdi_value     7:*/ 0x54, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFD, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0010111  
   /* tdi_value     7:*/ 0x74, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFA, 0x7D, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0010110  
   /* tdi_value     7:*/ 0x34, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFC, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0010010  
   /* tdi_value     7:*/ 0x24, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xF7, 
   /* tdo_value   216:*/ 0xDF, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7D, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0010011  
   /* tdi_value     7:*/ 0x64, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xF7, 
   /* tdo_value   216:*/ 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0010001  
   /* tdi_value     7:*/ 0x44, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0x5F, 0x7F, 0x7D, 0xF7, 0xFF, 0xFD, 
   /* tdo_value    88:*/ 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFD, 0xFE, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0010000  
   /* tdi_value     7:*/ 0x04, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFF, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0110000  
   /* tdi_value     7:*/ 0x06, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7D, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0110001  
   /* tdi_value     7:*/ 0x46, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0110011  
   /* tdi_value     7:*/ 0x66, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0110010  
   /* tdi_value     7:*/ 0x26, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0110110  
   /* tdi_value     7:*/ 0x36, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0110111  
   /* tdi_value     7:*/ 0x76, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0110101  
   /* tdi_value     7:*/ 0x56, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0110100  
   /* tdi_value     7:*/ 0x16, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0111100  
   /* tdi_value     7:*/ 0x1E, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFF, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0111101  
   /* tdi_value     7:*/ 0x5E, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7D, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0111111  
   /* tdi_value     7:*/ 0x7E, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0111110  
   /* tdi_value     7:*/ 0x3E, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFF, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0111010  
   /* tdi_value     7:*/ 0x2E, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7D, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0111011  
   /* tdi_value     7:*/ 0x6E, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFF, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0111001  
   /* tdi_value     7:*/ 0x4E, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFF, 0x6F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0111000  
   /* tdi_value     7:*/ 0x0E, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0xFD, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0101000  
   /* tdi_value     7:*/ 0x0A, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0101001  
   /* tdi_value     7:*/ 0x4A, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0x7D, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF, 0xEF, 0xBF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0101011  
   /* tdi_value     7:*/ 0x6A, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0101010  
   /* tdi_value     7:*/ 0x2A, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0101110  
   /* tdi_value     7:*/ 0x3A, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0101111  
   /* tdi_value     7:*/ 0x7A, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0101101  
   /* tdi_value     7:*/ 0x5A, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xDF, 0x7D, 0xFF, 0xDF, 0x7F, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0x78, 0x7F, 0xFB, 0xEF, 0xBF, 0xFB, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0101100  
   /* tdi_value     7:*/ 0x1A, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0100100  
   /* tdi_value     7:*/ 0x12, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xF7, 0xDF, 0x7F, 0xFF, 
   /* tdo_value   216:*/ 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFE, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0100101  
   /* tdi_value     7:*/ 0x52, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0100111  
   /* tdi_value     7:*/ 0x72, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0100110  
   /* tdi_value     7:*/ 0x32, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0100010  
   /* tdi_value     7:*/ 0x22, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0100011  
   /* tdi_value     7:*/ 0x62, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0100001  
   /* tdi_value     7:*/ 0x42, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 0100000  
   /* tdi_value     7:*/ 0x02, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1100000  
   /* tdi_value     7:*/ 0x03, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1100001  
   /* tdi_value     7:*/ 0x43, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1100011  
   /* tdi_value     7:*/ 0x63, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1100010  
   /* tdi_value     7:*/ 0x23, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1100110  
   /* tdi_value     7:*/ 0x33, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1100111  
   /* tdi_value     7:*/ 0x73, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1100101  
   /* tdi_value     7:*/ 0x53, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1100100  
   /* tdi_value     7:*/ 0x13, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1101100  
   /* tdi_value     7:*/ 0x1B, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1101101  
   /* tdi_value     7:*/ 0x5B, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x07, 0x80, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1101111  
   /* tdi_value     7:*/ 0x7B, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1101110  
   /* tdi_value     7:*/ 0x3B, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1101010  
   /* tdi_value     7:*/ 0x2B, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1101011  
   /* tdi_value     7:*/ 0x6B, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1101001  
   /* tdi_value     7:*/ 0x4B, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1101000  
   /* tdi_value     7:*/ 0x0B, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1111000  
   /* tdi_value     7:*/ 0x0F, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1111001  
   /* tdi_value     7:*/ 0x4F, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1111011  
   /* tdi_value     7:*/ 0x6F, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1111010  
   /* tdi_value     7:*/ 0x2F, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1111110  
   /* tdi_value     7:*/ 0x3F, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1111111  
   /* tdi_value     7:*/ 0x7F, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1111101  
   /* tdi_value     7:*/ 0x5F, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1111100  
   /* tdi_value     7:*/ 0x1F, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1110100  
   /* tdi_value     7:*/ 0x17, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1110101  
   /* tdi_value     7:*/ 0x57, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1110111  
   /* tdi_value     7:*/ 0x77, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x4F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1110110  
   /* tdi_value     7:*/ 0x37, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1110010  
   /* tdi_value     7:*/ 0x27, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x02, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x81, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1110011  
   /* tdi_value     7:*/ 0x67, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xC1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x0F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1110001  
   /* tdi_value     7:*/ 0x47, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x03, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7F, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1110000  
   /* tdi_value     7:*/ 0x07, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask    152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_mask     24:*/ 0xFF, 0xFF, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value    24:*/ 0xFF, 0xFE, 0x7C, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1010000  
   /* tdi_value     7:*/ 0x05, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask    216:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask     88:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask     24:*/ 0x00, 0x00, 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   216:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   152:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    88:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    24:*/ 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XENDDR, Ex_DR_Pause,
   /* Idle            */ XSDRSIZE, BYTES32(7),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      7:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(7)-DR_Exit1-DR_Pause
   // tdi_value     0: 1010001  
   /* tdi_value     7:*/ 0x45, 
   /* tdo_value     7:*/ 0x00, 
   /* DR_Pause        */ XWAIT, DR_Pause, DR_Pause, BYTES32(20), // -Wait(20)
   /* DR_Pause        */ XENDDR, Ex_Idle,
   /* DR_Pause        */ XWAIT, Idle, Idle, BYTES32(100), // -DR_Exit2-DR_Update-Idle-Wait(100)
   /* Idle            */ XSDRSIZE, BYTES32(274),
   /* Idle            */ XTDOMASK,
   /* tdo_mask    274:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask    216:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask    152:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask     88:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask     24:*/ 0x00, 0x00, 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(274)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 11111111 11  
   /* tdi_value   274:*/ 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   216:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   152:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    88:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    24:*/ 0xFF, 0xFF, 0xFF, 
   /* tdo_value   274:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   216:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   152:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    88:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    24:*/ 0x00, 0x00, 0x00, 
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* Idle            */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(20), // -Wait(20)
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* IR_Pause        */ XSTATE, IR_Exit2,
   /* IR_Exit2        */ XSTATE, IR_Update,
   /* IR_Update       */ XSTATE, DR_Select,
   /* DR_Select       */ XSTATE, DR_Capture,
   /* DR_Capture      */ XSTATE, DR_Exit1,
   /* DR_Exit1        */ XSTATE, DR_Update,
   /* DR_Update       */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(800), // -Wait(800)
   /* Idle            */ XENDIR, Ex_Idle,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ CONLD_COMMAND, // 0xC0
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ ENABLE_COMMAND, // 0xE8
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ PROGRAM_COMMAND, // 0xEA
   /* IR_Pause        */ XSDRSIZE, BYTES32(281),
   /* IR_Pause        */ XTDOMASK,
   /* tdo_mask    281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask    224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask    160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask     96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_mask     32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* IR_Pause        */ XSDRTDO, // -IR_Exit2-IR_Update-DR_Select-DR_Capture-DR_Shift-Shift(281)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value    64: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   128: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   192: 11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 
   // tdi_value   256: 11111111 10111111 11101000 0  
   /* tdi_value   281:*/ 0x00, 0x17, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   224:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value   160:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    96:*/ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdi_value    32:*/ 0xFF, 0xFF, 0xFF, 0xFF, 
   /* tdo_value   281:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   224:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value   160:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    96:*/ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* Idle            */ XENDIR, Ex_Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(10000), // -Wait(10000)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* Idle            */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(20), // -Wait(20)
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Pause
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* IR_Pause        */ XSTATE, IR_Exit2,
   /* IR_Exit2        */ XSTATE, IR_Update,
   /* IR_Update       */ XSTATE, DR_Select,
   /* DR_Select       */ XSTATE, DR_Capture,
   /* DR_Capture      */ XSTATE, DR_Exit1,
   /* DR_Exit1        */ XSTATE, DR_Update,
   /* DR_Update       */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(800), // -Wait(800)
   /* Idle            */ XENDIR, Ex_Idle,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ CONLD_COMMAND, // 0xC0
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ IDCODE_COMMAND, // 0x01
   /* Idle            */ XSDRSIZE, BYTES32(32),
   /* Idle            */ XTDOMASK,
   /* tdo_mask     32:*/ 0x0F, 0xFF, 0x8F, 0xFF, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(32)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 00000000 00000000 00000000 00000000  
   /* tdi_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0xF6, 0xE5, 0xF0, 0x93, 
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XREPEAT, 0,
   /* Idle            */ XREPEAT, 32,
   /* Idle            */ XSTATE, Reset, // *** Reset ***
   /* Reset           */ XSTATE, Idle,
   /* Idle            */ XRUNTEST, BYTES32(0), // cycle/ms
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-DR_Exit1-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSDRSIZE, BYTES32(1),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      1:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(1)-DR_Exit1-DR_Update-Idle
   // tdi_value     0: 0  
   /* tdi_value     1:*/ 0x00, 
   /* tdo_value     1:*/ 0x00, 
   /* Idle            */ XCOMPLETE,
// Processed 22928 bytes
};