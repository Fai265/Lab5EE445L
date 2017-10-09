// ***************** Timer0A_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq), 32 bits
// Outputs: none
void Timer0A_Init(void(*task)(uint16_t), uint32_t period, uint8_t instrument);


void Timer0A_Handler(void);


/***************************************************************
Change_Mode()
	Changes the current instrument

inputs:
	none

outputs:
	none
***************************************************************/
void Change_Mode(void);
