#include "mini_uart.h"

#include "gpio.h"
#include "util.h"

void mini_uart_init() {
    unsigned int selector;

    selector = get32( GPFSEL1 );
    selector &= ~( 7 << 12 );
    selector |= ( 2 << 12 );
    selector &= ~( 7 << 15 );
    selector |= ( 2 << 15 );
    put32( GPFSEL1, selector );

    put32( GPPUD, 0 );
    delay( 150 );
    put32( GPPUDCLK0, ( 1 << 14 ) | ( 1 << 15 ) );
    delay( 150 );
    put32( GPPUDCLK0, 0 );

    put32( AUX_ENABLES, 1 );
    put32( AUX_MU_CNTL_REG, 0 );
    put32( AUX_MU_IER_REG, 0 );
    put32( AUX_MU_LCR_REG, 3 );
    put32( AUX_MU_MCR_REG, 0 );
    put32( AUX_MU_BAUD_REG, 270 );
    /* put32( AUX_MU_IIR_REG, 6 ); */
    put32( AUX_MU_CNTL_REG, 3 );
}

char mini_uart_getc() {
    for ( ;; ) {
        if ( get32( AUX_MU_LSR_REG ) & 0x01 ) {
            break;
        }
    }
    return get32( AUX_MU_IO_REG ) & 0xff;
}

void mini_uart_putc( char c ) {
    for ( ;; ) {
        if ( get32( AUX_MU_LSR_REG ) & 0x20 ) {
            break;
        }
    }
    put32( AUX_MU_IO_REG, c );
}

void mini_uart_send_string( char *c ) {
    while ( *c ) mini_uart_putc( *c++ );
}

