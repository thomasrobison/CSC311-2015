double computeMeanServiceTime(QueuePointer qp) {
  NodePointer cnp = qp->pointerToHead;
  double serviceSum = 0.0;
  while(cnp != NULL){
    ProcessPointer cpp = dequeue(qp);
    serviceSum += cpp->serviceTime; 
    cnp = cnp->pointerToPrevNode;
  }
  double meanTime = serviceSum / qp->length;
  return meanTime;
}

double computeStandardDeviation(QueuePointer qp, double meanTime) {
  NodePointer cnp = qp->pointerToHead;
  double diffSum = 0.0;
  while(cnp != NULL) {
    ProcessPointer cpp = cnp->processPointer;
    double diff = cpp->serviceTime - meanTime;
    diffSum += diff * diff;
    cnp = cnp->pointerToPrevNode;
  }

  double stdDev = diffSum / qp->length;
  return stdDev;
}

double computeMaxServiceTime(QueuePointer qp) {
  NodePointer cnp = qp->pointerToHead;
  double curMax = 0.0;
  while( cnp != NULL ) {
    ProcessPointer cpp = cnp->processPointer;
    if(cpp->serviceTime > curMax) {
      curMax = cpp->serviceTime;
    }
    cnp = cnp->pointerToPrevNode;
  }
  return curMax;
}

void computeStartStopTimes( QueuePointer qp ) {
  // cnp points to the current node in the linked list
  NodePointer cnp = qp->pointerToHead;
  while( cnp != NULL ) {

    // cpp points to the current process
    ProcessPointer cpp = cnp->processPointer;

    // Compute this process' serviceStartTime
    // This is the larger of this process' arrivalTime
    // and the serviceCompleteTime of the process that
    // entered the system immediately before this process
    // (Note! The first process is special, because there
    // is no process that entered the system before it did!)
    if( cnp->pointerToNextNode == NULL ) {
      // the first node is special---there is no node
      // in front of this node
      cpp->serviceStartTime = cpp->arrivalTime;
    } // if
    else {
      // a is time at which this process entered system
      double a = cpp->arrivalTime;
      // b is time at which service for the process that 
      // entered system just before this one completed
      double b = 
        cnp->pointerToNextNode->processPointer->serviceCompleteTime;

      // time at which service for this process is 
      // completed is the larger of the two numbers
      if( a > b ) {
  cpp->serviceStartTime = a;
      } // if
      else {
        cpp->serviceStartTime = b;
      } // else
    } // else

    // Compute this process' serviceCompleteTime
    // This is just the process' serviceStartTime + its
    // serviceTime
    cpp->serviceCompleteTime = cpp->serviceStartTime +
      cpp->serviceTime;

    cnp = cnp->pointerToPrevNode;
  } // while
}

void printHistogram(QueuePointer qp) {
  int queueLength = qp->length;
  int values[9] = {0};
  int i;
  for (i = 0; i < queueLength; ++i) {
    ProcessPointer pp = dequeue(qp);
    double st = pp->serviceTime;
    if (st < 1) {
      values[0] += 1;
    }
    else if (st > 1 && st < 2) {
      values[1] += 1;
    }
    else if (st > 2 && st < 3) {
      values[2] += 1;
    }
    else if (st > 3 && st < 4) {
      values[3] += 1;
    }
    else if (st > 4 && st < 5) {
      values[4] += 1;
    }
    else if (st > 5 && st < 6) {
      values[5] += 1;
    }
    else if (st > 6 && st < 7) {
      values[6] += 1;
    }
    else if (st > 7 && st < 8) {
      values[7] += 1;
    }
    else {
      values[8] += 1;
    } 
    enqueue(qp, pp);
  }

  printf("\nHistogram of Service Times [Seconds]:\n\n");

  for (i = 0; i < 9; ++i) {
    int j;
    if (i == 8) {
      printf("[ > 8 ] ");
    } else {
      printf("[%d - %d] ", i, i+1);
    }

    if (queueLength > 300) {
      for (j = 0; j < values[i]; ++j) {
        if (j%10 == 0) {
          printf("O");
        }
        else if (j == 1) {
          printf("O");
        }
      }
    }
    else {
    for (j = 0; j < values[i]; ++j) {
      printf("O");
    }
    }
    printf("\n");
  }
}