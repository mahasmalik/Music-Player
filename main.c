
/**
 * \file
 *
 * \brief Empty user application template
 * \Maha Malik and Srilakshmi Godavarti
 */

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPK_ON SET_BIT(PORTA, 0);
#define SPK_OFF CLR_BIT(PORTA, 0);
#define NUM_NOTES 9

/*#define A_NOTEO1
#define A_SHARP_NOTEO1
#define B_NOTEO1
#define B_SHARP_NOTEO1
#define C_NOTEO1
#define C_SHARP_NOTEO1
#define D_NOTEO1
#define D_SHARP_NOTEO1
#define E_NOTEO1
#define E_SHARP_NOTEO1
#define F_NOTEO1
#define F_SHARP_NOTEO1
#define G_NOTEO1
#define G_SHARP_NOTEO1*/

void playNote(int freq, int dur);


struct note{
	int frequency;
	int duration;
	int delay;
};

//int NAMES[NUM_NOTES] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'Bb'};

//pitch = 1
int FREQUENCYO4[NUM_NOTES] = {554, 622, 699, 784, 880, 440, 494, 1245, 523};
int DURATION = 10000;
int DURATION_M[3] = {1,2,4};

/*ccdcfe ccdcgf ccCafed (Bb)(Bb)afgf*/
struct note SONG_HB[24] = {
	{0,1}, {0,1}, {1,1}, {0,1}, {2,1}, {1,0},
	{0,1}, {0,1}, {1,1}, {0,1}, {4,1}, {3,0},
	{0,1}, {0,1}, {7,1}, {4,1}, {3,1}, {2,1}, {1,0},
	{8,2}, {8,1}, {5,1}, {3,1}, {8,0}
};

/*edcdeee dddegg*/
struct note SONG_MLL[26] = {
	{2,1}, {1,1}, {0,1}, {1,1}, {2,1}, {2,1}, {2,0},
	{1,1}, {1,1}, {1,0}, {2,1}, {3,1}, {2,0},
	{2,1}, {1,1}, {0,1}, {1,1}, {2,1}, {2,1}, {2,0},
	{2,1}, {1,1}, {1,1}, {2,1}, {1,1}, {0,0}
};

/*ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc*/
struct note SONG_TTLS[42] = {
	{0,1}, {6,1}, {4,1}, {3,1}, {5,1}, {5,1}, {4,0},
	{3,1}, {3,1}, {2,1}, {2,1}, {1,1}, {1,1}, {0,0},
	{4,1}, {4,1}, {3,1}, {3,1}, {2,1}, {2,1}, {1,0},
	{4,1}, {4,1}, {3,1}, {3,1}, {2,1}, {2,1}, {1,0},
	{0,1}, {0,1}, {4,1}, {4,1}, {5,1}, {5,1}, {4,0},
	{3,1}, {3,1}, {2,1}, {2,1}, {1,1}, {1,1}, {0,0}
};

/*ccgg aaa-ag ffee ddc gggf-f eeed cgggf-ff feeed*/
struct note SONG_BB[37] = {
	{0,1}, {0,1}, {2,1}, {2,1},
	{3,1}, {3,1}, {3,2}, {3,2}, {2,0},
	{3,1}, {3,1}, {2,1}, {2,1},
	{1,1}, {1,1}, {0,1}, 
		
	{3,1}, {3,2}, {3,2}, {2,2}, {2,1},
	{1,1}, {1,1}, {1,1}, {0,1}, 
	{0,1}, {3,1}, {3,1}, {3,1}, {2,2}, {2,2}, {2,1},
	{2,1}, {1,1}, {1,1}, {1,1}, {0,1}
};

/*float tempoHB = 5.0;
float tempoMLL = 5.0;
float tempoBB = 5.0;*/
int tempo = 5;
int pitch = 1;
int play = 1;
int volume = 2;


int is_pressed(int r, int c){
	DDRC = 0x00;
	PORTC = 0x00;

	SET_BIT(DDRC, r); //?
	CLR_BIT(PORTC, r);
	CLR_BIT(DDRC, c+4);
	SET_BIT(PORTC, c+4);
	avr_wait(1);

	if(!GET_BIT(PINC,c + 4)){
		return 1;
	}
	return 0;
}

int getKey(){
	int r, c;
	for(r = 0; r < 4; ++r){
		for(c=0; c < 4; ++c){
			if(is_pressed(r,c)){
				return (r*4)+c+1;
			}
		}
	}
	return 0;
}

void playHB(){
	int i;
	for (i = 0; i < 24; i++){
		//playNote(440, 1000);
		//playNote(SONG_HB[i].duration, SONG_HB[i].frequency);
		if(getKey() == 15){
			play = 0;
			lcd_pos(1,0);
			lcd_puts2("Paused");
			avr_wait(5000);
			return;
		}
		if(play){
			if(pitch == 1){
				playNote(FREQUENCYO4[SONG_HB[i].frequency], (DURATION / DURATION_M[SONG_HB[i].duration]));
			}else{
				playNote(((float)pitch*2.25)*FREQUENCYO4[SONG_HB[i].frequency], (DURATION / DURATION_M[SONG_HB[i].duration]));
			}
			avr_wait(2500*((float)tempo/5));
		}
		//avr_wait(SONG_HB[i].delay*10000);
	}
}

void playMLL(){
	int i;
	for (i = 0; i < 26; i++){
		if(getKey() == 15){
			play = 0;
			lcd_pos(1,0);
			lcd_puts2("Paused");
			avr_wait(5000);
			return;
		}
		if(play){
			if(pitch == 1){
				playNote(FREQUENCYO4[SONG_MLL[i].frequency], (DURATION / DURATION_M[SONG_MLL[i].duration]));
			}else{
				playNote(((float)pitch*2.25)*FREQUENCYO4[SONG_MLL[i].frequency], (DURATION / DURATION_M[SONG_MLL[i].duration]));
			}
			avr_wait(1000*((float)tempo/5));
		}
		//avr_wait(SONG_MLL[i].delay*10000);
	}
}

void playBB(){
	int i;
	for (i = 0; i < 37; i++){
		if(getKey() == 15){
			play = 0;
			lcd_pos(1,0);
			lcd_puts2("Paused");
			avr_wait(5000);
			return;
		}
		if(play){
			if(pitch == 1){
				playNote(FREQUENCYO4[SONG_BB[i].frequency], (DURATION / DURATION_M[SONG_BB[i].duration]));
			}else{
				playNote(((float)pitch*2.25)*FREQUENCYO4[SONG_BB[i].frequency], (DURATION / DURATION_M[SONG_BB[i].duration]));
			}
			
			avr_wait(500*((float)tempo/5));
		}		
		//avr_wait(SONG_TTLS[i].delay*10000);
	}
}


void playNote(int freq, int dur){
	int period = ((float)(1.0 / freq))*10000;
	int t_low = period/2;
	int t_high = period/2;
	
	/*char buf[16];
	sprintf(buf, "%d", period);
	lcd_pos(1,0);
	lcd_puts2(buf);*/
	if(volume == 1){
		t_high = period/4;
		t_low = period - t_high;
	}
	if(volume == 2){
		t_low = period/2;
		t_high = period/2;
	}
	if(volume == 3){
		t_low = period/8;
		t_high = period - t_low;
	}
	//int t = (period / 2);
	
	int k = dur/period;
	
	int i;
	for(i = 0; i < k; ++i){
		SET_BIT(PORTB, 3);
		avr_wait(t_low);
		CLR_BIT(PORTB, 3);
		avr_wait(t_high);
	}
}


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	avr_init();
	lcd_init();
	lcd_clr();
	lcd_pos(0,0);
	
	lcd_puts2("Choose SONG");
	lcd_pos(1,0);
	char buffer[16];
	sprintf(buffer, "%d  %d  %d", tempo, pitch, volume);
	lcd_puts2(buffer);
	SET_BIT(DDRB, 3);
	//DDRA = 0x01;
	
	while(1){
		lcd_pos(1,0);
		char buffr[16];
		sprintf(buffr, "%d  %d  %d", tempo, pitch, volume);
		lcd_puts2(buffr);
		
		if(!play){
			continue;
		}else{
			if(getKey() == 1){
				lcd_clr();
				lcd_puts2("Birthday");
				playHB();
				lcd_clr();
			}
			if(getKey() == 2){
				lcd_clr();
				lcd_puts2("Mary Lamb");
				playMLL();
				lcd_clr();
			}
			if(getKey() == 3){
				lcd_clr();
				lcd_puts2("Baa Sheep");
				playBB();
				lcd_clr();
			}
			if(getKey() == 4){
				//tempo up
				if(tempo != 10){
					tempo += 1;
				}
				/*lcd_pos(1,0);
				char bufT[10];
				sprintf(bufT, "T Up: %d", tempo);
				lcd_puts2(bufT);*/
			}
			if(getKey() == 8){
				//tempo down
				if(tempo != 1){
					tempo -= 1;
				}
				/*lcd_pos(1,0);
				char bufT2[10];
				sprintf(bufT2, "T Down: %d", tempo);
				lcd_puts2(bufT2);*/
			}
			if(getKey() == 13){
				//change pitch with *
				if(pitch != 3){
					pitch += 1;
					}else{
					pitch = 1;
				}
				avr_wait(1000);
				/*lcd_pos(1,8);
				char bufp[4];
				sprintf(bufp, "P:%d", pitch);
				lcd_puts2(bufp);*/
			}
			if(getKey() == 14){
				//change volume with 0
				if(volume != 3){
					volume += 1;
					}else{
					volume = 1;
				}
				avr_wait(3000);
			}
		}
		if(getKey() == 15){
			//pause or play with #
			lcd_clr();
			lcd_pos(1,0);
			if(play){
				play = 0;
				lcd_puts2("Paused");
			} else{
				play = 1;
				lcd_puts2("Play");
			}
		}
		avr_wait(1000);
		
		
	}
	return 0;
}