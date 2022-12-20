
//mytest.cpp: a c++ file that tests the copy constructor and assignment
//            operator making sure that they work perfectly.

//#include <iostream>
#include "queue.h"

using namespace std;

int main() {
  
  Queue<int> intQueue;
  int numOfItems = 10;
  //prints out data in the source queue
  cout << "\nPush integers on queue and dump contents:\n";
  for (int i = 1; i <= numOfItems; i++) {
    intQueue.enqueue(i);
  }

  intQueue.dump();
  
  Queue<int> duplicateQueue (intQueue);

  //prints duplicate queue from the copy constructor 
  cout << "\nRead contents of duplicate using head() and dequeue():\n";
  while ( not duplicateQueue.empty() ) {
    cout << duplicateQueue.head() << endl;
    duplicateQueue.dequeue();
  }

  
  Queue<int> assignedQueue;

  assignedQueue = intQueue;
  assignedQueue.reverse();
  //prints data from assigned operator
  cout << "\nRead contents of assigned  using head() and dequeue():\n";
  while ( not assignedQueue.empty() ) {
    cout << assignedQueue.head() << endl;
    assignedQueue.dequeue();
  }
  
  
}
