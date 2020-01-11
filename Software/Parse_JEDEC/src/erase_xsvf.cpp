// Created from : 'erase'

#include <stdint.h>
#include "erase_xsvf.h"
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

#define BYTES32(x) (0xFF&((x)>>24)),(0xFF&((x)>>16)),(0xFF&((x)>>8)),(0xFF&(x))

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

const uint8_t erase_xsvf[212] = {
   /* Reset           */ XREPEAT, 0,
   /* Reset           */ XENDIR, Ex_Idle,
   /* Reset           */ XENDDR, Ex_Idle,
   /* Reset           */ XSTATE, Reset, // *** Reset ***
   /* Reset           */ XSTATE, Idle,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Update-Idle
   /* tdi_value     8:*/ IDCODE_COMMAND, // 0x01
   /* Idle            */ XSDRSIZE, BYTES32(32),
   /* Idle            */ XTDOMASK,
   /* tdo_mask     32:*/ 0x0F, 0xFF, 0x8F, 0xFF, 
   /* Idle            */ XRUNTEST, BYTES32(0), // cycle/ms
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(32)-DR_Update-Idle
   /* tdi_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0xF6, 0xE5, 0xF0, 0x93, 
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Update-Idle
   /* tdi_value     8:*/ IDCODE_COMMAND, // 0x01
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(32)-DR_Update-Idle
   /* tdi_value    32:*/ 0x00, 0x00, 0x00, 0x00, 
   /* tdo_value    32:*/ 0xF6, 0xE5, 0xF0, 0x93, 
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Update-Idle
   /* tdi_value     8:*/ ENABLE_COMMAND, // 0xE8
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Pause
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
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Pause
   /* tdi_value     8:*/ INIT_COMMAND, // 0xF0
   /* IR_Pause        */ XSTATE, IR_Exit2,
   /* IR_Exit2        */ XSTATE, IR_Update,
   /* IR_Update       */ XSTATE, Idle,
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(20), // -Wait(20)
   /* Idle            */ XENDIR, Ex_IR_Pause,
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Pause
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
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Update-Idle
   /* tdi_value     8:*/ CONLD_COMMAND, // 0xC0
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Update-Idle
   /* tdi_value     8:*/ CONLD_COMMAND, // 0xC0
   /* Idle            */ XWAIT, Idle, Idle, BYTES32(100), // -Wait(100)
   /* Idle            */ XREPEAT, 0,
   /* Idle            */ XREPEAT, 32,
   /* Idle            */ XSTATE, Reset, // *** Reset ***
   /* Reset           */ XSTATE, Idle,
   /* Idle            */ XRUNTEST, BYTES32(0), // cycle/ms
   /* Idle            */ XSIR, 8, // -DR_Select-IR_Select-IR_Capture-IR_Shift-Shift(8)-IR_Update-Idle
   /* tdi_value     8:*/ BYPASS_COMMAND, // 0xFF
   /* Idle            */ XSDRSIZE, BYTES32(1),
   /* Idle            */ XTDOMASK,
   /* tdo_mask      1:*/ 0x00, 
   /* Idle            */ XSDRTDO, // -DR_Select-DR_Capture-DR_Shift-Shift(1)-DR_Update-Idle
   /* tdi_value     1:*/ 0x00, 
   /* tdo_value     1:*/ 0x00, 
   /* Idle            */ XCOMPLETE,
// Processed 212 bytes
};