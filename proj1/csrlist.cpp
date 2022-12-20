// CMSC 341 - Fall 2020 - Project 1
#include "csrlist.h"

CSRList::CSRList(){
    /***********************************
     *      To be implemented
     * ********************************/
  m_head = nullptr;
  m_size = 0;
}

CSRList::~CSRList(){
    /***********************************
     *      To be implemented
     * ********************************/
  //clears all variables and pointers stored
  clear();
  
}
CSRList::CSRList(const CSRList & rhs){

  CSR *current = rhs.m_head;
  int counter = rhs.m_size, number = 0;
  
  while (counter > 0){
    
    while (current != nullptr){
      
      if (number == counter - 1){
	
	insertAtHead(*current);
      }
      
      current = current->m_next;
      
      number++;
    }
    number = 0;
    counter--;
    current = rhs.m_head;
  }
}
bool CSRList::empty() const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
  // checks if object is empty
  if (m_size == 0){
    return true;
  }
  return false;
}

void CSRList::insertAtHead(const CSR & matrix){
    /***********************************
     *      To be implemented
     * ********************************/
  // inserts new object at head
  CSR *newNode = new CSR(matrix);
  
  if (m_head != nullptr){
    
    newNode->m_next = m_head;

    m_head = newNode;
  }
  else{

    m_head = newNode;
  }
  m_size++;
}

void CSRList::clear(){
    /***********************************
     *      To be implemented
     * ********************************/

  //deletes all private variables
  
  CSR *current = m_head;
  
  while (current != nullptr){
    
    current = current->m_next;
    
    delete m_head;

    m_head = current;

  }

  
  m_head = nullptr;

  m_size = 0;

}

int CSRList::getAt(int CSRIndex, int row, int col) const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
  CSR *temp = m_head;
  
  int value;
  
  if ((CSRIndex < m_size) && (CSRIndex > 0)){
    ///gets desired value from object in a CSR list
    for (int i = 0; i < CSRIndex + 1; i++){
      
      if ((temp != nullptr) && (i == CSRIndex)){
	
	value = temp->getAt(row,col);
      }
      temp = temp->m_next;
    }
    
  }
  else {
    
    throw runtime_error("Error: Object is not in the list!");
  }
  return value;
}
  
void CSRList::dump(){
  
    if (!empty()){
        CSR* temp = m_head;
        while (temp != nullptr){
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        throw runtime_error("Error: List is empty!");
}

bool CSRList::operator== (const CSRList & rhs) const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
  bool sameSize = false, sameLists = false;
  int numOfSameLists = 0;
  CSR *current = m_head, *rhsCurrent = rhs.m_head;
  
  if (m_size == rhs.m_size){
    sameSize = true;
  }

  while ((current != nullptr) && (rhsCurrent != nullptr)){

    if (*current == *rhsCurrent){
      numOfSameLists++;
    }
    current = current->m_next;
    rhsCurrent = rhsCurrent->m_next;
  }

  if ((numOfSameLists == m_size) && (sameSize == true)){
    return true;
  }
  
  return false;
  
}

const CSRList& CSRList::operator=(const CSRList & rhs){
    /***********************************
     *      To be implemented
     * ********************************/
  
  if (this != &rhs){

    clear();
    
    CSR *current = rhs.m_head;
    int counter = rhs.m_size, number = 0;
    
    while (counter > 0){
      
      while (current != nullptr){
	
	if (number == counter - 1){
	  insertAtHead(*current);
	}
	
	current = current->m_next;
	
	number++;
      }
      number = 0;
      counter--;
      current = rhs.m_head;
    }

    
  }
  return *this;
}

int CSRList::averageSparseRatio(){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  //gets the sparse ratio of the objects in the list
  CSR *temp = m_head;
  int averageRatio = 0, individualRatio = 0;
  
  while (temp != nullptr){
    
    individualRatio = temp->sparseRatio();
    averageRatio +=  individualRatio;
    temp = temp->m_next;
  }
  return (averageRatio / m_size);
}
