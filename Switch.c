#include "..\inc\tm4c123gh6pm.h"
#include <stdio.h>
#include <stdint.h>
void Switch_Init(int num, int interrupts){
  SYSCTL_RCGCGPIO_R |= 0x20;        // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x20)==0){}; // allow time for clock to start
	GPIO_PORTF_LOCK_R=0x4C4F434B;			// unlocks CR register to allow PUR to be activated
	GPIO_PORTF_CR_R|=0x01;						// unlocks writes to PF0
	GPIO_PORTF_LOCK_R=0;							// relocks CR register	
                                    // 2) no need to unlock PF4/PF0
  GPIO_PORTF_PCTL_R &= ~0x000F0F00; // 3) regular GPIO
	if(num==2){
  GPIO_PORTF_AMSEL_R &= ~0x01;      // 4) disable analog function on PF0
  GPIO_PORTF_PUR_R |= 0x01;         // 5) pullup for PF0
  GPIO_PORTF_AFSEL_R &= ~0x01;      // 6) regular port function
  GPIO_PORTF_DEN_R |= 0x01;         // 7) enable digital port
	GPIO_PORTF_DIR_R &= 0xFFFFFFFE;	  // 8) set PF0 as an input
	}
	else if(num==1){
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
		//GPIO_PORTF_IS_R |= 0x11;       // PF0 and PF4 are level sensitive
		GPIO_PORTF_IS_R &= ~0x11;       // PF0 and PF4 are edge-sensitive
		GPIO_PORTF_IBE_R &= ~0x11;      // PF0 and PF4 not both edges
		GPIO_PORTF_IEV_R |= 0x11;       // PF0 and PF4 are rising-edge or high level
		//GPIO_PORTF_IEV_R &= ~0x11;
		GPIO_PORTF_ICR_R |= 0x11;       // Clears Interrupt on PF0 and PF4
		GPIO_PORTF_IM_R |= 0x11;        // Arms interrupts on PF0 and Pf4
		NVIC_PRI7_R |= 0xFFF4FFFF;      // Priority 2
		NVIC_EN0_R |= 1<<30;   // Enables Interrupts on GPIOPORTF
  }
}
void Switch_Handler(int switchID){
}
