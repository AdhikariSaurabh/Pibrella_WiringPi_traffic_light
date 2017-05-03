/*
 ***********************************************************************
 *    Program   : timer.h
 *    Function  : Run for specified time / Time in milliseconds
 *    Version   : Version_1.0
 ***********************************************************************
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>

struct timeval timeout;

int timer (int seconds, int milliseconds)
{
	int n;
	fd_set input;

	/* Initialize the input set */
	FD_ZERO(&input);
	FD_SET(STDIN_FILENO, &input);   // use stdin file descriptor

	/* Initialize the timeout structure */
	//timeout.tv_sec = seconds;        // Using only one of the arguments in traffic.c program
	timeout.tv_usec = seconds*1000;    // The amount of time provide by user in seconds will be multiplied by 1000 and then converted into microsecond to get the delay

	/* Do the select, will typically sleep based on mask returned by poll method, and trigger again when queue wakeup */ 
	n = select(FD_SETSIZE, &input, NULL, NULL, &timeout);

	/* See if there was an error */
	if (n < 0)
		perror("Timeout failed");
	else{
		if (n == 0)
		 puts("");                          //  In the traffic.c program we are not dispaying anything in case of timeout
		else
			printf("Key pressed - Timeout terminated\n");
	}

	return 0;
}
