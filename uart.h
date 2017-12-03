/* 
 * File:   uart.h
 * Author: MPLAB
 *
 * Created on August 8, 2016, 5:07 PM
 */

#ifndef UART_H
#define	UART_H

const char uartTxBuffLen=100;
char uartTxBuff[uartTxBuffLen];
char uartTxBuffC=0;
char uartTxBuffR=0;
char uartTxBuffSize=0; //Current buffer size. The size can be calculated, but the use of this is faster. Implemented to support buffer size interrogation inside interrupt routine.
char uartTxBuffMax=0; //The maximum buffer size reached within this session. Used to monitor if the buffer size is enough. 

const char uartRxBuffLen=100;
char uartRxBuff[uartRxBuffLen];
char uartRxBuffC=0;
char uartRxBuffR=0;
char uartRxBuffSize=0; //Current buffer size. The size can be calculated, but the use of this is faster. Implemented to support buffer size interrogation inside interrupt routine.
char uartRxBuffMax=0; //The maximum buffer size reached within this session. Used to monitor if the buffer size is enough. 

void uartSendTxData();
void uartTxString(const char* s);
void uartTxBuffAdd(char c);

char uartRxBuffGetLen();
char uartRxBuffGet();
void uartRxString(const char* s);

void uart_interrupt();


#endif	/* UART_H */

