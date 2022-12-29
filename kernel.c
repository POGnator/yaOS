/*
  This file is compiled but not used.
  I have the hopes that C++ will make a lot things here easier.
*/


#include "terminal/std-io.h"

void kernel_entry()
{
  //max size of input capped to 100
  char arr[100];
  init_vga(WHITE, GREEN);
  printstr((char*)"yaOS with C++ booted\n");
  //Puts the system into an endless loop.
  while(strcmp(arr, (char*)"CLOSE") == 0){
    printstr((char*)"yaOS> ");
    input(arr);
    //print_char('\n');
    //First try of a command handler, subject to change.
    if(strcmp(arr, (char*)"PROGRAM")==1){
      printstr((char*)"Will print ToDo list once finished.\n");
    }
    print_char('\n');
    print_int(vga_index);
    print_char('\n');
    if(vga_index>=1920){
      init_vga(WHITE,GREEN);
      isScrolling = 1;
      printstr(textLog);
      vga_index = 1840;
      isScrolling = 0;
    }
  }
}
//log every character into a string and remove first 80 when too big