#ifndef music_included
#define  music_included

void song(short sound);
void play(long note, long tempo);
void playlist(char song);
void play_c_scale();
void play_kh_theme();
void play_ff_fanfare();
void play_ff_chocobo();

#define QUARTER_NOTE 100
#define WHOLE_NOTE (QUARTER_NOTE*4)          /* time spent playing one note */
#define HALFDOT_NOTE (QUARTER_NOTE*5)/2
#define HALF_NOTE (QUARTER_NOTE*2)
#define QUARTERDOT_NOTE ((QUARTER_NOTE*3)/2) 
#define EIGHTHDOT_NOTE ((QUARTER_NOTE*3)/4)
#define EIGHTH_NOTE (QUARTER_NOTE/2)
#define SIXTEENTH_NOTE (QUARTER_NOTE/4)
#define THIRTY_SECOND_NOTE (QUARTER_NOTE/8)

#define WHOLE_REST 0X222e00          /* time spent in rest */
#define HALFDOT_REST 0x19a280
#define HALF_REST 0X111700
#define QUARTERDOT_REST 0Xcd140 
#define QUARTER_REST 0x88b80
#define EIGHTHDOT_REST 0x668a0
#define EIGHTH_REST 0x445c0
#define SIXTEENTH_REST 0x222e0
#define THIRTY_SECOND_REST 0x11170

/* 
   NOTES BY SEMITONE AND OCTAVE 
*/

#define D0_SHARP 6416
#define E0_FLAT 6416
#define E0 6046 
#define F0 5704
#define F0_SHARP 5380
#define G0_FLAT 5380
#define G0 5080
#define G0_SHARP 4796
#define A0_FLAT 4796
#define A0 4528
#define A0_SHARP 4272
#define B0_FLAT 4272
#define B0 4032

#define C1 3804
#define C1_SHARP 3592
#define D1_FLAT 3592
#define D1 3390
#define D1_SHARP 3198
#define E1_FLAT 3198
#define E1 3020
#define F1 2850
#define F1_SHARP 2690
#define G1_FLAT 2690
#define G1 2538
#define G1_SHARP 2394
#define A1_FLAT 2394
#define A1 2260
#define A1_SHARP 2134
#define B1_FLAT 2134
#define B1 2012

#define C2 1898
#define C2_SHARP 1794
#define D2_FLAT 1794
#define D2 1696
#define D2_SHARP 1600
#define E2_FLAT 1600
#define E2 1508
#define F2 1424
#define F2_SHARP 1346
#define G2_FLAT 1346
#define G2 1270
#define G2_SHARP 1198
#define A2_FLAT 1198
#define A2 1130
#define A2_SHARP 1866
#define B2_FLAT 1866
#define B2 1006

#define C3 950
#define C3_SHARP 896
#define D3_FLAT 896 
#define D3 846
#define D3_SHARP 800
#define E3_FLAT 800
#define E3 754
#define F3 712
#define F3_SHARP 672
#define G3_FLAT 672
#define G3 634
#define G3_SHARP 598
#define A3_FLAT 598
#define A3 564
#define A3_SHARP 532
#define B3_FLAT 532
#define B3 503


#endif
