#include "main.h"

void i2c_interrupt(){
    char c,r;
    char RWbit,DAbit,Pbit; //I2C status bits
    
    if(SSP1IF){ //MSSP Interrupt
        SSP1IF=0; //Clear interrupt flag
        
        //Write bit is clear (master sent data) but BF is also clear (nothing sent).
        //This happens when "write bit" was set so master read some data and at some point it wants to respond with Nack and Stop,
        //the slave triggers the interrupt at Nack but the Stop bit is not set yet. The stop bit should be a signal that the data transfer
        //is completed, but when the interrupt occurs, Stop bit is not set yet.
        //In this situation I see that the Write bit is clear and the BF is also clear, which is a contradiction.
        //In this case I presume that a Stop bit will follow and I abort the execution to be ready to catch the next address from master.
        if(BF==0 && SSP1STATbits.R_nW==0){
            return;
        }
        
        if(BF) c=SSP1BUF; //Read I2C buffer
        
        //Read and store status bits
        //It's possible that those bits are changed during the execution of the interrupt routine if another byte is received before the routine finishes
        RWbit=SSP1STATbits.R_nW;
        DAbit=SSP1STATbits.D_nA;
        Pbit=SSP1STATbits.P;
        if(Pbit) {
            return; //If Stop bit is detected, abort processing
        }
        
        //Master wants to read data
        if(RWbit){
            r=0; //Default response
            
            if(i2c_command==1){ //Request for Rx buffer length
                r=uartRxBuffGetLen();
            }
            if(i2c_command==2){ //Send one byte from Rx buffer (to master)
                r=uartRxBuffGet();
            }
            if(i2c_command==3){ //Request for Tx buffer free space
                r=uartTxBuffLen-uartTxBuffSize-1; //The occupied space is buffer length minus one (space required for cursor advance).
            }
            if(i2c_command==5){ //Request for the maximum used space in Tx buffer
                r=uartTxBuffMax;
            }
            if(i2c_command==6){ //Request for the maximum used space in Rx buffer
                r=uartRxBuffMax;
            }
            
            SSP1BUF=r; //Send response byte
        }
        
        //Master wants to send data
        if(!RWbit){
            if(!DAbit){ //Received address
                i2c_command=0; //After an address with write bit set, a command will follow. Cancel the previous one.
                //Exit as fast as possible as the master is already sending the first byte after address.
                //Addendum to above comment which is valid only in Proteus simulator:
                //When used in hardware the SCL line must be released manually.
                CKP = 1; //CKP bit is set releasing SCL, allowing the master to clock the data out of the slave.
                return; 
            }
            if(DAbit){ //Master sent data
                if(i2c_command==0){
                    i2c_command=c;
                }else{
                    if(i2c_command==4){ //put bytes into Tx buffer
                        uartTxBuffAdd(c);
                    }
                }
            }
        }        
        
        CKP = 1; //CKP bit is set releasing SCL, allowing the master to clock the data out of the slave.
    }
}
