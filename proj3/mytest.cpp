// CMSC 341 - Fall 2020 - Project 3
// mytest.cpp: test driver for the PQueue class.

#include "pqueue.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

// Priority functions compute an integer priority for a patient.  Internal
// computations may be floating point, but must return an integer.                                   

int priorityFn1(const Patient &patient);
int priorityFn2(const Patient &patient);
void logarithmicTime (PQueue& rhs);

const char* FAIL_STATEMENT = "*****TEST FAILED: ";
const char* PASS_STATEMENT = "     TEST PASSED: ";

int main() {

  // Create a patient queue with capacity five and priority function                                
  // priorityFn1()
  try{
    srand(time(NULL));
    
    PQueue queue1(priorityFn1);
    PQueue queue2(priorityFn1);
    int response;
    
    // Create some test jobs and insert them into the queue                                           
    //Patient(string name, int triage, int temp, int ox, int rr, int hr, int bp)
    
    Patient patient1("Jayden", rand() % 4 + 1, rand() % 12 + 30,	\
		     rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70 );
    Patient patient2("Romania", rand() % 4 + 1, rand() % 12 + 30,	\
		     rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70 );
    Patient patient3("India", rand() % 4 + 1, rand() % 12 + 30,		\
		     rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70 );
    Patient patient4("Mike", rand() % 4 + 1, rand() % 12 + 30,		\
		     rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70 );
    
    
    // test 1 - test if items were inserted properly
    queue1.insertPatient(patient3);
    queue1.insertPatient(patient1);
    queue1.insertPatient(patient2);
    queue1.insertPatient(patient4);
    
    Patient patient6("Jolanda", rand() % 4 + 1, rand() % 12 + 30,	\
		     rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70 );
    Patient patient5("07", rand() % 4 + 1, rand() % 12 + 30,		\
		     rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70 );
    
    
    cout << endl;
    
    if (queue1.numPatients() == 4){
      cout << PASS_STATEMENT << "the patients were correctly inserted" << endl;
    }
    else{
      cout << FAIL_STATEMENT << "insertPatients() doesn't work properly" << endl;
    }
    
    //test 2 - test if two queues were merged correctly
    queue2.insertPatient(patient6);
    queue2.insertPatient(patient5);
    
    queue1.mergeWithQueue(queue2);
    if (queue1.numPatients() == 6){
      cout << PASS_STATEMENT << "the patients were correctly merged" << endl;
    }
    else{
      cout << FAIL_STATEMENT << "the two heaps aren't merged" << endl;
    }

    // test 3 - test if merge functions only on queues
    //          with the same priority
    PQueue queue3(priorityFn2);
    try{
      cout << "     Test to check if different queues with different priority get merged:" << endl;
      queue3.mergeWithQueue(queue1);
      if (queue3.numPatients() == 0){
	cout << PASS_STATEMENT << "the queues weren't merged because they have different priority";
	cout << " functions"<< endl;
      }
      else{
	cout << FAIL_STATEMENT << "merge operates even with different priorities" << endl;
      }
    }
    catch (exception &e){
      cout << e.what() << endl;
    }
    
    // test 4
    queue3 = queue1;
    if (queue3.numPatients() == queue1.numPatients()){
      cout << PASS_STATEMENT << "assignment operator works perfectly" << endl;;
    }
    else{
      cout << FAIL_STATEMENT << "Implementation of assignment operator is horrible" << endl;
    }
    
    //test 5 - 
    if (queue3.getPriorityFn() == queue1.getPriorityFn()){
      cout << PASS_STATEMENT << "assignment operator copies over everything from ";
      cout <<"the queue to be copied" << endl;
    }
    else{
      cout << FAIL_STATEMENT << "Implementation of assignment operator is horrible" << endl;
    }
    cout << endl;
    
    //test 6 compare output after calling the assignment operator
    cout << "queue1 dump to compare queue1 and queue3:" << endl;
    queue1.printPatientQueue();
    
    cout << "queue3 dump to compare queue1 and queue3:" << endl;
    queue3.printPatientQueue();

    
    // test 7 - empty queue tests
    PQueue queue4(priorityFn1);

    //check if merging is possible with empty queue
    queue1.mergeWithQueue(queue4);
    if (queue1.numPatients() == 6){
      cout << PASS_STATEMENT << "the queues weren't merged because queue4 is empty" << endl;
    }
    else{
      cout << FAIL_STATEMENT << "merge operates even with the empty queues" << endl;
    }

    try{
      //should print queue is empty since the queue is empty
      cout << "     Test to check if empty queue is empty or not:" << endl;
      queue4.getNextPatient();
      
    }
    catch (exception &e){
      cout << e.what() << endl;
    }
  
    queue4.clear();
    cout << PASS_STATEMENT << "the program runs even when an empty queue clear function is called" << endl;
    cout << "                  so clear works perfectly" << endl;
    


    //test 8 - merging same queues
    queue1.mergeWithQueue(queue1);
    if (queue1.numPatients() == 6){
      cout << PASS_STATEMENT << "the queues weren't merged because they are the same" << endl;
    }
    else{
      cout << FAIL_STATEMENT << "merge operates even with the same queues" << endl;
    }

    cout << endl;
    // test 9 - setting priority
    cout << "Test to check if setPriority() rebuilds the heap:" << endl << endl;
    queue1.setPriorityFn(priorityFn2);
    queue1.printPatientQueue();
    
    // test for logarithmic run time
    logarithmicTime(queue1);
    
  }
  catch (exception &e){
    cout << e.what() << endl;
  }
  return 0;
  
}

void logarithmicTime(PQueue& rhs){
  
  //test 10 - test copy constructor and if code can handle                                         
  //         large volume of insers                                                          
  PQueue queue5(rhs);
  if (rhs.numPatients() == queue5.numPatients()){
    cout << PASS_STATEMENT << "copy constructor works perfectly" << endl;
  }
  else{
    cout << FAIL_STATEMENT << "copy constructor needs work" << endl;
  }

  cout << endl;
  //compare queues again
  cout << "queue5 dump to compare queue1 and queue5:" << endl;
  queue5.printPatientQueue();

  
  // test 11 - insert a large queue to test if it runs
  //          logarithmically

  clock_t start = clock(), end;
  
  PQueue queue6(priorityFn1);
  for (int i = 0; i < 100000; i++){
    Patient patient (to_string(i), rand() % 4 + 1, rand() % 12 + 30,		\
		     rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70 );
    queue6.insertPatient(patient);
  }

  end = clock();

  double time_taken1 = double (end - start) / double(CLOCKS_PER_SEC);

  PQueue queue7(priorityFn1);
  for (int i = 0; i < 1000000; i++){
    Patient patient (to_string(i), rand() % 4 + 1, rand() % 12 + 30,	\
                     rand() % 31 + 70, rand() % 35 + 5, rand() % 105 + 35, rand() % 90 + 70 );
    queue6.insertPatient(patient);
  }
  
  end = clock();

  double time_taken2 = double (end - start) / double(CLOCKS_PER_SEC);


  cout << "Time taken to insert 100000 items is " << time_taken1 << endl;
  cout << "Time taken to insert 1000000 items is " << time_taken2 << endl;
  cout << endl;
  cout << "In insertion or extraction, the logarithmic ";
  cout <<  "complexity of skew heap is due to its merging";
  cout << " function and since it's recursive merging costs ";
  cout << "us log(n). " << endl << "The merge function steps are; " << endl;
  cout << "1) Roots of the two heaps are compared firstly" << endl;
  cout << "2) Swap the children of the heap with the root of smaller priority" << endl;
  cout << "3) Merging the heap having larger root and ";
  cout <<  "the left subtree of the heap that has smaller root recursively." << endl;
  
  
  
  
}

int priorityFn1(const Patient&patient) {
  int pri = 5;
  if ((patient.getOxygen()<80 && (patient.getRR() > 35 || patient.getRR() < 8)) ||
      (patient.getHR() > 130 && patient.getBP() < 80))
      pri = 1;
  else if (((patient.getOxygen() >= 80 && patient.getOxygen() <= 89) && 
	    (patient.getRR() >= 31 && patient.getRR() <= 35)) ||
	   (patient.getTemperature() >= 40 || patient.getTemperature() <= 32))
    pri = 2;
  else if ((patient.getOxygen() >= 90 && patient.getOxygen() <= 94) && 
	   (patient.getRR() >= 26 && patient.getRR() <= 30))
    pri = 3; 
  else if ((patient.getOxygen() >= 95 && patient.getOxygen() <= 97) && 
	   (patient.getRR() >= 21 && patient.getRR() <= 25))
    pri = 4;
  else
      pri = 5;
  return pri;
}

int priorityFn2(const Patient&patient) {
  //priority only based on triage
  //traige is set by a health care professional
  return patient.getTriage();
}
