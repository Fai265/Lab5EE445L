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
void Switch_Init();

/***************************************************************
Switch_Handle()
	Called when a switch is pressed, handles user input.

inputs:
	switchID - Identifier of which switch was pressed

outputs:
	none
***************************************************************/
void Switch_Handle(int switchID);