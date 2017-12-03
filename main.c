/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on August 8, 2016, 4:49 PM
 */


#include "main.h"

void main(void) {
    config();
    uartTxString("Murzik\r\n");
    //uartRxString("ADI");
    do{
        uartSendTxData();
    }while(1);
}
