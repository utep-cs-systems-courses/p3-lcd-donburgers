#include <msp430.h>
#include "globals.h"
#include "timer.h"

// Initialize buzzer on P2.6
void buzzer_init()
{
    timerAUpmode();  // Set up timer for PWM
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;  // Set P2.6 as output
}

// Play a note on the buzzer
void playBuzzer(float frequency, int duration)
{
    int timerPeriod = SMCLK_FREQ / frequency;  // Calculate timer period for desired frequency
    TA0CCR0 = timerPeriod;
    TA0CCR1 = timerPeriod / 2;  // 50% duty cycle
    TA0CTL |= TASSEL_2 + MC_1;  // Source: SMCLK, Mode: Up to CCR0

    // Blink LEDs based on duration
    if (duration == 1) {  // If it's a whole note
        P1OUT |= BIT0;  // Turn on LED on P1.0
        P1OUT &= ~BIT2;  // Ensure LED on P1.2 is off
    }
    else if (duration == 2) {  // If it's a half note
        P1OUT |= BIT2;  // Turn on LED on P1.2
        P1OUT &= ~BIT0;  // Ensure LED on P1.0 is off
    }
}

// Stop the buzzer
void stopBuzzer()
{
    TA0CTL = MC_0;  // Stop the timer
    P2OUT &= ~BIT6;  // Turn off the buzzer
    P1OUT &= ~(BIT0 | BIT2);  // Turn off LEDs on P1.0 and P1.2
}