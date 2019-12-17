//============================================================================
// Name        : Convert_XSVF_C.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>

int main(int argc, const char *args[]) {

//   printf("Argc = %d\n", argc);
//   printf("Args[0] = %s\n", args[0]);

   const char *filename = "CPLD_Tester.xsvf";
   if (argc>1) {
      filename = args[1];
   }

   FILE *fp = fopen(filename, "rb");

   fseek(fp, 0L, SEEK_END);
   unsigned long size = ftell(fp);
   printf(
      "/* \n"
      " * XSVF_Data.cpp \n"
      " *\n"
      " * Derived from %s\n"
      " */ \n"
      "#include \"XSVF_Data.h\" \n"
      " \n"
      "const uint8_t xsvf_data[%lu] = {", filename, size);

   rewind(fp);
   unsigned index = 0;
   do {
      int data = fgetc(fp);
      if (data == EOF) {
         break;
      }
      if ((index++%16) == 0) {
         printf("\n   /* 0x%04X */ ", index-1);
      }
      printf("0x%02X, ", data);
   } while (true);
   printf("\n};");
	return 0;
}
