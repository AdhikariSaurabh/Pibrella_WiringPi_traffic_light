/*
 ***********************************************************************
 *    Program   : pibrella.h
 *    Function  : Hardware PIN Init/ definitions for Pibrella
 *    Version   : Version_1.0
 *    Openess   : Can add new led and define PIN for it
 ***********************************************************************
 */

// The 3 big LEDs

#define	PIBRELLA_RED		 2
#define	PIBRELLA_YELLOW		 0
#define	PIBRELLA_GREEN		 7

// The big red button

#define	PIBRELLA_BUTTON		14

// PWM/Tone output

#define	PIBRELLA_SQUAWK		 1

// The 4 inputs:

#define	PIBRELLA_IN_0		13
#define	PIBRELLA_IN_1		11
#define	PIBRELLA_IN_2		10
#define	PIBRELLA_IN_3		12

// The 4 outputs:

#define	PIBRELLA_OUT_0		 3
#define	PIBRELLA_OUT_1		 4
#define	PIBRELLA_OUT_2		 5
#define	PIBRELLA_OUT_3		 6

// Same, using the Pibrella board labels:

#define	PIBRELLA_IN_A		13
#define	PIBRELLA_IN_B		11
#define	PIBRELLA_IN_C		10
#define	PIBRELLA_IN_D		12

#define	PIBRELLA_OUT_E		 3
#define	PIBRELLA_OUT_F		 4
#define	PIBRELLA_OUT_G		 5
#define	PIBRELLA_OUT_H		 6


/*
 * playTone:
 *	Output the given frequency on the Pi's PWM pin
 *********************************************************************************
 */

static void playTone (int freq)
{
  int range ;

  if (freq == 0)
    pwmWrite (PIBRELLA_SQUAWK, 0) ;		// Off
  else
  {
    range = 600000 / freq ;
    pwmSetRange (range) ;
    pwmWrite    (PIBRELLA_SQUAWK, freq / 2) ;
  }
}


/*
 * pibrellaSetup:
 *	Initialise the Pi's GPIO for the Pibrella board
 *********************************************************************************
 */

void pibrellaSetup (void)
{
  pinMode (PIBRELLA_RED,	OUTPUT) ;
  pinMode (PIBRELLA_YELLOW,	OUTPUT) ;
  pinMode (PIBRELLA_GREEN,	OUTPUT) ;

  pinMode (PIBRELLA_BUTTON,	INPUT) ;

  pinMode (PIBRELLA_IN_0,	INPUT) ;
  pinMode (PIBRELLA_IN_1,	INPUT) ;
  pinMode (PIBRELLA_IN_2,	INPUT) ;
  pinMode (PIBRELLA_IN_3,	INPUT) ;

  pinMode (PIBRELLA_OUT_0,	OUTPUT) ;
  pinMode (PIBRELLA_OUT_1,	OUTPUT) ;
  pinMode (PIBRELLA_OUT_2,	OUTPUT) ;
  pinMode (PIBRELLA_OUT_3,	OUTPUT) ;

  digitalWrite (PIBRELLA_RED,    0) ;
  digitalWrite (PIBRELLA_YELLOW, 0) ;
  digitalWrite (PIBRELLA_GREEN,  0) ;

  digitalWrite (PIBRELLA_OUT_0,  0) ;
  digitalWrite (PIBRELLA_OUT_1,  0) ;
  digitalWrite (PIBRELLA_OUT_2,  0) ;
  digitalWrite (PIBRELLA_OUT_3,  0) ;

  pullUpDnControl (PIBRELLA_BUTTON, PUD_DOWN) ;
  pullUpDnControl (PIBRELLA_IN_0,   PUD_DOWN) ;
  pullUpDnControl (PIBRELLA_IN_1,   PUD_DOWN) ;
  pullUpDnControl (PIBRELLA_IN_2,   PUD_DOWN) ;
  pullUpDnControl (PIBRELLA_IN_3,   PUD_DOWN) ;

// Setup the PWM output to make the buzzer play tones

  pinMode    (PIBRELLA_SQUAWK, PWM_OUTPUT) ;
  pwmSetMode (PWM_MODE_MS) ;
  playTone   (0) ;
}


