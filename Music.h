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
	
void pauseSong(void);

void playSong(void);

void rewindSong(void);

bool Playing(void);

int Song_Index_Return(void);

void Song_Index_Increment(int songLength);
