//============================================================================
// Name        : Convert_XSVF_C.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>

static constexpr char STX = 0x02;
static constexpr char ETX = 0x03;

enum State {
   S_HEADER,
   S_COMMENT,
   S_COMMENT_device,
   S_COMMAND,
   S_QCOMMAND,
   S_QF,
   S_QP,
   S_QV,
   S_FUSEDEFAULT,
   S_X,
   S_J_arch,
   S_J_pin,
   S_L_num,
   S_L_value,
   S_ABORT,
};

struct FuseInformation {
   char       device_name[100];
   unsigned   fuse_limit;
   unsigned   number_of_pins;
   unsigned   vector_limit;
   bool       default_state;
   bool       default_test;
   unsigned   device_code_arch;
   unsigned   device_code_pin;
   bool       *fuseData;
};

bool loadFuseData(FILE *fp, FuseInformation &fuseInformation) {

   char     comment[200];
   char     *comment_ptr;
   unsigned fuse_number       = 0;

   State state       = S_HEADER;
   bool stripSpace   = true;

   do {
      int ch = fgetc(fp);
      if ((ch == ETX) || (ch == -1)) {
         break;
      }
      if ((ch =='\r') || (ch == '\n')) {
         continue;
      }
      switch (state) {
         case S_HEADER:
            if (ch == STX) {
               state = S_COMMAND;
            }
            continue;
            break;
         case S_COMMAND:
         {
            switch(ch) {
               case 'N':
                  state = S_COMMENT;
                  comment_ptr = comment;
                  stripSpace  = true;
                  break;
               case 'Q':   state = S_QCOMMAND;      break;
               case 'F':   state = S_FUSEDEFAULT;   break;
               case 'X':   state = S_X;             break;
               case 'J':   state = S_J_arch;        break;
               case 'L':   state = S_L_num;
                  fuse_number = 0;
                  break;
               default:    state = S_ABORT;         break;
            }
            continue;
         }
         case S_COMMENT:
            if (ch == '*') {
               state = S_COMMAND;
               *comment_ptr++ = '\0';
//               printf("Note: \'%s\'\n", comment);
               continue;
            }
            if (isspace(ch) && stripSpace) {
               continue;
            }
            stripSpace = false;
            *comment_ptr++ = ch;
            if (strncmp(comment,"ote",3) == 0) {
               comment_ptr = comment;
               stripSpace  = true;
            }
            if (strncmp(comment,"DEVICE",6) == 0) {
               comment_ptr = comment;
               stripSpace  = true;
               state = S_COMMENT_device;
            }
            continue;
         case S_COMMENT_device:
            if (ch == '*') {
               state = S_COMMAND;
               *comment_ptr++ = '\0';
               strncpy(fuseInformation.device_name, comment, sizeof(fuseInformation.device_name));
//               printf("Device: \'%s\'\n", comment);
               continue;
            }
            if (isspace(ch) && stripSpace) {
               continue;
            }
            stripSpace = false;
            *comment_ptr++ = ch;
            continue;
         case S_QCOMMAND:
         {
            switch(ch) {
               case 'F': state = S_QF;    break;
               case 'P': state = S_QP;    break;
               case 'V': state = S_QV;    break;
               default:  state = S_ABORT; break;
            }
            continue;
         }
         break;
         case S_QF:
            if (ch == '*') {
               fuseInformation.fuseData = (bool *)malloc(fuseInformation.fuse_limit);
               memset(fuseInformation.fuseData, 0, fuseInformation.fuse_limit);
//               printf("fuse_limit = %d\n", fuseInformation.fuse_limit);
               state = S_COMMAND;
               continue;
            }
            fuseInformation.fuse_limit = 10*fuseInformation.fuse_limit+(ch-'0');
            continue;
         case S_QP:
            if (ch == '*') {
               state = S_COMMAND;
//               printf("number_of_pins = %d\n", fuseInformation.number_of_pins);
               continue;
            }
            fuseInformation.number_of_pins = 10*fuseInformation.number_of_pins+(ch-'0');
            continue;
         case S_QV:
            if (ch == '*') {
               state = S_COMMAND;
//               printf("vector_limit = %d\n", fuseInformation.vector_limit);
               continue;
            }
            fuseInformation.vector_limit = 10*fuseInformation.vector_limit+(ch-'0');
            continue;
         case S_X:
            if (ch == '*') {
               state = S_COMMAND;
//               printf("default_test = %d\n", fuseInformation.default_test);
               continue;
            }
            fuseInformation.default_test = (ch - '0');
            continue;
         case S_J_arch:
            if (ch == ' ') {
               state = S_J_pin;
               continue;
            }
            fuseInformation.device_code_arch = 10*fuseInformation.device_code_arch + (ch-'0');
            continue;
         case S_J_pin:
            if (ch == '*') {
               state = S_COMMAND;
//               printf("device_identification = %d.%d\n", fuseInformation.device_code_arch, fuseInformation.device_code_pin);
               continue;
            }
            fuseInformation.device_code_pin = 10*fuseInformation.device_code_pin + (ch-'0');
            continue;
         case S_L_num:
            if (isspace(ch)) {
               state = S_L_value;
//               printf("fuse_number = %d\n", fuse_number);
               continue;
            }
            fuse_number = 10*fuse_number + (ch-'0');
            continue;
         case S_L_value:
            if (ch == '*') {
               state = S_COMMAND;
               continue;
            }
            if (isspace(ch)) {
               continue;
            }
            if (fuse_number>(fuseInformation.fuse_limit)) {
               return false;
            }
            fuseInformation.fuseData[fuse_number++] = (ch - '0');
            continue;
         case S_ABORT:
            if (ch == '*') {
               state = S_COMMAND;
            }
            continue;
            break;
         case S_FUSEDEFAULT:
            if (ch == '*') {
               state = S_COMMAND;
               if (fuseInformation.fuseData != nullptr) {
                  memset(fuseInformation.fuseData, fuseInformation.default_state, fuseInformation.fuse_limit);
                }
//               printf("default_state = %d\n", fuseInformation.default_state);
               continue;
            }
            fuseInformation.default_state = (ch - '0');
            continue;
      }
      putchar(ch);
   } while (true);
//   printf("\nETX ================\n");

   return true;
}

void printFuses(FuseInformation &fuseInformation) {
   static constexpr unsigned WIDTH = 64;

   printf("Device = %s\n", fuseInformation.device_name);

   printf("       ");
   for (unsigned fuseNum=0; fuseNum<WIDTH; fuseNum+=10) {
      printf("%-10X", fuseNum/10);
   }
   printf("\n       ");
   for (unsigned fuseNum=0; fuseNum<WIDTH; fuseNum++) {
      printf("%1X", fuseNum%10);
   }
   printf("\n       ");
   for (unsigned fuseNum=0; fuseNum<WIDTH; fuseNum++) {
      printf("-");
   }
   printf("\n");
   bool needIntro = true;
   for (unsigned fuseNum=0; fuseNum<fuseInformation.fuse_limit; fuseNum++) {
      if(needIntro) {
         printf("%06X:", fuseNum);
      }
      printf("%1d",fuseInformation.fuseData[fuseNum]);
      needIntro = (fuseNum%WIDTH) == (WIDTH-1);
      if (needIntro) {
         printf("\n");
      }
   }
}

extern int bitmap[];

bool rearrangeFuseMap(FuseInformation &fuseInformationIn,  FuseInformation &fuseInformationOut) {

   fuseInformationOut = fuseInformationIn;
   fuseInformationOut.fuseData = (bool *)malloc(fuseInformationIn.fuse_limit);

   int fuseNumber = 0;
   do {
      int mappedFuseNumber = bitmap[fuseNumber];
      if (mappedFuseNumber < 0) {
         break;
      }
      if ((unsigned)mappedFuseNumber>fuseInformationIn.fuse_limit) {
         fprintf(stderr, "mappedFuseNumber (%d) too large", mappedFuseNumber);
         fflush(stderr);
         return 0;
      }
      fuseInformationOut.fuseData[fuseNumber] = fuseInformationIn.fuseData[mappedFuseNumber];
      fuseNumber++;
   } while(true);
   return true;
}

int main(int argc, const char *args[]) {

   FuseInformation fuseInformation = {};

   const char *jedec_filename = "CPLD_Tester.jed";
   FILE *fp = fopen(jedec_filename, "rb");
   if (fp == nullptr) {
      return 0;
   }
   loadFuseData(fp, fuseInformation);
   fclose(fp);

//   printFuses(fuseInformation);

   FuseInformation mappedFuseInformation = {};
   rearrangeFuseMap(fuseInformation, mappedFuseInformation);
   printFuses(mappedFuseInformation);

   return 0;
}
