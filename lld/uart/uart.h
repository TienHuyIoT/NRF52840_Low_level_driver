/**
  ******************************************************************************
  * @file    uart.h
  * @author  HuyHT1-VF Team
  * @version V1.1.0
  * @date    23-May-2019
  * @brief   This file contains the common defines and functions prototypes for
  *          the uart.c driver.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/**
  * @brief  UART status structure definition
  */

typedef enum {
	UART_OK = 0,
	UART_ERROR
} UART_Status_t;

/** @defgroup UART_Exported_Macro UART Exported Macro
  * @{
  */
                                        
#define USART0_PRINTF(f_, ...)          fprintf(stdout, (f_), ##__VA_ARGS__);
                                        
#define USART1_PRINTF(f_, ...)          fprintf(&USART1_Stream, (f_), ##__VA_ARGS__);                                                          

#define DEBUG_PRINTF                    USART0_PRINTF
                                                  
#define SCU_NEO_LOG(Tag, f_, ...)       printf("\r\n" Tag " " f_, ##__VA_ARGS__);

/** @defgroup _UART_Exported_Functions UART Exported Functions
  * @{
  */
UART_Status_t LLD_UART0_Init(uint32_t Baud);
UART_Status_t LLD_UART0_DeInit(void);
UART_Status_t LLD_UART1_Init(uint32_t Baud);
UART_Status_t LLD_UART1_DeInit(void);

UART_Status_t putchar_usart0(char c);
UART_Status_t putchar_usart1(char c);

uint32_t Usart0Tx_can_send(void);
uint32_t Usart1Tx_can_send(void);

void puts_usart0(char *s);
void puts_usart1(char *s);

uint32_t write_usart0(uint8_t *s, uint32_t len);
uint32_t write_usart1(uint8_t *s, uint32_t len);

UART_Status_t getchar_usart0(char *c);
UART_Status_t getchar_usart1(char *c);

uint32_t Usart0Rx_is_available(void);
uint32_t Usart1Rx_is_available(void);

void Usart0Rx_flush(void);
void Usart1Rx_flush(void);

extern FILE USART1_Stream;

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __UART_H */
