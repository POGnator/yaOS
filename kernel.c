#include "terminal/std-io.h"

void kernel_entry()
{
  //max size of input capped to 100
  char arr[100];
  init_vga(WHITE, GREEN);
  printstr("yaOS booted\n");
  //Puts the system into an endless loop.
  while(strcmp(arr, "CLOSE") == 0){
    printstr("yaOS> ");
    input(arr);
    //print_char('\n');
    //First try of a command handler, subject to change.
    if(strcmp(arr, "PROGRAM")==1){
      printstr("Will print ToDo list once finished.\n");
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