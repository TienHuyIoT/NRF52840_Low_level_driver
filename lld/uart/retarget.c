#include "sdk_common.h"
/** @file
 *
 * @defgroup retarget Retarget layer for stdio functions
 * @{
 * @ingroup app_common
 * @} */
#if NRF_MODULE_ENABLED(RETARGET)
#if !defined(NRF_LOG_USES_RTT) || NRF_LOG_USES_RTT != 1
#if !defined(HAS_SIMPLE_UART_RETARGET)

#include <stdio.h>
#include <stdint.h>
#include "app_uart.h"
#include "nrf_error.h"
#include "tm_stdio.h"
   
#define STREAM_STD       0   
   
/* Output stream for USART1 function references */
static int USART1_Stream_OutputFunction(int ch, FILE* f);   
/* Input stream for USART1 function references */
int USART1_Stream_InputFunction(FILE* f);

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
int USART1_Stream_OutputFunction(int ch, FILE* f) {
  UNUSED_PARAMETER(f);
  /* Send data to USART1 */
  UNUSED_VARIABLE(app_uart_put(1, (uint8_t)ch));
  
  /* Return ch, it means OK */
  return ch;
  /* If you want to return error, then you have to send EOF (-1) */
  //return -1;
}

/* Handle USART1 stream input = custom function name, linked with USART1 stream in the beginning of main() function */
int USART1_Stream_InputFunction(FILE* f)
{
  UNUSED_PARAMETER(f);
  uint8_t input;
  /* If any data at USART, return them */
  while (app_uart_get(1, &input) == NRF_ERROR_NOT_FOUND)
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
