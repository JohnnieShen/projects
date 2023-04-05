#include "io.h"
#include "fb.h"
#include "atag.h"
//static char key_buffer[256];
void kernel_main(){
  uart_init();
  fb_init();
  drawPixel(250,250,0x0e);
  while(1);
}
