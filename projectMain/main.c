#include <msp430.h>
#include "globals.h"
#include "button.h"
#include "buzzer.h"
#include "delay.h"
#include "timer.h"

// Main function
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer

    buzzer_init();  // Initialize the buzzer
    button_init();  // Initialize the button
    
    P1DIR |= (BIT0 | BIT2);  // Set P1.0 and P1.2 as outputs
    P1OUT &= ~(BIT0 | BIT2);  // Ensure LEDs are off to start

    // Wait for the button to be pressed
    while ((P2IN & BIT0) == BIT0) {  // while button is not pressed
        // do nothing
    }

    // Once button is pressed, play the melody
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        playBuzzer(melody[i], noteDurations[i]);
        delay_ms(1000 / noteDurations[i]);
        stopBuzzer();
        delay_ms(250 / noteDurations[i]);  // Short delay between notes
    }

    return 0;
}