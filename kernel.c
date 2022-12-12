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
    print_char('\n');
    //First try of a command handler, subject to change.
    if(strcmp(arr, "PROGRAM")==1){
      printstr("Will print ToDo list once finished.\n");
    }
    printstr(arr);
    print_newline();
    print_int(vga_index);
    print_char('\n');
    if(vga_index>=1820){
      uint16 iterator = 0;
      for(iterator = 0; iterator < strlen(textLog-80); iterator++){
        //vga_buffer[iterator] = vga_entry(NULL, WHITE, GREEN);
        init_vga(WHITE, GREEN);
        print_char(textLog[iterator+80]);
      }
    }
  }
}
//log every character into a string and remove first 80 when too big