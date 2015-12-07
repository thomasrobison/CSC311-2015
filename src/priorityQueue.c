#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct priorityQueue PriorityQueue, *PriorityQueuePointer;

struct priorityQueue {
  int capacity;
  int size;
  double *data;
}; // priorityQueue

PriorityQueuePointer createPriorityQueue( int maximumSize ) {
  PriorityQueuePointer pq = (PriorityQueuePointer) malloc(sizeof(PriorityQueue));
  pq->capacity = maximumSize;
  pq->size = 0;
  pq->data = (double *) malloc((1 + maximumSize) * sizeof(double));

  int i;
  for( i = 0; i < maximumSize; i++ ) {
    pq->data[i] = 0.0;
  } // for

  return pq;
} // createPriorityQueue( int )

bool isPriorityQueueEmpty( PriorityQueuePointer pq ) {
  return pq->size == 0;
} // isPriorityQueueEmpty( PriorityQueuePointer )

void rise( double data[], int i ) {
  int j = i/2;
  if( i > 1 && data[j] > data[i] ) {
    double temp = data[i];
    data[i] = data[j];
    data[j] = temp;

    rise( data, j );
  } // if
} // rise( int[], int )

void pqEnqueue( PriorityQueuePointer pq, double n ) {
  if( pq->size < pq->capacity ) {
    int index = 1 + pq->size;
    pq->data[index] = n;

    rise( pq->data, index );

    pq->size++;
  } // if
} // pqEnqueue( int )

void printPriorityQueue( PriorityQueuePointer pq ) {
  int i;
  for( i = 1; i <= pq->size; i++ ) {
    printf( "%8.4f ", pq->data[i] );
  } // for
  printf( "\n" );
} // printPriorityQueue( PriorityQueuePointer )

void fall( PriorityQueuePointer pq, int i ) {
  int j = 2 * i;
  int k = 2 * i + 1;
  if( k <= pq->size && pq->data[k] < pq->data[j] ) {
    j = k;
  } // if

  if( j <= pq->size && pq->data[i] > pq->data[j] ) {
    double temp = pq->data[i];
    pq->data[i] = pq->data[j];
    pq->data[j] = temp;

    fall( pq, j );
  } // if
} // fall( PriorityQueuePointer, int )

int pqDequeue( PriorityQueuePointer pq ) {
  if( pq->size > 0 ) {
    printPriorityQueue( pq );

    double result = pq->data[1];
    pq->data[1] = pq->data[pq->size];
    pq->data[pq->size] = 0.0;
    pq->size--;

    fall( pq, 1 );

    return result;
  } // if
  else {
    return -99;
  } // else
} // pqEnqueue()

double pqPeek( PriorityQueuePointer pq ) {
  return pq->data[1];
} // peek( PriorityQueuePointer )

// int main( int argc, char** charv ) {
//   PriorityQueuePointer pq = createPriorityQueue( 12 );
//   printf( "Is newly created income empty? %d\n\n", isPriorityQueueEmpty(pq) );


//   pqEnqueue( pq, 5.0 );
//   pqEnqueue( pq, 2.0 );
//   pqEnqueue( pq, 3.0 );
//   pqEnqueue( pq, 1.0 );
//   pqEnqueue( pq, 4.0 );

//   printPriorityQueue( pq );

//   printf( "\n" );

//   while( !isPriorityQueueEmpty(pq) ) {
//     double n = pqDequeue( pq );
//     printf( "highest priority item = %8.4f\n", n );
//   } // while

//   exit(0);
// } // main( int, char** )
