#include "terminal/std-io.h"

// Defining kernel_entry as a function of C so that the linker won't fuck with us
extern "C"{
    void kernel_entry();
}

void kernel_entry(){
    init_vga(WHITE, BLACK);
    printstr((char*)"yaOS C++ fork booted\n");
    while(1){
        char arr[100];
        printstr((char*)"yaOS> ");
        input(arr);
        print_char('\n');
        printstr(arr);
        print_char('\n');
        print_int(strlen(arr));
        print_char('\n');
        if (next_line_index < 12){
            for(int i = 0; i<80; i++){
                for(int j = 0; j<26; j++){
                    print_char(textLog[i][j]);
                }
            }
        }
    }
}