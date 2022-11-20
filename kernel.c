/*#include "kernel.h"
#include "keyboard.h"
#include "utils.h"
#include "char.h"*/
#include "terminal/commands.h"
#include "terminal/std-io.h"




void kernel_entry()
{
  char arr[500];
  init_vga(WHITE, GREEN);
  printstr("yaOS booted.", 1);
  //Puts the system into an endless loop.
  while(strcmp(arr, "CLOSE") == 0){
    printstr("yaOS> ", 0);
    input(arr);
    print_newline();
    printstr(arr, 1);
  }
}