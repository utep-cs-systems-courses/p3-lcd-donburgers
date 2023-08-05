#include <msp430.h>
#include "button.h"

// Initialize button on P2.0
void button_init(void)
{
    P2DIR &= ~BIT0;  // Set P2.0 as input
    P2REN |= BIT0;  // Enable pull-up resistor on P2.0
    P2OUT |= BIT0;  // Set pull-up resistor to pull-up mode
}
