#include "uart.h"

#include "gpio.h"
#include "util.h"

void uart_init() {
    unsigned int selector;

    selector = get32( GPFSEL1 );
    selector &= ~( 7 << 12 );
    selector |= ( 4 << 12 );
    selector &= ~( 7 << 15 );
    selector |= ( 4 << 15 );
    put32( GPFSEL1, selector );

    put32( GPPUD, 0 );
    delay( 150 );
    put32( GPPUDCLK0, ( 1 << 14 ) | ( 1 << 15 ) );
    delay( 150 );
    put32( GPPUDCLK0, 0 );

    put32( UART_CR, 0 );
    put32( UART_IBRD, 26 );
    put32( UART_FBRD, 3 );
    put32( UART_LCRH, 7 << 4 );
    put32( UART_IMSC, 0 );
    put32( UART_CR, 1 | ( 3 << 8 ) );
}

char uart_getc() {
    while ( get32( UART_FR ) & ( 1 << 4 ) ) {
    }
    return get32( UART_DR ) & 0xff;
}

void uart_putc( char c ) {
    while ( get32( UART_FR ) & ( 1 << 5 ) ) {
    }
    put32( UART_DR, c );
}

void uart_send_string( char *c ) {
    while ( *c ) uart_putc( *c++ );
}

