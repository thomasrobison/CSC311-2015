#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "priorityQueue.c"
#include "process.c"
#include "processQueue.c"
#include "statistics.c"
#include "processPriorityQueue.c"

#define DEBUG false

// This is that start of a program to simulate the 
// first-come/first-served scheduling of processes 
// for uninterrupted execution in a CPU 
// (or customers in a bank who line up in
// front of a teller's window).

// There are two principle parameters in this
// simulation: MEAN_SERVICE_TIME and MEAN_INTERARRIVAL_TIME.
// The relationship between these two parameters determines
// the performance of the system. If processes (customers)
// arrive faster than they can be served, the length of
// the queue (waiting line) will grow and grow.

// Create a queue and fill it with a specified
// number of processes.
QueuePointer buildQueue( int numberOfProcesses ) {
  seedRandomNumberGenerator();

  QueuePointer qp = createQueue();

  if(DEBUG) {
    printQueue(qp);
  }

  double elapsedTime = 0.0;
  int i;
  for( i = 0; i < numberOfProcesses; i++ ) {
    ProcessPointer pp = createProcess();
    elapsedTime += pp->interarrivalTime;
    pp->arrivalTime = elapsedTime;
    enqueue( qp, pp );
    if( DEBUG ) {
      printQueue(qp);
    }
  } // for

  return qp;
} // buildQueue( int )

// Print a complete description of the 
// process referenced in each element (node) of the queue.
// The complete description includes id, service time,
// interarrival time, arrival time, time at which
// service begins, and time at which service is completed.
void printProcessesInQueue( QueuePointer qp ) {
  NodePointer np = qp->pointerToHead;
  printf("\t\tService | Interarrival | Arrival | Start | End \n");
  while( np != NULL ) {
    printProcess( np->processPointer );
    np = np->pointerToPrevNode;
  } // while
} // printProcessInQueue( QueuePointer )

// Verify that the elements of the doubly-linked
// list are correctly linked.
void testQueue( int numberOfProcesses ) {
  printf( "\n\nBegin adding elements to the queue.\n\n" );
  QueuePointer qp = buildQueue(numberOfProcesses);

  computeStartStopTimes(qp);

  printf( "\n" );
  printProcessesInQueue( qp );

  printf( "\nBegin removing elements from the queue.\n\n" );
  printQueue( qp );

  while( !isQueueEmpty( qp ) ) {
    ProcessPointer pp = dequeue( qp );
    printQueue( qp );
    free( pp );
  } // while
} // testQueue( int )

ProcessPointer findAvailable(PriorityQueuePointer pq, double time) {
  ProcessPointer pp = pqPeek(pq);
  if(pp->arrivalTime < time) {
    pp = pqDequeue(pq);
  } else {
    ProcessPointer temp = pqDequeue(pq);
    pp = findAvailable(pq, time);
    pqEnqueue(pq, temp);
    if(pp->arrivalTime > time) {
      pqEnqueue(pq, pp);
    }
  }
  return pp;
}

void testPriorityQueue(QueuePointer before, QueuePointer after) {
  PriorityQueuePointer during = createPriorityQueue(before->length);
  double elapsedTime = 0.0;
  while(!isQueueEmpty(before)) {
    ProcessPointer pp = dequeue(before);
    pqEnqueue(during, pp);
    // if(isQueueEmpty(after)) {
    //   elapsedTime += pp->interarrivalTime + pp->serviceTime;
    //   enqueue(after, pp);
    // }
    // else {
    //   pqEnqueue(during, pp);
    // }
  }

  // QueuePointer temp = createQueue(during->capacity);
  // while(!isPriorityQueueEmpty(during)) {
  //   ProcessPointer pp = pqPeek(during);
  //   if(pp->arrivalTime < elapsedTime){
  //     pp = pqDequeue(during);
  //   }
  //   else {
  //     while(true) {
  //       pp = pqDequeue(during);
  //       if(pp->arrivalTime < elapsedTime){
  //         break;
  //       }
  //       else {
  //         enqueue(temp, pp);
  //       }
  //     }
  //     while(!isQueueEmpty(temp)){
  //       ProcessPointer p = dequeue(temp);
  //       pqEnqueue(during, p);
  //     }
  //     // pp = findAvailable(during, elapsedTime);
  //   }

    while(!isPriorityQueueEmpty(during)) {
      ProcessPointer pp = pqDequeue(during);
      pp->arrivalTime = elapsedTime + pp->interarrivalTime;
      elapsedTime += pp->serviceTime + pp->interarrivalTime;
      enqueue(after, pp);
    }
  }


PriorityQueuePointer buildPriorityQueue( int numberOfProcesses ) {
  seedRandomNumberGenerator();

  PriorityQueuePointer pqp = createPriorityQueue(numberOfProcesses);

  double elapsedTime = 0.0;
  int i;
  for( i = 0; i < numberOfProcesses; i++ ) {
    ProcessPointer pp = createProcess();
    elapsedTime += pp->interarrivalTime;
    pp->arrivalTime = elapsedTime;
  } // for

  return pqp;
} // buildQueue( int )  

// void sortQueue(QueuePointer qp, sortedQueue* sq) {
//   int queueLength = qp->length;

// }

void printStatistics(QueuePointer qp) {
  double meanTime = computeMeanServiceTime(qp);
  printf("\nMean Service Time: %8.4f", meanTime);

  double maxTime = computeMaxServiceTime(qp);
  printf("\nMax Service Time: %8.4f", maxTime);

  double stdDev = computeStandardDeviation(qp, meanTime);
  printf("\nService Time Variance: %8.4f\n", stdDev);

  //printHistogram(qp);
}

int main( int argc, char** argv ) {
  if (argc < 2) {
    printf("Please specify a number of processes.\n");
    exit(1);
  }
  int n = atoi(argv[1]);
  QueuePointer before = buildQueue(n);
  QueuePointer after = createQueue(n);


  printf("BEFORE:\n");
  printProcessesInQueue(before);
  testPriorityQueue(before, after);
  computeStartStopTimes(after);
  printf("\nAFTER\n");
  printProcessesInQueue(after);
  printStatistics(after);

  exit(0);
} //  main( int, char** )
