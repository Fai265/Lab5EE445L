// MAX5353TestMain.c
// Runs on LM4F120/TM4C123
// Test the functions provided in MAX5353.c by outputting
// a sine wave at a particular frequency.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// SSI0Clk (SCLK, pin 4) connected to PA2
// SSI0Fss (!CS, pin 2) connected to PA3
// SSI0Tx (DIN, pin 3) connected to PA5
// see Figure 7.19 for complete schematic

#include <stdint.h>
#include "MAX5353.h"
#include "SysTick.h"
#include "Timer0A.h"
#include "Switch.h"
#include "../inc/tm4c123gh6pm.h"
#include "Music.h"
#include "..\Lab3EE445L\src\PLL.h"

#define PF2             (*((volatile uint32_t *)0x40025010)) //Blue LED

#define A2  109
#define A2s 116
#define B2  123
#define C3  130
#define C3s 138
#define D3  146
#define D3s 155
#define E3  164
#define F3  174
#define F3s 184
#define G3  195
#define G3s 207
#define A3  219
#define A3s 233
#define B3  246
#define C4  261
#define C4s 277
#define D4  293
#define D4s 311
#define E4  329
#define F4  349
#define F4s 369
#define G4  391
#define G4s 415
#define A4  440
#define A4s 466
#define B4  493
#define C5  523
#define C5s 554
#define D5  587
#define D5s 622
#define E5  659
#define F5  698
#define F5s 739
#define G5  783
#define G5s 830
#define A5  880


	note StarWarsNotes[100] = {	//Each measure on a different line
    {D4, 1}, {D4, 1}, {D4, 1}, 
    {G4, 3}, {D5, 3}, 
    {C5, 1}, {B4, 1}, {A4, 1}, {G5, 3}, {D5, 2},
		{C5, 1}, {B4, 1}, {A4, 1}, {G5, 3}, {D5, 2},
		{C5, 1}, {B4, 1}, {C5, 1}, {A4, 3}, {D5, 1}, {D5, 1},
		{G4, 3}, {D5, 3}, 
    {C5, 1}, {B4, 1}, {A4, 1}, {G5, 3}, {D5, 2},
		{C5, 1}, {B4, 1}, {A4, 1}, {G5, 3}, {D5, 2},
		{C5, 1}, {B4, 1}, {C5, 1}, {A4, 2}, {0, 2}, {D5, 1}, {D5, 1},
		{E4, 3}, {C5, 1}, {B4, 1}, {A4, 1}, {G4, 1},
		{G4, 1}, {A4, 1}, {B4, 1}, {A4, 1}, {E4, 1}, {F4s, 2}, {D4, 1}, {D4, 1},
		{E4, 3}, {C5, 1}, {B4, 1}, {A4, 1}, {G4, 1},
		{G5, 4}
	};
	song StarWars = {.tempo = 120, .notes = StarWarsNotes, .songLength=100};


//static uint8_t play = 0;
static uint32_t i;

void EnableInterrupts(void);

// 12-bit 32-element sine wave
// multiply each value by 2 to shift into bits 12:1 of SSI packet
// three control bits in 15:13 are all zero for immediate DAC update
// book figure shows MAX5353 in unipolar rail-to-rail configuration
// that means when wave[n] = 0x0000 (LSB = 0), output = 0
//                 wave[n] = 0x1000 (LSB = 0), output = Vref
//                 wave[n] = 0x1FFE (LSB = 0), output = 2*Vref
const uint16_t wave[32] = {
  2048*2,2448*2,2832*2,3186*2,3496*2,3751*2,3940*2,4057*2,4095*2,4057*2,3940*2,
  3751*2,3496*2,3186*2,2832*2,2448*2,2048*2,1648*2,1264*2,910*2,600*2,345*2,
  156*2,39*2,0*2,39*2,156*2,345*2,600*2,910*2,1264*2,1648*2};

void portF_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R & 0x20) == 0);
	GPIO_PORTF_DIR_R |= 0x06;   // make PF2 out (built-in blue LED)
	GPIO_PORTF_AFSEL_R &= ~0x06;// disable alt funct on PF2
	GPIO_PORTF_DEN_R |= 0x06;   // enable digital I/O on PF2                             
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000; // configure PF2 as GPIO
	GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF  
}
int main(void){
	PLL_Init(Bus80MHz);
  i=0;															 // This is the index of the song array
	portF_Init();
  DAC_Init(0x1000);                  // initialize with command: Vout = Vref
  SysTick_Init();
	GPIO_PortF_Switch_Init(4, 1);
  GPIO_PortD_Switch_Init(3);
	EnableInterrupts();
	//play = 1;    //IF THINGS DON'T WORK UNCOMMENT THIS

	while(1){
		while(Playing() == true){
			i=Song_Index_Return();  //comment this out if things don't work
			PF2 ^= 0x04;
			int wait = 60000 / StarWars.tempo;	//60000 milliseconds in a minute, divide by tempo to get
																					//Milliseconds per beat
			int exp = (1 << StarWars.notes[i].noteLength);	//rudimentary mapping
			//i.e. Quarter Note: noteLength = 2. 2^2 = 4 / 4 = 1. Quarter Note gets full wait
			//Eigth gets half wait, Half gets double, Full gets quadruple
			
			wait = (wait / 4) * exp;
			wait /= 10;	//Make it compatible with SysTick_Wait10ms
			
			Timer0A_Init((*DAC_Out), (800000 / StarWars.notes[i].notePitch), 0);	//Interrupt at Note frequency
			
			//i = ((i + 1) % 100);  //uncomment this out if things don't work
			Song_Index_Increment(StarWars.songLength);
			if(StarWars.notes[i].noteLength == 0){
				wait = 0;
			}
			SysTick_Wait10ms(wait);
		}
	}
}

//void pauseSong(){
//	//Disable Interrupts
//	TIMER0_CTL_R = 0x00000000;    //disable TIMER0A
//	NVIC_ST_CTRL_R = 0;           //disable SysTick
//	play = 0;
//}

//void playSong(){
//	//Enable Interrupts
//	TIMER0_CTL_R = 0x00000001;    //enable TIMER0A
//																//enable SysTick with core clock
//	NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
//	play = 1;
//}

//void rewindSong(){
//	i = 0;
//	pauseSong();
//}


