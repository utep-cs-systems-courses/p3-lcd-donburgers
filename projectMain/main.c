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

void drawGif() {
  // Initialize the LCD
  lcd_init();

  // Loop through the frames of the GIF
  for (int frame = 0; frame < frames; frame++) {
    // Set the drawing area to the size of the GIF image
    lcd_setArea(0, 0, animation_width - 1, animation_height - 1);

    // Iterate through the pixels of the current frame
    for (int y = 0; y < animation_height; y++) {
      for (int x = 0; x < animation_width; x++) {
        // Get the color value for the current pixel
        u_int color = kek[frame][y * animation_width + x];

        // Write the color to the LCD
        lcd_writeColor(color);
      }
    }

    // Delay between frames (adjust as needed for desired animation speed)
    __delay_cycles(50000);
  }
}

// Main function
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer

    buzzer_init();  // Initialize the buzzer
    button_init();  // Initialize the button
    P2DIR &= ~BIT0;     // Set P2.0 (S1) as input
    P2REN |= BIT0;      // Enable pull-up resistor
    P2OUT |= BIT0;      // Select pull-up resistor
    
    P1DIR |= (BIT0 | BIT2);  // Set P1.0 and P1.2 as outputs
    P1OUT &= ~(BIT0 | BIT2);  // Ensure LEDs are off to start

    // Wait for the button to be pressed
    while (1) {
        if ((P2IN & BIT0) == 0) {  // If button (P2.0) is pressed
            drawGif();
            for (int i = 0; melody[i] != -1; i++) {
                playBuzzer(melody[i], noteDurations[i]);
                delay_ms(1000 / noteDurations[i]);
                stopBuzzer();
                delay_ms(250 / noteDurations[i]);  // Short delay between notes
            }

            // Debounce delay (adjust as needed)
            __delay_cycles(200000);
            // Wait for button release
            while ((P2IN & BIT0) == 0);
        }
    }

    return 0;
}
