#include <msp430.h>
#include "globals.h"
#include "button.h"
#include "buzzer.h"
#include "delay.h"
#include "timer.h"

// Define the frequency for the system clock (SMCLK)
#define SMCLK_FREQ 1000000  // Assuming SMCLK is set to 1MHz

float melody[] = {
  NOTE_E6, NOTE_D6, NOTE_A5,
  NOTE_E6, NOTE_D6, NOTE_G6, NOTE_F6, NOTE_E6, //Measure 2
  NOTE_A6, NOTE_E6, // Measure 3
  NOTE_E6, NOTE_F6, NOTE_G6, NOTE_E6, //4th,
  NOTE_E6, NOTE_D6, NOTE_C6, NOTE_B5, //5th,
  NOTE_B5, NOTE_C6, NOTE_D6, NOTE_B5, //6th
  NOTE_E4, NOTE_C4, NOTE_B4, NOTE_C5, 
  NOTE_B4, NOTE_G4, NOTE_E4, NOTE_G4, 
  NOTE_B4, NOTE_C5, NOTE_B4, NOTE_C5, 
  NOTE_B4, NOTE_G4, NOTE_E4, NOTE_G4, 
  NOTE_B5, NOTE_C5, NOTE_B4, NOTE_G4, 
  NOTE_E4
};

duration for each note in the melody
int noteDurations[] = 
{
  2, 2, 1, // 1st Measure
  2, 2, 1, 2, 1, // 2nd Measure
  2, 1, // 3rd Measure
  2, 2, 2, 1,// 4th
  2, 2, 2, 1, // 5th
  2, 2, 2, 1, // 6th
  1, 1, 1, 1,
  1, 1, 1, 1, 
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  3
};

volatile unsigned int stopSongFlag = 0; // Global flag to stop the song

int main(void) 
{
  WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer
  buzzer_init();  // Initialize the buzzer
  button_init();  // Initialize the button

  P1DIR |= (BIT0 | BIT2);  // Set P1.0 and P1.2 as outputs
  P1OUT &= ~(BIT0 | BIT2);  // Ensure LEDs are off to start
  P2DIR &= ~BIT0; // Set P2.0 as Input
  P2IE |= BIT0;  // Enable interrupt for P2.0
  P2IES |= BIT0; // High-to-low transition
  P2IFG &= ~BIT0; // Clear interrupt flag

  while (1) {
    if ((P2IN & BIT0) == 0) {  // If button on P2.0 is pressed
      for (int i = 0; melody[i] != -1 && !stopSongFlag; i++) { // Check 'stopSongFlag'
        playBuzzer(melody[i], noteDurations[i]);
        delay_ms(1000 / noteDurations[i]);
        stopBuzzer();
        delay_ms(250 / noteDurations[i]);  // Short delay between notes
      }
      stopSongFlag = 0; // Reset the flag for next time
    }
  }

  return 0;
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void CCR0_ISR(void)
{
  if (stopSongFlag) {
    TA1CTL = MC_0; // Stop Timer
    stopBuzzer(); // Turn off the buzzer Q
    TA1CCTL0 &= ~CCIFG; // Clear the interrupt flag (if needed)
    __bic_SR_register_on_exit(LPM0_bits); // Exit low-power mode
    return;
  }
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
  stopSongFlag = 1; // Set flag to stop the song
  P2IFG &= ~BIT0;  // Clear interrupt flag
}
