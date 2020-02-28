#ifndef MINI_UART_H
#define MINI_UART_H

#include "peripherals.h"

#define AUX_ENABLES ( PBASE + 0x215004 )
#define AUX_MU_IO_REG ( PBASE + 0x215040 )
#define AUX_MU_IER_REG ( PBASE + 0x215044 )
#define AUX_MU_IIR_REG ( PBASE + 0x215048 )
#define AUX_MU_LCR_REG ( PBASE + 0x21504c )
#define AUX_MU_MCR_REG ( PBASE + 0x215050 )
#define AUX_MU_LSR_REG ( PBASE + 0x215054 )
#define AUX_MU_MSR_REG ( PBASE + 0x215058 )
#define AUX_MU_SCRATCH ( PBASE + 0x21505c )
#define AUX_MU_CNTL_REG ( PBASE + 0x215060 )
#define AUX_MU_STAT_REG ( PBASE + 0x215064 )
#define AUX_MU_BAUD_REG ( PBASE + 0x215068 )

void uart_init();
char uart_getc();
void uart_putc( char c );
void uart_send_string( char *c );

#endif

