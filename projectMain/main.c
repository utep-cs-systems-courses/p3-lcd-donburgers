#include <msp430.h>
#include "globals.h"
#include "button.h"
#include "buzzer.h"
#include "delay.h"
#include "timer.h"
#include "grlib.h"
#include "darksouls_bonfire.h" 

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

// Main function
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer

    buzzer_init();  // Initialize the buzzer
    button_init();  // Initialize the button
    
    P1DIR |= (BIT0 | BIT2);  // Set P1.0 and P1.2 as outputs
    P1OUT &= ~(BIT0 | BIT2);  // Ensure LEDs are off to start    // Wait for the button to be pressed
    while ((P2IN & BIT0) == BIT0) {  // while button is not pressed
        // do nothing
    }
    Graphics_initialize();
    // Draw the image at the desired coordinates (e.g., x=0, y=0)
    Graphics_drawImage(&darksouls_bonfire4BPP_COMP_RLE4, 0, 0);
    // Once button is pressed, play the melody
    for (int i = 0; melody[i] != -1; i++)
      {
        playBuzzer(melody[i], noteDurations[i]);
        delay_ms(1000 / noteDurations[i]);
        stopBuzzer();
        delay_ms(250 / noteDurations[i]);  // Short delay between notes
    }

    return 0;
}
