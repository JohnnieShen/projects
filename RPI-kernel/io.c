#include "io.h"
#include <stddef.h>
#include <stdint.h>
void mmio_write(long reg, unsigned int val) { *(volatile unsigned int *)reg = val; }
unsigned int mmio_read(long reg) { return *(volatile unsigned int *)reg; }
static void wait(unsigned int cycle){
  while(cycle--!=0){}
}
void uart_init() {
  mmio_write(UART0_CR, 0);
  mmio_write(GPPUD,0);
  wait(150);
  mmio_write(GPPUDCLK0,(1<<14)|(1<<15));
  wait(150);
  mmio_write(GPPUDCLK0,0);
  mmio_write(UART0_ICR, 0x7FF);
  
  mmio_write(UART0_IBRD, 1);
  mmio_write(UART0_FBRD, 41);
  mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
  mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	     (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
  mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
  
}

void uart_sendc(unsigned char c)
{
  while ( mmio_read(UART0_FR) & (1<<5) ) { }
  mmio_write(UART0_DR, c);
}

unsigned char uart_recvc()
{
  while ( mmio_read(UART0_FR) & (1<<4) ) { }
  return mmio_read(UART0_DR);
}

void uart_sends(const char* str)
{
  for (long i = 0; str[i] != '\0'; i ++)
    uart_sendc((unsigned char)str[i]);
}
