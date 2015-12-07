#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "process.c"

typedef struct priorityQueue PriorityQueue, *PriorityQueuePointer;

struct priorityQueue {
  int capacity;
  int size;
  ProcessPointer *data;
}; // priorityQueue

PriorityQueuePointer createPriorityQueue( int maximumSize ) {
  PriorityQueuePointer pq = (PriorityQueuePointer) malloc(sizeof(PriorityQueue));
  pq->capacity = maximumSize;
  pq->size = 0;
  pq->data = (ProcessPointer *) malloc((1 + maximumSize) * sizeof(ProcessPointer));

  // int i;
  // for( i = 0; i < maximumSize; i++ ) {
  //   pq->data[i] = NULL;
  // } // for

  return pq;
} // createPriorityQueue( int )

bool isPriorityQueueEmpty( PriorityQueuePointer pq ) {
  return pq->size == 0;
} // isPriorityQueueEmpty( PriorityQueuePointer )

void rise( ProcessPointer data[], int i ) {
  int j = i/2;
  if( i > 1 && data[j]->serviceTime > data[i]->serviceTime ) {
    ProcessPointer temp = data[i];
    data[i] = data[j];
    data[j] = temp;

    rise( data, j );
  } // if
} // rise( int[], int )

void pqEnqueue( PriorityQueuePointer pq, ProcessPointer pp ) {
  if( pq->size < pq->capacity ) {
    int index = 1 + pq->size;
    pq->data[index] = pp;

    rise( pq->data, index );

    pq->size++;
  } // if
} // pqEnqueue( int )

void printPriorityQueue( PriorityQueuePointer pq ) {
  int i;
  for( i = 1; i <= pq->size; i++ ) {
    printProcess( pq->data[i] );
  } // for
  printf( "\n" );
} // printPriorityQueue( PriorityQueuePointer )

void fall( PriorityQueuePointer pq, int i ) {
  int j = 2 * i;
  int k = 2 * i + 1;
  if( k <= pq->size && pq->data[k]->serviceTime < pq->data[j]->serviceTime ) {
    j = k;
  } // if

  if( j <= pq->size && pq->data[i]->serviceTime > pq->data[j]->serviceTime ) {
    ProcessPointer temp = pq->data[i];
    pq->data[i] = pq->data[j];
    pq->data[j] = temp;

    fall( pq, j );
  } // if
} // fall( PriorityQueuePointer, int )

int pqDequeue( PriorityQueuePointer pq ) {
  if( pq->size > 0 ) {
    printPriorityQueue( pq );

    ProcessPointer result = pq->data[1];
    pq->data[1] = pq->data[pq->size];
    pq->data[pq->size] = NULL;
    pq->size--;

    fall( pq, 1 );

    return result;
  } // if
  else {
    return -99;
  } // else
} // pqEnqueue()

ProcessPointer pqPeek( PriorityQueuePointer pq ) {
  return pq->data[1];
} // peek( PriorityQueuePointer )

int main( int argc, char** charv ) {
  PriorityQueuePointer pq = createPriorityQueue( 12 );
  printf( "Is newly created income empty? %d\n\n", isPriorityQueueEmpty(pq) );


  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );
  pqEnqueue( pq, createProcess() );

  printPriorityQueue( pq );

  printf( "\n" );

  while( !isPriorityQueueEmpty(pq) ) {
    ProcessPointer pp = pqDequeue( pq );
    int n = pp->id;
    printf( "highest priority item = %d\n", n );
  } // while

  exit(0);
} // main( int, char** )
