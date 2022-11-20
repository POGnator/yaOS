/*#include "kernel.h"
#include "keyboard.h"
#include "utils.h"
#include "char.h"*/
#include "terminal/commands.h"
#include "terminal/io.h"




void kernel_entry()
{
  /*
  TODO:
  - Make input system better
  - scrolling line
  x Print integer
  - equivalent of strcmp
  */
  char arr[500];
  init_vga(WHITE, GREEN);
  printstr("yaOS booted.", 1);
  //Puts the system into an endless loop.
  while(strcmp(arr, "CLOSE") == 0){
    printstr("yaOS> ", 0);
    test_input(arr);
    print_newline();
    printstr(arr, 1);
  }
}