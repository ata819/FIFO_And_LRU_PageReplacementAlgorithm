/*
 * Info:
 * Alan Ta
 * 819357091
 * cssc2363
 * CS570 Summer
 * Program 5: FIFO and LRU Page Replacement Simulator
 * Due: 08/090/2020
 */
/********************************************
 * Page Replacement Simulation: header file
 *******************************************/

#include <stdio.h>
#include <stdlib.h>


/**************************************
 * The parameters of memory and disk pages
 *
 * PageFrameList: The dynamically-allocated array representing memory pages
 * FrameNR: the number of page frames in memory
 * nextToReplaced: Point to the next page to be replaced
 *
 * accessPattern: The sequence of the demanding pages
 * AccessPatternLength: The length of the randomized access pattern
 * ReferenceSZ: the page number range of the access pattern
 *
 */

#define AccessPatternLength 20  // total number of memory access

typedef struct
{
    int *PageFrameList;     // The dynamically-allocated array representing memory pages
    int nextToReplaced;	      // point to the next frame to be replaced
}PageFrame;



/*
 * The following global variables will be used in the program, please understand each of them before starting your coding ...
 */


int *accessPattern;        // memory access pattern, for example: 4 2 2 0 1   means will access the page 4, 2, 2, 0 and 1 one by one in order


int ReferenceSZ;           // range of pages to be accssed
int FrameNR;               // the number of page frames in memory

PageFrame memory;          // representing the memory

// Generates a random set of values ranging between 0 and the ReferenceSZ with a fixed size of 20
void generateAccessPattern();

// Initializes the page frame and set all the frame values to -1
void initializePageFrame();

// Prints out the values in the Page Frame
void printPageFrame();

// Prints the access patterns that were generated in generatedAccessPattern or the hard coded
void printAccessPattern();

/* Algorithm Functions */

// A function that performs the First In - First Out algorithm. It applies this algorithm for page replacement
int FIFO();

// A function that performs the Least Recently Used algorithm. It applies this algorithm for page replacement
int LRU();

// A ticker clock that increments the values of an array of size FrameNR
// Used to keep track of how long a page has been in the frame. Higher ticks = longer time spent in
void lruClock();

// Goes through a temp array of size FrameNR and finds the biggest tick value index
int LRUIndex();