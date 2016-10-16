/*
 * uart.h
 *
 *  Created on: Oct 8, 2016
 *      Author: Satyanarayana
 */


#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

void UART0_init();
void UART0_IRQHandler();
void send_string(char s[]);
void send_char(char _value);
void put_data_with_Interrupt(uint8_t *c);

#ifndef FRDM
#define _FRDM 1

#else

#define _BBB 1
#endif

#endif /* SOURCES_UART_H_ */

