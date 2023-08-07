																																																							MSP430 Buzzer Melody Player - Dark Souls Lord Gwyn Theme

Overview
Embrace the challenge of the Dark Souls universe right on your MSP430! This project plays the haunting theme of Lord Gwyn, the final boss in Dark Souls, through a buzzer. Whether you're a seasoned Chosen Undead or just beginning your journey in Lordran, this melody is sure to evoke memories of epic battles and hard-fought victories.

Features
Lord Gwyn's Theme: Relive the climactic battle with Lord Gwyn, the Lord of Cinder, through the power of PWM and a simple buzzer.
Button Interface: Press a button on P2.0 to face your destiny and start the melody. Are you ready to link the fire?
LED Feedback: LEDs on P1.0 and P1.2 provide visual feedback, like the glowing embers of a bonfire.
Interrupt Handling: Interrupt your fate and stop the melody with a Timer1_A0 interrupt, just as Gwyn interrupted the Age of Fire.

🎮
The melody played is the iconic theme from the final boss fight with Lord Gwyn in Dark Souls. This theme encapsulates the melancholic, challenging, and rewarding essence of the game. Just as players must time their rolls and parries to defeat Gwyn, this code carefully orchestrates interrupts and timers to bring the theme to life. Now you don't have to defeat Gwyn to hear this mesmerizing theme; just press a button and prepare to die... musically!

How to Compile and Run
Prerequisites
Ensure that you have the MSP430 development tools installed, including msp430-elf-gcc.
Connect the MSP430G2553 microcontroller to your computer.

Compilation
Open a Terminal: Navigate to the directory containing the source files (main.c, button.c, timer.c, delay.c, buzzer.c), header files, and the Makefile.

Compile the Code: Run the following command to compile the code:

bash
make
This will use the Makefile to compile the code with the specified flags and target MCU (MSP430G2553). It will create an ELF file named main.elf.

Upload and Run
Follow the instructions specific to your development environment or programmer to upload the main.elf file to the MSP430G2553 microcontroller. Once uploaded, reset the microcontroller to start playing the theme of Lord Gwyn.
