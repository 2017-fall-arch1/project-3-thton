/* Course : Computer Architecture Fall 2017
 * Professor : Dr. Eric Freudenthal
 * Assignment : Lab 3
 * Title : Game of Pong
 * Author : Toan Ton
 * Date : 12/5/2017
 */  
#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include <abCircle.h>
#include "music.h"
#include "buzzer.h"

#define GREEN_LED BIT6


AbRect paddle = {abRectGetBounds, abRectCheck, {20,5}}; /**< 20x5 rectangle */
AbRArrow rightArrow = {abRArrowGetBounds, abRArrowCheck, 30};

AbRectOutline fieldOutline = {	/* playing field */
  abRectOutlineGetBounds, abRectOutlineCheck,   
  {screenWidth/2 - 10, screenHeight/2 - 10}
};

Layer layer4 = {
  (AbShape *)&rightArrow,
  {(screenWidth/2), (screenHeight/2)}, /**< bit below & right of center*/
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  0,
};

Layer fieldLayer = {		/* playing field as a layer */
  (AbShape *) &fieldOutline,
  {screenWidth/2, screenHeight/2},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  0,
};

Layer layer3 = {
  (AbShape *)&circle4,         /* pong ball */
  {(screenWidth/2), (screenHeight/2)},   /* center */
  {0,0}, {0,0},
  COLOR_BLACK,
  &fieldLayer,
};

Layer layer1 = {		/**< Layer with a red paddle */
  (AbShape *)&paddle,
  {screenWidth/2, screenHeight-15}, /* buttom (player 1) */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_RED,
  &layer3,
};

Layer layer0 = {		/**< Layer with a blue paddle */
  (AbShape *)&paddle,
  {(screenWidth/2), 15}, /* top (player 2) */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLUE,
  &layer1,
};

/** Moving Layer
 *  Linked list of layer references
 *  Velocity represents one iteration of change (direction & magnitude)
 */
typedef struct MovLayer_s {
  Layer *layer;
  Vec2 velocity;
  struct MovLayer_s *next;
} MovLayer;

/* initial value of {0,0} will be overwritten */
MovLayer ml3 = { &layer3, {3,3}, 0 }; /**< not all layers move */
MovLayer ml1 = { &layer1, {3,0}, 0 }; //Red player bar 
MovLayer ml0 = { &layer0, {3,0}, 0 }; //Blue player bar

void movLayerDraw(MovLayer *movLayers, Layer *layers)
{
  int row, col;
  MovLayer *movLayer;

  and_sr(~8);			/**< disable interrupts (GIE off) */
  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Layer *l = movLayer->layer;
    l->posLast = l->pos;
    l->pos = l->posNext;
  }
  or_sr(8);			/**< disable interrupts (GIE on) */


  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Region bounds;
    layerGetBounds(movLayer->layer, &bounds);
    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1], 
		bounds.botRight.axes[0], bounds.botRight.axes[1]);
    for (row = bounds.topLeft.axes[1]; row <= bounds.botRight.axes[1]; row++) {
      for (col = bounds.topLeft.axes[0]; col <= bounds.botRight.axes[0]; col++) {
	Vec2 pixelPos = {col, row};
	u_int color = bgColor;
	Layer *probeLayer;
	for (probeLayer = layers; probeLayer; 
	     probeLayer = probeLayer->next) { /* probe all layers, in order */
	  if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {
	    color = probeLayer->color;
	    break; 
	  } /* if probe check */
	} // for checking all layers at col, row
	lcd_writeColor(color); 
      } // for col
    } // for row
  } // for moving layer being updated
}	  



//Region fence = {{10,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}}; /**< Create a fence region */

/** Advances a moving shape within a fence
 *  
 *  \param ml The moving shape to be advanced
 *  \param fence The region which will serve as a boundary for ml
 */
void mlAdvance(MovLayer *ml, Region *fence)
{
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;
  for (; ml; ml = ml->next) {
    vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);
    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
    for (axis = 0; axis < 2; axis ++) {
      if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||
	  (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {
	int velocity = ml->velocity.axes[axis] = -ml->velocity.axes[axis];
	newPos.axes[axis] += (2*velocity);
      }	/**< if outside of fence */
    } /**< for axis */
    ml->layer->posNext = newPos;
  } /**< for ml */
}

char p1Stats[6] = "P1:0";  /* Variables for score keeping and managing game */
char p2Stats[6] = "P2:0";
u_int scoreAt = 3;
char p1Score = 0;
char p2Score = 0;
char playGame = 0;
char gameOver = 0;

u_int bgColor = COLOR_BLACK;     /**< The background color */
int redrawScreen = 1;           /**< Boolean for whether screen needs to be redrawn */

Region fieldFence;		/**< fence around playing field  */
Region fencePaddle1;
Region fencePaddle2;

/*Printing the score of a player */
void printScore(char *scoreBoard, char width){
  drawString5x7(width,2, scoreBoard, COLOR_BLACK, COLOR_GREEN);
}

void resetPositions(MovLayer *ml, MovLayer *p1, MovLayer *p2){   /* resetting position of paddles and ball after each score  */
  Vec2 newPos;
  newPos.axes[0] = screenWidth/2;
  newPos.axes[1] = screenHeight/2;
  ml->layer->posNext = newPos;
  newPos.axes[1] = (screenHeight-15);
  p1->layer->posNext = newPos;
  newPos.axes[1] = (15);
  p2->layer->posNext = newPos;
}

void updateScore(int player){          /* function for updating the score for a player  */
  if(player == 0){
    p1Score++;
    p1Stats[scoreAt] = '0'+p1Score;
    printScore(p1Stats, 1);
  }
  else{
    p2Score++;
    p2Stats[scoreAt] = '0'+p2Score;
    printScore(p2Stats, 104);
  }
}

char game(MovLayer *ml, MovLayer *p1, MovLayer *p2, Region *fenceP1,Region *fenceP2, Region *fence)
{
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;

  /*collision between ball and paddles*/
  vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);
  abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
  if (((shapeBoundary.topLeft.axes[1] <= fenceP2->botRight.axes[1]) &&
       (shapeBoundary.topLeft.axes[0] > fenceP2->topLeft.axes[0]) &&
       (shapeBoundary.topLeft.axes[0] < fenceP2->botRight.axes[0])) ||
      ((shapeBoundary.botRight.axes[1] >= fenceP1->topLeft.axes[1]) &&
       (shapeBoundary.botRight.axes[0] > fenceP1->topLeft.axes[0]) &&
       (shapeBoundary.botRight.axes[0] < fenceP1->botRight.axes[0]))){
    int velocity = ml->velocity.axes[1] = -ml->velocity.axes[1];
    newPos.axes[1] += (2*velocity);
  }

  /* collisions between ball and vertical walls */
  if((shapeBoundary.topLeft.axes[0] <= fence->topLeft.axes[0]) ||
     (shapeBoundary.botRight.axes[0] >= fence->botRight.axes[0])){
    int velocity = ml->velocity.axes[0] = -ml->velocity.axes[0];
    newPos.axes[0] += (2*velocity);
  }

  /* collision between ball and horizontal wall (scoring) */
  if(shapeBoundary.topLeft.axes[1] < fence->topLeft.axes[1]){
    updateScore(0);
    //buzzer_set_note(1);
    return 1;
  }

  if(shapeBoundary.botRight.axes[1] > fence->botRight.axes[1]){
    updateScore(1);
    //buzzer_set_note(1);
    return 1;
  }

  ml->layer->posNext = newPos; //update posNext
  return 0;
}


/** Initializes everything, enables interrupts and green LED, 
 *  and handles the rendering for the screen
 */
void main()
{
  P1DIR |= GREEN_LED;		/**< Green led on when CPU on */		
  P1OUT |= GREEN_LED;

  configureClocks();
  lcd_init();
  shapeInit();

  layerInit(&layer0);
  layerDraw(&layer0);

  layerGetBounds(&fieldLayer, &fieldFence);

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */


  for(;;) { 
    while (!redrawScreen) { /**< Pause CPU if screen doesn't need updating */
      P1OUT &= ~GREEN_LED;    /**< Green led off witHo CPU */
      or_sr(0x10);	      /**< CPU OFF */
    }
    P1OUT |= GREEN_LED;       /**< Green led on when CPU on */
    redrawScreen = 0;
  }
}

/** Watchdog timer interrupt handler. 15 interrupts/sec */
void wdt_c_handler()
{
  static short count = 0;    /* variables for managing game */
  static short sound = 0;
  static char point = 0;
  static long wait = 0;
  static char increment = 0;
  u_char width = 60;
  
  P1OUT |= GREEN_LED;		      /**< Green LED on when cpu on */

  while(!playGame){
    drawString5x7(screenWidth/2-12,30, "PONG", COLOR_GOLD, COLOR_BLACK); //title
    drawString5x7(10,50,"S1: Red Left", COLOR_RED, COLOR_BLACK);  //instructions for the game
    drawString5x7(10,65,"S2: Red Right", COLOR_RED, COLOR_BLACK);
    drawString5x7(10,80,"S3: Blue Left", COLOR_BLUE, COLOR_BLACK);
    drawString5x7(10,95,"S4: Blue Right",COLOR_BLUE, COLOR_BLACK);
    drawString5x7(10,115,"Press to Play!", COLOR_YELLOW, COLOR_BLACK);
    if(++wait == 150){    //giving time for player to read instructions
      wait = 0;
      playGame = 1;
      bgColor = COLOR_GREEN;

      lcd_init();
      p2sw_init(15);
      buzzer_init();
      layerDraw(&layer0);

      drawString5x7(50,2, "Score", COLOR_BLACK, COLOR_GREEN);
      printScore(p1Stats, 1);
      printScore(p2Stats, 104);
    }
  }

  if(!gameOver)
    song(sound);
    //drawString5x7(screenWidth/2-20, screenHeight-8,"Playing", COLOR_RED, COLOR_GREEN);

  if(++sound > 225)
    sound = 0;
  
  if(count++ == 15){
    layerGetBounds(&layer1, &fencePaddle1);
    layerGetBounds(&layer0, &fencePaddle2);

    movLayerDraw(&ml3,&layer3); //moving ball

    point = game(&ml3, &ml1, &ml0, &fencePaddle1, &fencePaddle2, &fieldFence); //start game

    if(point){
      resetPositions(&ml3, &ml1, &ml0);  //reset positions after score
      movLayerDraw(&ml3,&layer3);
      movLayerDraw(&ml1,&layer1);
      movLayerDraw(&ml0,&layer0);
      if(((p1Score != 5) || (p2Score !=5)) && ((p1Score != 5) && (p2Score !=5))){
	drawChar5x7(screenWidth/2-2,50,'3', COLOR_BLACK,COLOR_GREEN);    //3 second countdown for players
	while(++wait < 1000000){}
	drawChar5x7(screenWidth/2-2,50,'2', COLOR_BLACK,COLOR_GREEN);
	while(++wait < 2000000){}
	drawChar5x7(screenWidth/2-2,50,'1', COLOR_BLACK,COLOR_GREEN);
	while(++wait < 3000000){}
	drawChar5x7(screenWidth/2-2,50,'1', COLOR_GREEN,COLOR_GREEN); //clear countdown
      }
      point = 0;
      wait = 0;
    }


    if(p1Score == 5 || p2Score == 5){     // win check for 5 rounds
      gameOver = 1;
      char *winner;
      (p1Score == 5)?(winner = "Red!"):(winner = "Blue!");
      bgColor = COLOR_GOLD;

      layerDraw(&layer0);
      and_sr(~8);
      buzzer_set_note(1);

      drawString5x7(screenWidth/2-25,50,"GAME OVER!",COLOR_RED,COLOR_GOLD);    //game over message
      drawString5x7(screenWidth/2-20,100,"WINNER",COLOR_BLACK,COLOR_GOLD);
      drawString5x7(screenWidth/2-16,115,winner,COLOR_BLACK,COLOR_GOLD);
      
      while(1){}
    }
    u_int switches = p2sw_read(), i;    //getting input from players with switches
    for(i=0; i<4; i++){
      if(!(switches & (1<<i))){
	if(i == 0){    //switch one makes red go left
	  ml1.velocity.axes[0] = -4;
	  movLayerDraw(&ml1,&layer1);
	  mlAdvance(&ml1, &fieldFence);
	  redrawScreen = 1;
	} 
	if(i == 1){   //switch two makes red go right
	  ml1.velocity.axes[0] = 4;
	  movLayerDraw(&ml1,&layer1);
	  mlAdvance(&ml1,&fieldFence);
	  redrawScreen = 1;
	}
	if(i == 2){   //switch three makes blue go left
	  ml0.velocity.axes[0] = -4;
	  movLayerDraw(&ml0,&layer0);
	  mlAdvance(&ml0,&fieldFence);
	  redrawScreen = 1;
	}
	if(i == 3){  //switch four makes blue go right
	  ml0.velocity.axes[0] = 4;
	  movLayerDraw(&ml0,&layer0);
	  mlAdvance(&ml0,&fieldFence);
	  redrawScreen = 1;
	}
      }
      count = 0;
    }
    P1OUT &= ~GREEN_LED;		    /**< Green LED off when cpu off */
  }
}
