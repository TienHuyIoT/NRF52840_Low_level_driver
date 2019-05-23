#include "app_uart.h"
#include "app_error.h"
#include "scu_neo_board.h"
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif
#include "uart.h"

#define UART_INSTANCE_STD       0
#define UART1_INSTANCE          1

#define UART0_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART0_RX_BUF_SIZE 256                         /**< UART RX buffer size. */

#define UART1_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART1_RX_BUF_SIZE 256                         /**< UART RX buffer size. */

nrf_uarte_baudrate_t uart_baud_select(uint32_t baud)
{
#if defined (UARTE_PRESENT)  
  switch(baud)
  {    
  case 9600:
    return NRF_UARTE_BAUDRATE_9600;
    case 19200:
    return NRF_UARTE_BAUDRATE_19200;
    case 38400:
    return NRF_UARTE_BAUDRATE_38400;
    case 57600:
    return NRF_UARTE_BAUDRATE_57600;
    case 115200:
    return NRF_UARTE_BAUDRATE_115200;
  }
  return NRF_UARTE_BAUDRATE_115200;
#else
  switch(baud)
  {    
  case 9600:
    return NRF_UART_BAUDRATE_9600;
    case 19200:
    return NRF_UART_BAUDRATE_19200;
    case 38400:
    return NRF_UART_BAUDRATE_38400;
    case 57600:
    return NRF_UART_BAUDRATE_57600;
    case 115200:
    return NRF_UART_BAUDRATE_115200;
  }
  return NRF_UART_BAUDRATE_115200;
#endif  
}

void uart_error_handle(app_uart_evt_t * p_event, void* p_context)
{
  UNUSED_PARAMETER(p_context);  
  //uint32_t inst_idx = (uint32_t)p_context;
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

/* When UART is used for communication with the host do not use flow control.*/
#define UART_HWFC APP_UART_FLOW_CONTROL_DISABLED

UART_Status_t LLD_UART0_Init(uint32_t Baud)
{
    uint32_t err_code;
/* UART0 INIT */
    app_uart_comm_params_t comm_params =
      {
          RX_PIN_NUMBER,
          TX_PIN_NUMBER,
          RTS_PIN_NUMBER,
          CTS_PIN_NUMBER,
          UART_HWFC,
          false
      };
    comm_params.baud_rate = uart_baud_select(Baud);

    APP_UART_FIFO_INIT(UART_INSTANCE_STD,
                       &comm_params,
                         UART0_RX_BUF_SIZE,
                         UART0_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

    APP_ERROR_CHECK(err_code);
    return UART_OK;
}

UART_Status_t LLD_UART0_DeInit(void)
{
  return (app_uart_close(UART_INSTANCE_STD) == NRF_SUCCESS) ? UART_OK : UART_ERROR;
}

UART_Status_t LLD_UART1_Init(uint32_t Baud)
{
  uint32_t err_code;
  /* UART1 INIT */
    app_uart_comm_params_t comm_params =
      {
          RX1_PIN_NUMBER,
          TX1_PIN_NUMBER,
          RTS1_PIN_NUMBER,
          CTS1_PIN_NUMBER,
          UART_HWFC,
          false
      };
    comm_params.baud_rate = uart_baud_select(Baud);
    
    APP_UART_FIFO_INIT(UART1_INSTANCE,
                       &comm_params,
                         UART1_RX_BUF_SIZE,
                         UART1_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

    APP_ERROR_CHECK(err_code);
    return UART_OK;
}

UART_Status_t LLD_UART1_DeInit(void)
{
  return (app_uart_close(UART1_INSTANCE) == NRF_SUCCESS) ? UART_OK : UART_ERROR;
}

UART_Status_t putchar_usart0(char c)
{
  return (app_uart_put(UART_INSTANCE_STD, (uint8_t)c) == NRFX_SUCCESS) ? UART_OK : UART_ERROR;
}

UART_Status_t putchar_usart1(char c)
{
  return (app_uart_put(UART1_INSTANCE, (uint8_t)c) == NRFX_SUCCESS) ? UART_OK : UART_ERROR;
}

void puts_usart0(char *s)
{
  while(*s)
  {
    app_uart_put(UART_INSTANCE_STD, (uint8_t)*s++);
  }
}

void puts_usart1(char *s)
{
  while(*s)
  {
    app_uart_put(UART1_INSTANCE, (uint8_t)(*s));
    s++;
  }
}

uint32_t write_usart0(uint8_t *s, uint32_t len)
{
  uint32_t i;  
  for(i = 0; i < len; i++)
  {
    if(app_uart_put(UART_INSTANCE_STD, (uint8_t)(*s)) != NRFX_SUCCESS)
    {
      break;
    }
    s++;
  }
  return i;
}

uint32_t write_usart1(uint8_t *s, uint32_t len)
{
  uint32_t i;  
  for(i = 0; i < len; i++)
  {
    if(app_uart_put(UART1_INSTANCE, (uint8_t)(*s)) != NRFX_SUCCESS)
    {
      break;
    }
    s++;
  }
  return i;
}

/**
  * @brief get one character from Rx buff usart0
  * @param  none
  * @retval character
  */
UART_Status_t getchar_usart0(char *c)
{     
    return (app_uart_get(UART_INSTANCE_STD, (uint8_t *)c) == NRF_SUCCESS)? UART_OK : UART_ERROR;
}

UART_Status_t getchar_usart1(char *c)
{     
    return (app_uart_get(UART1_INSTANCE, (uint8_t *)c) == NRF_SUCCESS)? UART_OK : UART_ERROR;
}

/**
  * @brief check rx buff usart0
  * @param  none
  * @retval size real buff available
  */
uint32_t Usart0Rx_is_available(void){
  return app_uartRx_is_available(UART_INSTANCE_STD);
}

uint32_t Usart1Rx_is_available(void){
  return app_uartRx_is_available(UART1_INSTANCE);
}

uint32_t Usart0Tx_can_send(void)
{
  return app_uartTx_can_send(UART_INSTANCE_STD);
}

uint32_t Usart1Tx_can_send(void)
{
  return app_uartTx_can_send(UART1_INSTANCE);
}

void Usart0Rx_flush(void)
{
  app_uart_flush(UART_INSTANCE_STD);
}

void Usart1Rx_flush(void)
{
  app_uart_flush(UART1_INSTANCE);
}

/** @file
 *
 * @defgroup retarget Retarget layer for stdio functions
 * @{
 * @ingroup app_common
 * @} */

#include "sdk_common.h"

#if NRF_MODULE_ENABLED(RETARGET)
#if !defined(NRF_LOG_USES_RTT) || NRF_LOG_USES_RTT != 1
#if !defined(HAS_SIMPLE_UART_RETARGET)

#include <stdio.h>
#include <stdint.h>
#include "app_uart.h"
#include "nrf_error.h"
#include "tm_stdio.h"
   
#define STREAM_STD       UART_INSTANCE_STD  
   
/* Output stream for USART1 function references */
static int USART1_Stream_OutputFunction(int ch, FILE* f);   
/* Input stream for USART1 function references */
static int USART1_Stream_InputFunction(FILE* f);

FILE USART1_Stream = {&USART1_Stream_OutputFunction, &USART1_Stream_InputFunction};

/* Handle stdout actions */
int TM_STDIO_StdoutHandler(int ch, FILE* f) 
{
  UNUSED_PARAMETER(f);
  /* Send data to USART1 */
  UNUSED_VARIABLE(app_uart_put(STREAM_STD, (uint8_t)ch));
  
  /* Return ch, it means OK */
  return ch;
  /* If you want to return error, then you have to send EOF (-1) */
  //return -1;
}

/* Handle stdin actions */
int TM_STDIO_StdinHandler(FILE* f) 
{
  UNUSED_PARAMETER(f);
  uint8_t input;
  /* If any data at USART, return them */
  while (app_uart_get(STREAM_STD, &input) == NRF_ERROR_NOT_FOUND)
  {
      // No implementation needed.
  }
  return input;

  /* End of data, string is valid */
  /* You have to send -1 at the end of string */
  //return -1;
}

/* USART1_Stream function that will send char by char to stream */
static int USART1_Stream_OutputFunction(int ch, FILE* f) {
  UNUSED_PARAMETER(f);
  /* Send data to USART1 */
  UNUSED_VARIABLE(app_uart_put(UART1_INSTANCE, (uint8_t)ch));
  
  /* Return ch, it means OK */
  return ch;
  /* If you want to return error, then you have to send EOF (-1) */
  //return -1;
}

/* Handle USART1 stream input = custom function name, linked with USART1 stream in the beginning of main() function */
static int USART1_Stream_InputFunction(FILE* f)
{
  UNUSED_PARAMETER(f);
  uint8_t input;
  /* If any data at USART, return them */
  while (app_uart_get(UART1_INSTANCE, &input) == NRF_ERROR_NOT_FOUND)
  {
      // No implementation needed.
  }
  return input;

  /* End of data, string is valid */
  /* You have to send -1 at the end of string */
  //return -1;
}

#endif // !defined(HAS_SIMPLE_UART_RETARGET)
#endif // NRF_LOG_USES_RTT != 1
#endif //NRF_MODULE_ENABLED(RETARGET)
