/*
 * Implementation of FIFO and LRU page replacement algorithm
 * Info:
 * Alan Ta
 * 819357091
 * cssc2363
 * CS570 Summer
 * Program 5: FIFO and LRU Page Replacement Simulator
 * Due: 08/090/2020
*/


#include "vmalgorithm.h"
#include <time.h>

/* Generate an access pattern
 * Example: 3, 2, 2, 1, 1  indicates the page 3, 2, 2, 1, 1 in order
 */

// An array for LRU algorithm. Used to create a LRU Clock and store tick values
int tempArray[1000];

void generateAccessPattern()
{
    int i;
    srand(time(0));
    accessPattern = (int *)malloc( sizeof(int) * AccessPatternLength);
    printf("The randomized Access Pattern: ");
    for(i=0; i< AccessPatternLength; i++)
    {
        accessPattern[i] = rand() % ReferenceSZ;
        printf("%d ", accessPattern[i]);
    }
    printf("\n");
}

/*
 * Initialize the parameters of simulated memory
 */
void initializePageFrame()
{
    int i;
    memory.PageFrameList = (int *)malloc( sizeof(int)* FrameNR );    // dynamic allocated FrameNR frames to be used in memory
    memory.nextToReplaced =0;          // indicate the new frame to be replaced as 0
    for(i=0; i< FrameNR; i++)
    {
        memory.PageFrameList[i] = -1;  // initialization to -1 indicating all frames are unused
    }

}

// Print the pages loaded in memory
void printPageFrame()
{
    int i;
    for(i=0; i< FrameNR; i++)
    {
        printf("%2d ",memory.PageFrameList[i]);
    }
    printf("\n");
}


/*
 *  Print the access pattern in order
 */
void printAccessPattern()
{
    int i;
    printf("The Same Access Pattern: ");
    for(i=0; i< AccessPatternLength; i++)
    {
        printf("%d ", accessPattern[i]);
    }
    printf("\n");

}


/*
 * Return: number of the page fault using FIFO page replacement algorithm
 */
int FIFO()
{
    int pageFaults = 0;
    int mismatch = 0;
    memory.nextToReplaced = 0;
    int n = 0, m = 0;

    for(m; m < AccessPatternLength; m++){ // Checks the values in the accessPattern
        for(n = 0; n < FrameNR; n++) { // Given one accessPattern value, check if the value exist in the Frame
            if (accessPattern[m] != memory.PageFrameList[n]) {
                mismatch++;
            }
            else if(accessPattern[m] == memory.PageFrameList[n]){
                mismatch--;
            }
        }
        if(mismatch == FrameNR){ // If the value isnt in the frame, page fault
            pageFaults++;
            if(memory.nextToReplaced == (FrameNR)){ // Resets the index of the frame back to 0/start
                memory.nextToReplaced = 0;
            }
            memory.PageFrameList[memory.nextToReplaced] = accessPattern[m]; // Inserts the value into the frame index
            memory.nextToReplaced = memory.nextToReplaced + 1; // Increments to the next index
        }
        mismatch = 0;
        printPageFrame();
    }
    return pageFaults;
}


/*
 * Return: number of the page fault using LRU page replacement algorithm
 */

int LRU()
{
    int pageFaults = 0;
    int mismatch = 0;
    int mismatchFrame = 0;
    memory.nextToReplaced = 0;
    int n = 0, m = 0, k = 0;

    for(m; m < AccessPatternLength; m++){ // Checks the values in the accessPattern
        for(n = 0; n < FrameNR; n++) { // Given one accessPattern value, check if the value exist in the Frame
            if (accessPattern[m] != memory.PageFrameList[n]) {
                mismatch++;
            }
            else if(accessPattern[m] == memory.PageFrameList[n]){
                mismatch--;
                mismatchFrame = n; // Saves the index value of the matching value
            }
        }
        lruClock(); // ticks the frame clock
        if(mismatch == FrameNR){ // If the value isnt in the frame, page fault
            pageFaults++;
            memory.PageFrameList[memory.nextToReplaced] = accessPattern[m];
            tempArray[memory.nextToReplaced] = 0; // zeros out the tick value for that index
            memory.nextToReplaced = LRUIndex(); // finds the next biggest tick value index
        }
        // The value exist in the frame, zero it out and recalculate the next biggest tick value index
        if(mismatch != FrameNR){
            tempArray[mismatchFrame] = 0;
            memory.nextToReplaced = LRUIndex();
        }
        mismatch = 0;
        printPageFrame();
    }
    return pageFaults;
}

// A clock that increments the values of the number of frames given
void lruClock(){
    int k = 0;
    for(k; k < FrameNR; k++){
        tempArray[k]++;
    }

}

// Finds the largest tick value index in the array
int LRUIndex(){
    int l = 0;
    int leastUsed = tempArray[0];
    int index = 0;
    for(l = 1; l < FrameNR; l++){
        if(tempArray[l] > leastUsed){
            leastUsed = tempArray[l];
            index = l;
        }
    }
    return index;
}

