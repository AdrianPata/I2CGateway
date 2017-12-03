#include "main.h"

void interrupt interrupts(){
    i2c_interrupt();
    uart_interrupt();
}