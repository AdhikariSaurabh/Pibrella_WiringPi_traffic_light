/*

 ***********************************************************************
 *    Program	: traffic.c
 *    Function	: Traffic Lights system with event driven
 *    Version	: Version_1.0
 *    Openess	: Can add new led & ledMap [NUM_LEDS]
 *    header	: Pibrella.h, wiringPi.h & timer.h
 ***********************************************************************

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <wiringPi.h>
#include "pibrella.h"
#include "timer.h"

#ifndef	TRUE
#define	TRUE	(1==1)
#define	FALSE	(1==2)
#endif

#define	DEBUG			1&&

#define	NUM_LEDS	 	7
#define BUZZER                  1
#define COUNT                   5

/**************************   Map the LEDs to the hardware pins************/ 
const int ledMap [NUM_LEDS] = {
	PIBRELLA_OUT_3,
	PIBRELLA_OUT_2,
	PIBRELLA_OUT_1,
	PIBRELLA_OUT_0,
	PIBRELLA_GREEN,
	PIBRELLA_YELLOW,
	PIBRELLA_RED,
} ;



/******************* FUNCTION DECLARATION ******************************/
void stayingreen (void);
void stayinyellow (void);




 /* ************************************************************************ *      setup
 *	Program the GPIO correctly and initialise the lamps
 ****************************************************************************/

void setup (void)

{
	wiringPiSetup () ;      //Basic Wiring Pi setup
	pibrellaSetup () ;	//Basic Pibrella Setup


}


/*
 *************************************************************************** *      introLeds
 *	To start with all the LEDS will glow for 1 sec 
 ****************************************************************************/

void introLeds (void)
{
	DEBUG printf("-------->all the leds glow for 1 sec<--------\n");
        const int i;
        

	// Flashing once
         
              
		digitalWrite (ledMap [4], 1) ;
                digitalWrite (ledMap [5], 1) ;
                digitalWrite (ledMap [6], 1) ;
                pwmWrite (BUZZER, 25) ;    /* PWM buzzer On */
		timer (500,0) ;
                pwmWrite (BUZZER, 0) ;       /* PWM buzzer Off */
		digitalWrite (ledMap [4], 0) ;
                digitalWrite (ledMap [5], 0) ;
                digitalWrite (ledMap [6], 0) ;
                timer (500,0) ;
	
}

/*
 *************************************************************************** *      StayinRed
 * Red LED should Keep on Glow until the button is pressed 
 * and once button is pressed red led should glow for 2 sec 
 * and then change its state to green
 ****************************************************************************/

void stayinred (void)
{

	DEBUG printf ("--------->Red Led glow<-----------\n") ;
        DEBUG printf ("----> Please Press the Push Button  <-----\n"); 
	// Glow In same until there is interrupt

	for (;;){
		digitalWrite (ledMap [6], 1) ;
		if (digitalRead (PIBRELLA_BUTTON) == HIGH){
			//Change to green
                timer(2000,0);            // for 2 seconds to remain in red
           digitalWrite (ledMap [6], 0) ;  // RED Led off if button pressed 
			stayingreen () ;
		}
	}
}

/*
 *************************************************************************** *      StayinGreen
 *	Green LED Glow for 5 seconds & blink for 1HZ for 5 seconds & blink   *      for 2 HZ for 5 seconds
 ****************************************************************************/

void stayingreen (void)
{

	int i;
     DEBUG printf ("--------> Green Led Signal <-----------\n") ;
     DEBUG printf ("(@....@)Pedestrians u can start crossing (@....@)\n"); 
     digitalWrite (ledMap[4],1);
	timer (5000, 0);
	digitalWrite (ledMap[4],0);
	delay(100);

	if (digitalRead (PIBRELLA_BUTTON) == HIGH){ /* If Big Red button pressed no action */
		//do_nothing;
	}
        
                DEBUG printf("---> Start Glowing @ 1Hz<---\n");
	for(i=1;i<=COUNT;i++){
             //   DEBUG printf("Inside Timer1\n");
    
		digitalWrite (ledMap[4],1);
		pwmWrite (BUZZER, 25) ;	/* PWM buzzer On */
                timer(500,0);
		pwmWrite (BUZZER, 0) ;	/* PWM buzzer Off */
		digitalWrite (ledMap[4],0);
		timer(500,0);
                DEBUG printf("%d\n",i);
                if(i==COUNT){
                DEBUG printf("---> Start Glowing @ 2Hz<----\n");
                } 
        }

	for(i=1;i<=(COUNT*2);i++){
               
                digitalWrite (ledMap[4],1);
		pwmWrite    (BUZZER, 25) ;	/* PWM buzzer On */
                timer(250,0);
		pwmWrite    (BUZZER, 0);	/* PWM buzzer Off */
                digitalWrite (ledMap[4],0);
		timer(250,0);
                DEBUG printf("%d\n",i);
               
        }

	stayinyellow();
}
/*
 *************************************************************************** * StayinYellow
 * Yellow LED Glow & simultaneously the buzzer should ring for 5 sec and 
 *  change to Red LED
 ****************************************************************************/

void stayinyellow (void)
{

	DEBUG printf("-------> Yellow light Signal<--------\n") ;

	digitalWrite (ledMap [5], 1);  /* SwitchOn yellow LED */
	pwmWrite    (BUZZER, 25) ;     /* PWM buzzer On */
	timer (2000, 0);               // in yellow for 2 seconds 
	pwmWrite    (BUZZER, 0) ;      /* PWM buzzer Off */
	digitalWrite (ledMap [5], 0);  /* Switchoff yellow LED */

	if (digitalRead (PIBRELLA_BUTTON) == HIGH){		
       /* If Big Red button pressed no action */
		//do_nothing;
	}
	stayinred();
}

/*
 *************************************************************************** *The main program
 ****************************************************************************/

int main (void)
{



       setup() ;	//Initial board setup setup wiring pi & Pibrella
      
       
       introLeds () ;	//Glow all LED @ once for 1 seconds


	//Stay in Red Initially
	for (;;)
        {
            
		stayinred();
	}

	return 0 ;
}
