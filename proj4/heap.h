// CMSC 341 - Fall 2020 - Project 4
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************
  void maxify (unsigned index);
  unsigned Parent(unsigned index);
};

// ***************************************
// Templated function definitions go here!
// ***************************************

template <class T>
Heap<T>::Heap(){

  // initialize used variable
  _used = false;
}

template <class T>
unsigned Heap<T>::Parent(unsigned index){

  //get parent of the index passed in
  if (size() == index)
    return ((index) / 2);
  return ((index - 1) / 2);
  
}

template <class T>
void Heap<T>::maxify(unsigned index){

  // orders heap in a max heap order
  if (index > 0 && Parent(index) > 0\
      && _heap[Parent(index)].priority() < _heap[index].priority()){
    
    // swap indices
    T object = _heap[Parent(index)];
    _heap[Parent(index)] = _heap[index];
    _heap[index] = object;

    // recursively order the heap in max order
    maxify (Parent(index));
  }

  

  
}

template <class T>
void Heap<T>::insert(const T& object){

  // create dummy object and push back that if heap is empty
  // else just push back and order the heap
  if (used() == false){
    T dummy;
    _heap.push_back(dummy);
    
  }
  _heap.push_back(object);
  if (used() == true)
    maxify (size());
  
  _used = true;
}

template <class T>
T Heap<T>::readTop() const{

  // return the object at root
  if (!empty()){
    return _heap.at(ROOT);
  }
  
  // or throw an error, if heap is empty 
  throw range_error("_heap is empty");
}

template <class T>
void Heap<T>::removeTop(){

  // remove object at root and reorder the heap
  if (!empty()){
    _heap[ROOT] = _heap.back();
    _heap.pop_back();
    maxify(size());
    return ;
  }

  // throw error if heap is empty
  throw range_error("_heap is empty");
}

template <class T>
void Heap<T>::dump() const{

  // dump _heap
  for (unsigned i = ROOT; i <= size() ; i++){
    
    cout << _heap.at(i) << endl;
  }
}
#endif
