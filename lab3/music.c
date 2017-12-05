#include <msp430.h>
#include "music.h"
#include "buzzer.h"

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


