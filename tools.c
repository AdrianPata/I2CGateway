#include "main.h"

unsigned char readEEPROM(unsigned char address)
{
  EEADR = address; //Address to be read
  EECON1bits.EEPGD = 0;//Selecting EEPROM Data Memory
  EECON1bits.CFGS=0;//Access EEPROM
  EECON1bits.RD = 1; //Initialise read cycle
  return EEDATA; //Returning data
}

void writeEEPROM(unsigned char address, unsigned char datas)
{
  EEADR = address; //Address to write
  EEDATA = datas; //Data to write
  EECON1bits.EEPGD = 0; //Selecting EEPROM Data Memory
  EECON1bits.CFGS=0;//Access EEPROM
  EECON1bits.WREN = 1; //Enable writing of EEPROM
  EECON2=0x55; //Required sequence for write to internal EEPROM
  EECON2=0xAA; //Required sequence for write to internal EEPROM
  EECON1bits.WR = 1; //Initialise write cycle
  while(PIR2bits.EEIF == 0)//Checking for complition of write operation
  {  }
  PIR2bits.EEIF = 0; //Clearing EEIF bit
  EECON1bits.WREN = 0; //To disable write
}
