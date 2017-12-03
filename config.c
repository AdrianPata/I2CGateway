# include "main.h"

void config(){
    SCS1=0;SCS0=0; //Clock determined by FOSC<2:0> in Configuration Word 1
    IRCF3=1;IRCF2=1;IRCF1=1;IRCF0=0; //8 MHz or 32 MHz HF(see Section 5.2.2.1 ?HFINTOSC?)
    
    ANSA0=0;ANSA1=0;ANSA2=0;ANSA4=0; //Set all inputs as digital
    
    //IRQ
    TRISA0=1; //Set pin as input
    LATA0=0; //Pull line low (When RCA0 is configured as output, it will pull the line low)
    
    //EUSART
    RXDTSEL=1; //RX pe pin RA5
    TXCKSEL=1; //TX pe pin RA4
    TRISA5=1; //Pin is input
    CREN=1; //Enables receiver
    TXEN=1; //Transmit enabled
    SYNC=0; //Synchronous mode
    //EUSART Baud Rate Generator 
    //FOSC = 8.000 MHz
    //Read values from EEPROM
    BRGH=readEEPROM(0x01);
    BRG16=readEEPROM(0x02);
    SPBRGH=readEEPROM(0x03);
    SPBRG=readEEPROM(0x04);    
    SPEN=1; //Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
    
    //I2C
    TRISA1=1; TRISA2=1; //When enabled, the SDA and SCL pins must be configured as inputs.
    SSP1ADD=readEEPROM(0x00); //Slave address in EEPROM at 0x00
    SSPM3=0;SSPM2=1;SSPM1=1;SSPM0=0; //I2C Slave mode, 7-bit address
    SEN=1; //Clock stretching is enabled for both slave transmit and slave receive (stretch enabled)
    SSPEN=1;//Enables the serial port and configures the SDA and SCL pins as the source of the serial port pins
    
    //Interrupts
    RCIE=1; //Enables the USART receive interrupt
    SSP1IE=1; //Enables the MSSP interrupt
    PEIE=1; //Enables all active peripheral interrupts
    GIE=1; //Global Interrupt Enable bit
    
    TMR1ON=1; //TMR1
}
