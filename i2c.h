/* 
 * File:   i2c.h
 * Author: MPLAB
 *
 * Created on August 8, 2016, 5:07 PM
 */

#ifndef I2C_H
#define	I2C_H

//Last command received from master
char i2c_command=0;
    //0: Unused
    //1: Get amount of data available in Rx buffer
    //2: Get data from Rx buffer
    //3: How much space is free in the Tx buffer?
    //4: Put data into Tx buffer
    //5: Request for the maximum used space in Tx buffer
    //6: Request for the maximum used space in Rx buffer

void i2c_interrupt();

#endif	/* I2C_H */

