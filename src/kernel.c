#include "uart.h"

void kernel_main( void ) {
    uart_init();
    uart_send_string( "Hello world from kernel!\r\n" );
    for ( ;; ) {
        uart_putc( uart_getc() + 1 );
    }
}

