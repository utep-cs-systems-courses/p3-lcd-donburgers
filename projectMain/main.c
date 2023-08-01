#include <msp430.h>

// Define the frequencies for musical notes
#define NOTE_C4  261.63
#define NOTE_D4  293.66
#define NOTE_E4  329.63
#define NOTE_F4  349.23
#define NOTE_G4  392.00
#define NOTE_A4  440.00
#define NOTE_B4  493.88

// Define the frequency for the system clock (SMCLK)
#define SMCLK_FREQ 1000000  // Assuming SMCLK is set to 1MHz

// Define the melody sequence
float melody[] = {
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4
};

// Define the duration for each note in the melody
int noteDurations[] = {
    4, 4, 4, 4, 4, 4, 2  // 4 represents a quarter note, 2 represents a half note, etc.
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
void playBuzzer(float frequency)
{
    int timerPeriod = SMCLK_FREQ / frequency;  // Calculate timer period for desired frequency
    TA0CCR0 = timerPeriod;
    TA0CCR1 = timerPeriod / 2;  // 50% duty cycle
    TA0CTL |= TASSEL_2 + MC_1;  // Source: SMCLK, Mode: Up to CCR0
    P1OUT |= (BIT0 | BIT1);  // Turn on LEDs on P1.0 and P1.1
}

// Stop the buzzer
void stopBuzzer()
{
    TA0CTL = MC_0;  // Stop the timer
    P2OUT &= ~BIT6;  // Turn off the buzzer
    P1OUT &= ~(BIT0 | BIT1);  // Turn off LEDs on P1.0 and P1.1
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

    P1DIR |= (BIT0 | BIT1);  // Set P1.0 and P1.1 as outputs
    P1OUT &= ~(BIT0 | BIT1);  // Ensure LEDs are off to start

    // Play the melody
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        playBuzzer(melody[i]);
        delay_ms(1000 / noteDurations[i]);
        stopBuzzer();
        delay_ms(250 / noteDurations[i]);  // Short delay between notes
    }

    return 0;
}
