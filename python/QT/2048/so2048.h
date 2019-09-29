#include <stdio.h>
#include<stdio.h>
#include<time.h>

/* variables */
int bestScore = 0; 
int currentScore = 0; 
int fields[4][4];

/* methods */
void initGame(); //init the status of the game
void initPanel(); // clean the panel and generate the initial numbers
int randInt(); // generate an random Integer
