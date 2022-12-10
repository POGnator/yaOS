#ifndef ELECTION_H
#define ELECTION_H
#include "../terminal/std-io.h"

int cool_program(){
    init_vga(WHITE, GREEN);
    char* name = "ab";
    printstr("Enter your name: ",0);
    input(name);
    init_vga(WHITE,GREEN);
    printstr("Hello, ",0);
    printstr(name,0);
    printstr("! ",0);
    input(name);
    init_vga(WHITE, GREEN);
    return 0;
}

#endif