#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "tm_stdio.h"
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif
#include "uart.h"

extern FILE USART1_Stream;

/**
 * @brief Function for main application entry.
 */
int main(void)
{
    LLD_UART0_Init(115200);
    LLD_UART1_Init(115200);
    
    USART0_PRINTF("\r\nUART example started.\r\n");
    USART1_PRINTF("\r\nUART example started.\r\n");

    while (true)
    {
        char cr;
        while (getchar_usart0(&cr) != UART_OK);
        while (putchar_usart0(cr) != UART_OK);

        if (cr == 'q' || cr == 'Q')
        {
            printf(" \r\nExit!\r\n");

            while (true)
            {
                // Do nothing.
            }
        }
    }
}

/** @} */
