#include "..\inc\tm4c123gh6pm.h"
#include <stdio.h>
#include <stdint.h>
#include "..\Systick_4C123\Systick.h"
#include "MAX5353TestMain.c"

void PD0_Handler(void);
void PD1_Handler(void);
void PD2_Handler(void);

void GPIO_PortF_Switch_Init(int switchNum, int interrupts){
  SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20)==0){}; // allow time for clock to start
		GPIO_PORTF_LOCK_R=0x4C4F434B;			// unlocks CR register to allow PUR to be activated
		GPIO_PORTF_CR_R|=0x01;						// unlocks writes to PF0
		GPIO_PORTF_LOCK_R=0;							// relocks CR register	
																			// 2) no need to unlock PF4/PF0
		GPIO_PORTF_PCTL_R &= ~0x000F0F00; // 3) regular GPIO
	if(switchNum==2){
		GPIO_PORTF_AMSEL_R &= ~0x01;      // 4) disable analog function on PF0
		GPIO_PORTF_PUR_R |= 0x01;         // 5) pullup for PF0
		GPIO_PORTF_AFSEL_R &= ~0x01;      // 6) regular port function
		GPIO_PORTF_DEN_R |= 0x01;         // 7) enable digital port
		GPIO_PORTF_DIR_R &= 0xFFFFFFFE;	  // 8) set PF0 as an input
	}
	else if(switchNum==1){
		GPIO_PORTF_AMSEL_R &= ~0x10;      // 4) disable analog function on PF4
		GPIO_PORTF_PUR_R |= 0x10;         // 5) pullup for PF4
		GPIO_PORTF_AFSEL_R &= ~0x10;      // 6) regular port function
		GPIO_PORTF_DEN_R |= 0x10;         // 7) enable digital port
		GPIO_PORTF_DIR_R &= 0xFFFFFFEF;		// 8) set PF4 as an input

	}
	else{
		GPIO_PORTF_AMSEL_R &= ~0x11;      // 4) disable analog function on PF4 PF0
		GPIO_PORTF_PUR_R |= 0x11;         // 5) pullup for PF4 and PF0
		GPIO_PORTF_AFSEL_R &= ~0x11;      // 6) regular port function
		GPIO_PORTF_DEN_R |= 0x11;         // 7) enable digital port
		GPIO_PORTF_DIR_R &= 0xFFFFFFEE;	  // 8) set PF0 and PF4 as an input
	}
	if(interrupts){
		//GPIO_PORTF_IS_R |= 0x11;      // PF0 and PF4 are level sensitive
		GPIO_PORTF_IS_R &= ~0x11;       // PF0 and PF4 are edge-sensitive
		GPIO_PORTF_IBE_R &= ~0x11;      // PF0 and PF4 not both edges
		GPIO_PORTF_IEV_R |= 0x11;       // PF0 and PF4 are rising-edge or high level
		//GPIO_PORTF_IEV_R &= ~0x11;
		GPIO_PORTF_ICR_R |= 0x11;       // Clears Interrupt on PF0 and PF4
		GPIO_PORTF_IM_R |= 0x11;        // Arms interrupts on PF0 and Pf4
		NVIC_EN0_R |= 1<<30;            // Enables Interrupts on GPIOPORTF
  }
}

void GPIOPortF_Handler(void){
  if((GPIO_PORTF_RIS_R&0x10)==0x10){ // if an interrupt on PF4
    GPIO_PORTF_IM_R &= ~0x10;        // disarm interrupt on PF4
		Change_Mode();
		SysTick_Wait10ms(1);						 // debounce delay
		GPIO_PORTF_ICR_R |= 0x10;        // Clears interrupt on PF4
		GPIO_PORTF_IM_R |= 0x10;         // arm interrupt on PF4

	}
	if((GPIO_PORTF_RIS_R&0x01)==0x01){ // if an interrupt on PF0
		GPIO_PORTF_IM_R &= ~0x01;        // disarm interrupt on PF0 
    //Play();
		SysTick_Wait10ms(1);						 // debounce delay
    GPIO_PORTF_ICR_R |= 0x01;        // Clears interrupt on PF0
		GPIO_PORTF_IM_R |= 0x01;         // arm interrupt on PF0
  }
}


//Can't have more than 4 switches currently
void GPIO_PortD_Switch_Init(int numSwitches){
	int Or=0;
	if(numSwitches>4){
		numSwitches=4;
	}
	for(int i=0;i<numSwitches;i++){
		Or+=1<<i;
	}
	SYSCTL_RCGCGPIO_R |= 0x08;          // 1) activate clock for Port D
  while((SYSCTL_PRGPIO_R&0x08)==0){}; // allow time for clock to start
	GPIO_PORTD_AMSEL_R &= ~0x01;        // 4) disable analog function on PF0
  GPIO_PORTD_PCTL_R &= ~0xFFFFFFF;    // 3) regular GPIO
  //GPIO_PORTD_PUR_R |= 0x01;         // 5) pullup for PD0
  GPIO_PORTD_AFSEL_R &= ~Or;        // 6) regular port function
  GPIO_PORTD_DIR_R &= ~Or;	        // 8) set PD0-PD3 as an input
	GPIO_PORTD_DEN_R |= Or;           // 7) enable digital port
	GPIO_PORTD_IS_R &= ~Or;       // PD0->PDnumSwitches are edge-sensitive
	GPIO_PORTD_IBE_R &= ~Or;      // PD0->PDnumSwitches not both edges
	GPIO_PORTD_IEV_R |= Or;       // PD0->PDnumSwitches are rising-edge or high level
	//GPIO_PORTD_IEV_R &= Or;
	GPIO_PORTD_ICR_R |= Or;       // Clears Interrupt on PD0->PDnumSwitches
	GPIO_PORTD_IM_R |= Or;        // Arms interrupts on PD0->PDnumSwitches
  NVIC_PRI0_R = NVIC_PRI0_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; //Priority 3
	NVIC_EN0_R |= 1<<3;           // Enables Interrupts on GPIOPORTD
}

void GPIOPortD_Handler(void){
  if((GPIO_PORTD_RIS_R&0x01)==0x01){ // if an interrupt on PD0
    PD0_Handler();
	}
	if((GPIO_PORTD_RIS_R&0x02)==0x02){ // if an interrupt on PD0
   PD1_Handler();
	}
	if((GPIO_PORTD_RIS_R&0x04)==0x04){ // if an interrupt on PD0
   PD2_Handler();
	}
}

void PD0_Handler(void){
	GPIO_PORTD_IM_R &= ~0x01;        // disarm interrupt on PD0
	SysTick_Wait10ms(1);						 // debounce delay
	GPIO_PORTD_ICR_R |= 0x01;        // Clears interrupt on PD0
	GPIO_PORTD_IM_R |= 0x01;         // arm interrupt on PD0
	GPIO_PORTD_ICR_R |= 0x01;        // Clears interrupt on PD0

	pauseSong();
}

void PD1_Handler(void){
	GPIO_PORTD_IM_R &= ~0x02;        // disarm interrupt on PD1
	SysTick_Wait10ms(1);						 // debounce delay
	GPIO_PORTD_ICR_R |= 0x02;        // Clears interrupt on PD1
	GPIO_PORTD_IM_R |= 0x02;         // arm interrupt on PD1
  GPIO_PORTD_ICR_R |= 0x02;        // Clears interrupt on PD1
	
	playSong();
}

void PD2_Handler(void){
	GPIO_PORTD_IM_R &= ~0x04;        // disarm interrupt on PD2
	SysTick_Wait10ms(1);						 // debounce delay
	GPIO_PORTD_ICR_R |= 0x04;        // Clears interrupt on PD2
	GPIO_PORTD_IM_R |= 0x04;         // arm interrupt on PD2
  GPIO_PORTD_ICR_R |= 0x04;        // Clears interrupt on PD2
	
	rewindSong();
}