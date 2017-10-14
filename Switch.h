// Switch.h
// Initializes and handles switch input.
// Cooper Carnahan and Faisal Mahmood
// 10/04/17
// Lab 5
// Saadallah
// 10/04/17

/***************************************************************
Switch_Init()
	Initializes switch input to the TM4C123.

inputs:
	none

outputs:
	none
***************************************************************/
void Switch_Init(int num, int interrupts);

/***************************************************************
Switch_Handler()
	Called when a switch is pressed, handles user input. Will either
	call function Play(), Pause(), Rewind(), or Change_Mode()

inputs:
	switchID - Identifier of which switch was pressed

outputs:
	none
***************************************************************/
void Switch_Handler(int switchID);

/***************************************************************
GPIO_PortF_Switch_Init()
	Initializes switch input to the TM4C123.

inputs:
	int switchNum - determines which switches are activated
	int interrupts - determines whether interrupts are activated

outputs:
	none
***************************************************************/
void GPIO_PortF_Switch_Init(int switchNum, int interrupts);

/***************************************************************
GPIO_PortD_Switch_Init()
	Initializes switch input to the TM4C123.

inputs:
	int numSwitches - determines how many switches are activated

outputs:
	none
***************************************************************/
void GPIO_PortD_Switch_Init(int numSwitches);

/***************************************************************
GPIO_PortD_Handler()
	Initializes switch input to PortD.

inputs:
  none
	
outputs:
	none
***************************************************************/
void GPIOPortD_Handler(void);

/***************************************************************
PD0_Handler()
	Handler for interrupts on PD0

inputs:
  none
outputs:
	none
***************************************************************/
void PD0_Handler(void);

/***************************************************************
PD1_Handler()
	Handler for interrupts on PD1

inputs:
  none
outputs:
	none
***************************************************************/
void PD1_Handler(void);

/***************************************************************
PD2_Handler()
	Handler for interrupts on PD2

inputs:
  none
outputs:
	none
***************************************************************/
void PD2_Handler(void);

