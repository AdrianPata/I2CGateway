#include "main.h"

/* TRANSMIT */
void uartTxBuffAdd(char c){
    char tc;
    tc=uartTxBuffC; //Get temporary cursor
    tc++; //Advance cursor
    if(tc==uartTxBuffLen) tc=0; //Past the end of the buffer?
    if(tc==uartTxBuffR) return; //Buffer full
    
    uartTxBuff[uartTxBuffC]=c; //Put character in buffer at cursor   
    uartTxBuffC=tc; //Advance cursor (using calculated position)
    uartTxBuffSize++; //Increase buffer size
    if(uartTxBuffSize>uartTxBuffMax) uartTxBuffMax=uartTxBuffSize; //If it is the case, modify the max value reached for the buffer.
}

char uartTxBuffGetLen(){
    return uartTxBuffSize;
    /*
    if(uartTxBuffC>=uartTxBuffR) {
        return uartTxBuffC-uartTxBuffR;
    } else {
        return uartTxBuffC+(uartTxBuffLen-uartTxBuffR);
    }
    */
}

char uartTxBuffGet(){
    char r;
    if(uartTxBuffC==uartTxBuffR) return 0; //Buffer empty
    r=uartTxBuff[uartTxBuffR];
    uartTxBuffR++;
    if(uartTxBuffR==uartTxBuffLen)uartTxBuffR=0;
    uartTxBuffSize--; //Decrease buffer size.
    return r;
}

void uartTxString(const char* s){
    for(char i=0;i<strlen(s);i++){
        uartTxBuffAdd(s[i]);
    }
}

//Transmit buffer data
void uartSendTxData(){
    if(uartTxBuffGetLen()>0 && TXIF==1){
        TXREG=uartTxBuffGet();
    }
}

/* RECEIVE */

void uartRxBuffAdd(char c){
    char tc;
    tc=uartRxBuffC; //Get temporary cursor
    tc++; //Advance cursor
    if(tc==uartRxBuffLen) tc=0; //Past the end of the buffer?
    if(tc==uartRxBuffR) return; //Buffer full
    
    uartRxBuff[uartRxBuffC]=c; //Put character in buffer at cursor   
    uartRxBuffC=tc; //Advance cursor (using calculated position)
    uartRxBuffSize++; //Increase buffer size.
    if(uartRxBuffSize>uartRxBuffMax) uartRxBuffMax=uartRxBuffSize; //If it is the case, modify the max value reached for the buffer.
}

char uartRxBuffGetLen(){
    return uartRxBuffSize;
    /*
    if(uartRxBuffC>=uartRxBuffR) {
        return uartRxBuffC-uartRxBuffR;
    } else {
        return uartRxBuffC+(uartRxBuffLen-uartRxBuffR);
    }
    */
}

char uartRxBuffGet(){
    char r;
    if(uartRxBuffC==uartRxBuffR) return 0; //Buffer empty
    r=uartRxBuff[uartRxBuffR];
    uartRxBuffR++;
    if(uartRxBuffR==uartRxBuffLen)uartRxBuffR=0;
    uartRxBuffSize--; //Decrease buffer size.
    return r;
}

void uartRxString(const char* s){
    for(char i=0;i<strlen(s);i++){
        uartRxBuffAdd(s[i]);
    }
}


/* INTERRUPT PROCESSING */

//Generates an external IRQ by pulling down the line
void uartDoIRQ(){
    TRISA0=0; //Set pin as output. This will pull the line low.
    TRISA0=1; //Line as input
}

void uart_interrupt(){
    char c;
    if(RCIF){//There are bytes in the receive FIFO buffer
        c=RCREG; //Read byte from UART receiver
        uartRxBuffAdd(c);
        uartDoIRQ();
    }
}