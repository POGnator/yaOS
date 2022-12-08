/*#include "kernel.h"
#include "keyboard.h"
#include "utils.h"
#include "char.h"*/
//#include "terminal/commands.h"
#include "terminal/std-io.h"
//#include "programs/election.h"

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
    if(strcmp(arr, "PROGRAM")==1){
      //cool_program();
    }
    print_newline();
    printstr(arr,1);
    print_int(vga_index,0);
    if(vga_index>=1920){
      init_vga(WHITE,GREEN);
    }
  }
}