#ifndef IO_H
#define IO_H


#include "../kernel.h"
#include "keyboard.h"
#include "utils.h"
#include "char.h"
#include "commands.h"

//index for video buffer array
uint32 vga_index;
//counter to store new lines
static uint32 next_line_index = 1;
//fore & back color values
uint8 g_fore_color = WHITE, g_back_color = BLUE;
//digit ascii code for printing integers
int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
uint32 lastLineLength = 0;
char textLog[80][23];
int isScrolling = 0;
int line = 0;

/*
16 bit video buffer elements(register ax)
8 bits(ah) higher : 
  lower 4 bits - forec olor
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

//clear video buffer array
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for(i = 0; i < BUFSIZE; i++){
    //vga_buffer gets 0 at place i
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
  next_line_index = 0;
  vga_index = 0;
}

//initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS;  //point vga_buffer pointer to VGA_ADDRESS 
  clear_vga_buffer(&vga_buffer, fore_color, back_color);  //clear buffer
  g_fore_color = fore_color;
  g_back_color = back_color;
  lastLineLength = 0;
}

uint32 strlen(const char* str){
  uint32 length = 0;
  while(str[length])
    length++;
  return length;
}

void print_newline(){
  /*if(next_line_index >= 55){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;*/
  vga_index += 80-lastLineLength;
  next_line_index++;
  lastLineLength = 0;
}

void print_char(char ch){
  if(ch != '\n'){
    vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
    vga_index++;
    lastLineLength++;
  }else{
    print_newline();
  }
  if(isScrolling == 0/* && vga_index > 80*/){
    line++;
    textLog[lastLineLength][next_line_index] = ch;
  }
}

uint32 digit_count(int num){
  uint32 count = 0;
  if (num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

uint32 printstr(char *str/*, uint32 newline*/){
  uint32 index = 0;
  while(str[index]){
    print_char(str[index]);
    index++;
  }
  //if (newline == 1){
  //  print_newline();
  //}
  return index;
}
uint8 inb(uint16 port)
{
  uint8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}

/*
keep the cpu busy for doing nothing(nop)
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void wait_for_io(uint32 timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void sleep(uint32 timer_count)
{
  wait_for_io(timer_count);
}

uint32 input(char *buf)
{
  /*
  to return the actual input.
  As of right now, this returns the input + extra spaces, so it's kinda working but actually not.
  */
  uint32 j = 0;
  for(j=0;j<strlen(buf);j++){
    buf[j] = ' ';
  }

  char ch = 0;
  char keycode = 0;
  uint32 i = 0;
  //fill array with input chars
  do{
    vga_buffer[vga_index] = vga_entry(0, g_back_color, g_fore_color);
    keycode = get_input_keycode();
    ch = get_ascii_char(keycode);
    print_char(ch);
    buf[i] = ch;
    i++;
    sleep(0x05FFFFFF);
  }while(ch > 0 && keycode != KEY_ENTER);
  return i;
}
//Returns 0 if not same, return 1 if same
uint32 strcmp(char* str1, char* str2){
  uint32 i = 0;
  if(strlen(str1) != strlen(str2)){
    //printstr("bruh",1);
    return 0;
  }
  for(i = 0; i < strlen(str1); i++){
    if(str1[i] == str2[i]){
    }
    else{
      return 0;
    }
  }
  return 1;
}
void print_int(uint32 num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  printstr(str_num);
}

#endif