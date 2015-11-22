
// schedules.c
// Norbert Wiener
// CSC311 Systems Software
// 23 November 2015


// An illustration of several features
// of the C programming language.
//   1) preprocessor directives (#include and #define)
//   2) header files (stdio.h, stdlib.h, time.h, math.h)
//   3) typedefs
//   4) structs
//   5) library functions (malloc(), srand(), rand(), log())
//   6) casts 
//   7) pointers

#include <stdio.h>
#include <stdlib.h>

// define a node in a linked list
// that describes a process (a task)
// this description includes:
//   1) the time required to complete the process
//   2) the time until the next process joins the queue

int main( int argc, char **argv ) {

  // Seed the random number generator
  // with the time measured in seconds.
  // "time_t" is a just another name for
  // a long (64 bit) integer.

  // NULL is a constant defined for us.
  // (It is zero.)

  // Must declare counter before beginning loop!

    // malloc() is the function for "memory allocation"
    // sizeof is an operator that tells us how many bytes
    // we'll need to store an object of a given type.
    // malloc() returns a general kind of pointer (void *)
    // so we must cast it to remind the compiler to what 
    // kind of object we are pointing.

    // draw a random number from an exponential distribution
    // with a specified mean

    // draw a random number from an exponential distribution
    // with a specified mean
    
    // add this process to the list of processes
    // (this is the "linking" part of the linked list)

  // traverse the list.
  // begin at the last element added to the list
  // and end with the first element we added to the list.

  printf( "Hello from schedules!\n" );

  exit(0);  
} // main( int, char** )

