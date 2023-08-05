#ifndef GLOBALS_H
#define GLOBALS_H

#include "notes.h"

// Define the frequency for the system clock (SMCLK)
#define SMCLK_FREQ 1000000  // Assuming SMCLK is set to 1MHz

extern float melody[];
extern int noteDurations[];

void timerAUpmode();
void buzzer_init();
void playBuzzer(float frequency, int duration);
void stopBuzzer();
void delay_ms(int ms);

#endif
