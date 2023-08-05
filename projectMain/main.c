#include <msp430.h>
#include "notes.h"
#include "button.h"


// Define the frequency for the system clock (SMCLK)
#define SMCLK_FREQ 1000000  // Assuming SMCLK is set to 1MHz

float melody[] = {
    NOTE_E6, NOTE_D6, NOTE_A5,  
    NOTE_E6, NOTE_D6, NOTE_G6, NOTE_F6, NOTE_E6, //Measure 2
    NOTE_A6, NOTE_E6, // Measure 3
    NOTE_E6, NOTE_F6, NOTE_G6, NOTE_E6, 
    NOTE_E6, NOTE_D6, NOTE_C6, NOTE_B5, 
    NOTE_B5, NOTE_C6, NOTE_D6, NOTE_B5,
};

// Define the duration for each note in the melody
int noteDurations[] = {
  //1 = whole note
  //2 = Half notes
    2, 2, 1, // 1st Measure 
    2, 2, 1, 2, 1, // 2nd Measure 
    2, 1, 
    2, 2, 2, 1, 
    2, 2, 2, 1, 
    2, 2, 2, 1, 
    
    
};


// Set up Timer A to run in up mode
void timerAUpmode()
{
    TA0CCR0 = 0;  // Initialize counter to 0
    TA0CCR1 = 0;  // Initialize duty cycle to 0% (off)
    TA0CTL |= TASSEL_2 + MC_1;  // Source: SMCLK, Mode: Up to CCR0
    TA0CCTL1 |= OUTMOD_7;  // Output mode: Reset on CCR1, set on CCR0
}

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


// Delay for a specified number of milliseconds
void delay_ms(int ms)
{
    while (ms--) 
    {
        __delay_cycles(SMCLK_FREQ / 1000);  // 1 ms delay
    }
}

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
