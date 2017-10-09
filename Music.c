#include <stdint.h>
#include "MAX5353.h"
#include "SysTick.h"
#include "Timer0A.h"
#include "Switch.h"
#include "../inc/tm4c123gh6pm.h"

typedef int bool;
#define true 1
#define false 0
	
static int songIndex=0;
static bool play=true;

void pauseSong(void){
	//Disable Interrupts
	TIMER0_CTL_R = 0x00000000;    //disable TIMER0A
	//NVIC_ST_CTRL_R = 0;           //disable SysTick
	play = 0;
}

void playSong(void){
	//Enable Interrupts
	TIMER0_CTL_R = 0x00000001;    //enable TIMER0A
																//enable SysTick with core clock
	//NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
	play = 1;
}

void rewindSong(void){
	songIndex = 0;
	pauseSong();
}

bool Playing(void){
	return play;
}

int Song_Index_Return(void){
	return songIndex;
}

void Song_Index_Increment(int songLength){
	songIndex = ((songIndex + 1) % songLength);
}
