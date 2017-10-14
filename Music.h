typedef int bool;
#define true 1
#define false 0
	
typedef struct note{
   int notePitch;				//What period to interrupt at
   int noteLength;			//Translates to eigth, quarter, half, full
												//1 = Eigth, 2 = Quarter, 3 = Half, 4 = Full
} note;

typedef struct song{
	 int tempo;
   struct note * notes;			//Song max length of 100 notes
	 int songLength; 
} song;
	


/***************************************************************
Pause_Song()
	Pauses song if song is currently playing

inputs:
  none
outputs:
	none
***************************************************************/
void Pause_Song(void);

/***************************************************************
Play_Song()
	Plays song if song is currently paused

inputs:
  none
outputs:
	none
***************************************************************/
void Play_Song(void);

/***************************************************************
Rewind_Song()
	Starts the song over and pauses song if song is currently 
	playing

inputs:
  none
outputs:
	none
***************************************************************/
void Rewind_Song(void);

/***************************************************************
Playing()
	Pauses song if song is currently playing

inputs:
  none
outputs:
	bool playing - returns either true or false depending on whether
	the song is playing or not
***************************************************************/
bool Playing(void);

/***************************************************************
Song_Index_Return()
	Pauses song if song is currently playing

inputs:
  none
outputs:
	int songIndex - returns the current note of the song 
***************************************************************/
int Song_Index_Return(void);

/***************************************************************
Song_Index_Increment()
	Moves to the next note in the song

inputs:
  int songLength - contains length of song  
outputs:
	none
***************************************************************/
void Song_Index_Increment(int songLength);
