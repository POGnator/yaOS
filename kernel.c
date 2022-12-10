#include "terminal/std-io.h"

void kernel_entry()
{
  //max size of input capped to 100
  char arr[100];
  init_vga(WHITE, GREEN);
  printstr("yaOS booted.", 1);
  //Puts the system into an endless loop.
  while(strcmp(arr, "CLOSE") == 0){
    printstr("yaOS> ", 0);
    input(arr);
    print_newline();
    //First try of a command handler, subject to change.
    if(strcmp(arr, "PROGRAM")==1){
      printstr("Will print ToDo list once finished.",1);
    }
    printstr(arr,1);
    print_int(vga_index,0);
    if(vga_index>=1920){
      init_vga(WHITE,GREEN);
    }
  }
}