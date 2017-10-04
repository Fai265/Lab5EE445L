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
Play()
	Called when switch 2 is pressed, handles user input. Will 
	cause the music to begin playing 

inputs:
	none
	
outputs:
	none
***************************************************************/
void Play(void);

/***************************************************************
Rewind()
	Called when switch 1 is held, handles user input. Will 
	cause the music to go back to the beginning and wait for 
  user to begin playing again	

inputs:
	none
	
outputs:
	none
***************************************************************/
void Rewind(void);

/***************************************************************
Pause()
	Called when switch 1 is pressed, handles user input. Will 
	cause the music to go back to the beginning and wait for 
  user to begin playing again	

inputs:
	none
	
outputs:
	none
***************************************************************/
void Pause(void);