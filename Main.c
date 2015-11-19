/*
 * CS 5372 - Design and Specification of Real-Time Systems
 * Instructor: Salamah I. Salamah, Ph. D.
 * 
 * Final Project: Movement Sensor
 * Presentation due: 11/30/2015
 * 
 * Team members:
 * Upama Rahman
 * Chris Mckye
 * Julio Corral
 * Ernesto Vazquez
 */
#include <vxWorks.h>
#include <stdio.h>
#include <taskLib.h>
#include <sysLib.h>
#include <msgQLib.h>
#include <semLib.h>
#include <stdio.h>

/* Constants */
#define MSG_Q_MAX_LENGTH 20
#define MSG_SIZE 10
/* elements needed */
FILE *shared_file;
MSG_Q_ID msgQ;
SEM_ID mutex;
int sensor_task, log_task, print_task; 
FILE *fr;

void sensor(){
	
}

void logToFile(){
	
}

void printtxtlog(){
if(semMutex){
		semTake(semMutex,WAIT_FOREVER);
		int n;
		   long elapsed_seconds;
		   char line[80];
		   clrscr();

		   fr = fopen ("elapsed.dta", "rt");  /* open the file for reading */
		   /* elapsed.dta is the name of the file */
		   /* "rt" means open the file for reading text */
		   while(fgets(line, 80, fr) != NULL)
		      {
		   	 /* get a line, up to 80 chars from fr.  done if NULL */
		   	 sscanf (line, "%ld", &elapsed_seconds);
		   	 /* convert the string to a long int */
		   	 printf ("%ld\n", elapsed_seconds);
		      }
		      fclose(fr);  /* close the file prior to exiting the routine */
	   semGive(semMutex);
	   taskDelay(1000); // delay it enought time so new content can be written and after written, release the semaphore.
	  }
	
}

void Init(){
	/* Initialize elements */
	mutex = semMCreate(SEM_Q_FIFO);
	msgQ = msgQCreate(MSG_Q_MAX_LENGTH, MSG_SIZE, MSG_Q_FIFO);
	
	/* create tasks */
	sensor_task = taskSpawn("sensor", 110, 0x100, 2000, (FUNCPTR)sensor, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	log_task = taskSpawn("log", 110, 0x100, 2000, (FUNCPTR)logToFile, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	print_task = taskSpawn("print", 110, 0x100, 2000, (FUNCPTR)printtxtlog, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

int main(void){
	Init();
	// watchdog executes ...
	return 0;
}
