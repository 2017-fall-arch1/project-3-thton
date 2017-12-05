#include <msp430.h>
#include <music.h>
#include <buzzer.h>

void song(short sound){
  unsigned short level = THIRTY_SECOND_NOTE;
  if(sound < level)
    buzzer_set_note(C2);
  level += THIRTY_SECOND_NOTE;

  if(sound >= level)
    buzzer_set_note(C2_SHARP);
  level += THIRTY_SECOND_NOTE;

  if(sound >= level)
    buzzer_set_note(D2);
  level += EIGHTH_NOTE;

  if(sound >= level)
    buzzer_set_note(B1);
  level += SIXTEENTH_NOTE;

  if(sound >= level)
    buzzer_set_note(G1);
  level += SIXTEENTH_NOTE;

  if(sound >= level)
    buzzer_set_note(E1);
  level += SIXTEENTH_NOTE;

  if(sound >= level)
    buzzer_set_note(D2);
  level += SIXTEENTH_NOTE;

  if(sound >= level)
    buzzer_set_note(B1);
  level += SIXTEENTH_NOTE;
  
  if(sound >= level)
    buzzer_set_note(G1);
  level += SIXTEENTH_NOTE;
}


/*
  Plays a tone and the time of a note 
*/
void play(long note, long tempo){
  long count = 0;
  buzzer_set_note(note);
  while(++count < tempo){}
}

/*
  Plays a chocobo theme song
*/
void play_ff_chocobo(){
  char rep = 0;
  long count = 0;
  
  /* 
     strophe 1 & 2 silent
    
     strophe 3 
  */
  buzzer_set_note(C2);
  while(++count < THIRTY_SECOND_NOTE){}
  count = 0; 
  buzzer_set_note(C2_SHARP);
  while(++count < THIRTY_SECOND_NOTE){}
  count = 0;
  buzzer_set_note(D2);
  while(++count < EIGHTH_NOTE){}
  count = 0;
  buzzer_set_note(B1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(G1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(E1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(D2);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(B1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(G1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  /* strophe 4*/
  buzzer_set_note(B1);
  while(++count < EIGHTH_NOTE){}
  count = 0;
  buzzer_set_note(G1);
  while(++count < EIGHTH_NOTE){}
  count = 0;
  buzzer_set_note(B1);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
  buzzer_set_note(A1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  
  /* strophe 5*/

  /* Repeats tone 2 times with spacing */
  while(rep < 2){
    buzzer_set_note(G1);
    while(++count < SIXTEENTH_NOTE){}
    count = 0;
    buzzer_set_note(0);
    rep++;
  }
  rep = 0;
  
  buzzer_set_note(A1);
  while(++count < THIRTY_SECOND_NOTE){}
  count = 0;
  buzzer_set_note(G1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(F1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(G1);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
  buzzer_set_note(F1);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;

  /* Repeats tone 2 times with spacing */
  while(rep < 2){
    buzzer_set_note(G1);
    while(++count < SIXTEENTH_NOTE){}
    count = 0;
    buzzer_set_note(0);
    rep++;
  }
  rep=0;
  
  count = 0;
  buzzer_set_note(B1);
  while(++count < THIRTY_SECOND_NOTE){}
  count = 0;
  buzzer_set_note(D2);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(E2);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(F2);
  while(++count < QUARTER_NOTE){}
  count = 0; 
}


/*
  Plays a specific song  
*/
void playlist(char song){

  switch(song){
  case 1:
    play_c_scale();
    break;
  case 2:
    play_kh_theme();  
    break;
  case 3:
    play_ff_fanfare();
    break;
  case 4:
    play_ff_chocobo();
    break;
  }
}

/*
  Plays a C major scale 
*/
void play_c_scale(){
  
  long count = 0;
  long tempo = QUARTER_NOTE;

  buzzer_set_note(C1);
  while(++count < tempo){}
  count = 0; 
  buzzer_set_note(D1);
  while(++count < tempo){}
  count = 0;
  buzzer_set_note(E1);
  while(++count < tempo){}
  count = 0;
  buzzer_set_note(F1);
  while(++count < tempo){}
  count = 0;
  buzzer_set_note(G1);
  while(++count < tempo){}
  count = 0;
  buzzer_set_note(A1);
  while(++count < tempo){}
  count = 0;
  buzzer_set_note(B1);
  while(++count < tempo){}
  count = 0;
  buzzer_set_note(C2);
  while(++count < tempo){}
}

/*
  Plays the kingdom hearts theme 
*/
void play_kh_theme(){  
  long count = 0;
  char rep = 0;

  /* Repeats melody 3 times with spacing */
  
  while(rep < 3){
    buzzer_set_note(G1);
    while(++count < EIGHTH_NOTE){}
    count = 0; 
    buzzer_set_note(D2);
    while(++count < QUARTER_NOTE){}
    count = 0;
    buzzer_set_note(C2);
    while(++count < EIGHTH_NOTE){}
    count = 0;
    buzzer_set_note(B1_FLAT);
    while(++count < SIXTEENTH_NOTE){}
    count = 0;
    buzzer_set_note(A1);
    while(++count < EIGHTHDOT_NOTE){}
    count = 0;
    buzzer_set_note(B1_FLAT);
    while(++count < QUARTER_NOTE){}
    count = 0;
    rep++;
  }
  
  rep = 0;

  /* Repeats tone 4 times with spacing */
  while(rep < 4){
    buzzer_set_note(F1);
    while(++count < EIGHTH_NOTE){}
    count = 0;
    buzzer_set_note(0);
    rep++;
  }
  
  buzzer_set_note(B1_FLAT);
  while(++count < EIGHTH_NOTE){}
  count = 0;
  buzzer_set_note(A1);
  while(++count < EIGHTH_NOTE){}
  count = 0;
  buzzer_set_note(B1_FLAT);
  while(++count < EIGHTH_NOTE){}
  count = 0;
  buzzer_set_note(E2_FLAT);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
  buzzer_set_note(D2);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;

  buzzer_set_note(B1_FLAT);
  while(++count < EIGHTH_NOTE){}
  count = 0;

  /* Repeats tone 2 times with spacing */
  while(rep < 2){
    buzzer_set_note(A1);
    while(++count < EIGHTHDOT_NOTE){}
    count = 0;
    rep++;
  }
  
  buzzer_set_note(B1_FLAT);
  while(++count < EIGHTH_NOTE){}
  count = 0;

  buzzer_set_note(F2);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;

  buzzer_set_note(E2_FLAT);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;

  buzzer_set_note(D2);
  while(++count < EIGHTH_NOTE){}
  count = 0;

  buzzer_set_note(C2);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;

  buzzer_set_note(D2);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;

  buzzer_set_note(E2_FLAT);
  while(++count < EIGHTH_NOTE){}
  count = 0;

  buzzer_set_note(D2);
  while(++count < QUARTERDOT_NOTE){}
  count = 0;

  buzzer_set_note(B1_FLAT);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  
  buzzer_set_note(E1_FLAT);
  while(++count < HALF_NOTE){}
  count = 0;

  buzzer_set_note(D2);
  while(++count < QUARTERDOT_NOTE){}
  count = 0;
  buzzer_set_note(E2_FLAT);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;

  buzzer_set_note(C2);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
  buzzer_set_note(B1_FLAT);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
  buzzer_set_note(A1);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
}

/*
  Plays final fantasy fanfare theme
*/
void play_ff_fanfare(){
  char rep = 0;
  long count = 0;

  /* Repeats tone 3 times with spacing */
  while(rep < 3){
    buzzer_set_note(C2);
    while(++count < SIXTEENTH_NOTE){}
    count = 0;
    buzzer_set_note(0);
    rep++;
  }
  
  buzzer_set_note(C2);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
  buzzer_set_note(A1_FLAT);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
  buzzer_set_note(B1_FLAT);
  while(++count < EIGHTHDOT_NOTE){}
  count = 0;
  buzzer_set_note(C2);
  while(++count < EIGHTH_NOTE){}
  count = 0;
  buzzer_set_note(B1_FLAT);
  while(++count < SIXTEENTH_NOTE){}
  count = 0;
  buzzer_set_note(C2);
  while(++count < QUARTERDOT_NOTE){}
  count = 0;
}

