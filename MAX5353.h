// MAX5353.h
// Cooper Carnahan and Faisal Mahmood
// 10/04/17
// Lab 5
// Saadallah
// 10/04/17
// Runs on LM4F120/TM4C123
// Use SSI0 to send a 16-bit code to the MAX5353.

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
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


typedef struct note{
   int notePitch;				//What period to interrupt at
   int noteLength;			//Translates to eigth, quarter, half, full
												//1 = Eigth, 2 = Quarter, 3 = Half, 4 = Full
} note;

typedef struct song{
	 int tempo;
   struct note * notes;			//Song max length of 100 notes
} song;

//********DAC_Init*****************
// Initialize Max5353 12-bit DAC
// inputs:  initial voltage output (0 to 4095)
// outputs: none
// assumes: system clock rate less than 20 MHz
void DAC_Init(uint16_t data);

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out(uint16_t code);

//********DAC_Out2*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: reply is returned
// send the 16-bit code to the SSI, return a reply
uint16_t DAC_Out2(uint16_t code);

//********DAC_InitRaw*****************
// Initialize Max5353 12-bit DAC with PA2,PA5 
// with alternate functionality while PA3 is 
// configured with regular functionality for
// FSS usage
// inputs:  initial voltage output (0 to 4095)
// outputs: none
// assumes: system clock rate less than 20 MHz
void DAC_InitRaw(void);

//********DAC_Out*****************
// Send data to Max5353 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
// send the 16-bit code to the SSI, 
void DAC_OutRaw(uint16_t code);
