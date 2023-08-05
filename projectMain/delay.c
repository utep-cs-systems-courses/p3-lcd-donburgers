#include <msp430.h>
#include "globals.h"

// Delay for a specified number of milliseconds
void delay_ms(int ms)
{
    while (ms--) 
    {
        __delay_cycles(SMCLK_FREQ / 1000);  // 1 ms delay
    }
}
