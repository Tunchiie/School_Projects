#include "wordTree.h"
# include <iostream>

using namespace std;



WordTree::~WordTree(){
    /***********************************
     *      To be implemented
     * ********************************/
  //recursively clears nodes
  if (_root != nullptr){
    clearTree(_root->_left);
    clearTree(_root->_right);
  }
  delete _root;
}

void WordTree::updateHeight(Node *aNode) {
  /***********************************
   *      To be implemented
   * ********************************/

  int newHeight = 1;
  
  if (aNode != nullptr){
    Node *aNodeLeft = aNode->_left;
    Node *aNodeRight = aNode->_right;

    // add 1 to the height of the highest subtree
    if ((aNodeRight != nullptr)			\
	&& (aNodeLeft != nullptr)){
      
      
      
      
      if ((aNodeLeft->_height)			\
	  > (aNodeRight->_height)){
	
	aNode->_height = 1 + aNode->_left->_height;

      }
      
      else if ((aNodeLeft->_height)		\
	       < (aNodeRight->_height)){
	
	aNode->_height = 1 + aNode->_right->_height;

	
      }

      //if both heights are equal, add from any subtree
      else{
	aNode->_height = 1 + aNode->_right->_height;
      }
    }

    // add 1 to the only subtree height
    else if ((aNodeRight != nullptr )||		\
	     (aNodeLeft != nullptr)){
      
      if (aNodeRight != nullptr){

	
	
	aNode->_height = newHeight + aNode->_right->_height;

      }

      else if (aNodeLeft != nullptr){

	
	aNode->_height = newHeight + aNode->_left->_height;

      }
    }

    // the node with no subtrees has a height of 0
    else{
      aNode->_height = 0;

    }
    
  }
}

void WordTree::clearTree(Node* aNode){
    /***********************************
     *      To be implemented
     * ********************************/

  //recursively clear left and right of the node
  if (aNode != nullptr){
    clearTree(aNode->_left);
    clearTree(aNode->_right);
    delete aNode;
  }
}

void WordTree::inOrder(Node* aNode, std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/

  if (aNode != nullptr){

    ostr << "[";
    inOrder(aNode->_left, ostr);
    ostr << aNode->_value << ":" << aNode->_count << ":" << aNode->_height;
    inOrder(aNode->_right, ostr);
      ostr << "]";
  }
}

Node* WordTree::find(Node* aNode, const string& element){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  //check the node for same element, if not found check left
  //                                 and right of node.
  Node *aNodeLeft = aNode->_left;
  Node *aNodeRight = aNode->_right;
  

  if (element == aNode->_value){

    return aNode;
  }
  else if (element < aNode->_value){

    if (aNodeLeft != nullptr){
      return find (aNodeLeft, element);
    }
    else{
      return nullptr;
    }
  }
  else {

    if (aNodeRight != nullptr){
      
      return find (aNodeRight, element);
    }
    else{
      return nullptr;
    }
  }
  
  return nullptr;
}
Node* WordTree::find(const string& element){
    /***********************************
     *      To be implemented
     * ********************************/

  //check root for word
  if ((_root->_value) == element){
    return _root;
  }

  // call find helper to recursively find it
  else{
    
    return find (_root, element);
  }
  
}

Node* WordTree::rightRotation(Node* aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  // rotate right to left
  Node *newRoot = aNode->_right;
  Node *left = newRoot->_left;

  aNode->_right = left;
  newRoot->_left = aNode;

  // update heights of the changed nodes
  updateHeight(aNode);
  updateHeight(newRoot);

  
  return newRoot;
}

Node* WordTree::leftRotation(Node* aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  // rotate left to right
  Node *newRoot = aNode->_left;
  Node *next = newRoot->_right;
  
  aNode->_left = next;
  newRoot->_right = aNode;
  
  //update the height                                                         
  updateHeight(aNode);
  updateHeight(newRoot);
  
  return newRoot;
}

Node* WordTree::leftRightRotation(Node* aNode){

  // rotate right to left but rotate lefts left first
  Node *newRoot = aNode->_left;
  aNode->_left = rightRotation(newRoot);
  
  return leftRotation(aNode);
}

Node* WordTree::rightLeftRotation(Node* aNode){

  // rotate left to right but rotate rights right first
  Node *newRoot = aNode->_right;
  aNode->_right = leftRotation(newRoot);
  

  return rightRotation(aNode);
}
int WordTree::checkBalance(Node* aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
  
  int balance = 0;

  // check left and right subtree to find the difference
  if (aNode != nullptr){
    
    if ((aNode->_left != nullptr) &&		\
	(aNode->_right != nullptr)){
      
      balance = aNode->_left->getHeight()	\
	- aNode->_right->getHeight();
    }
    else{
      if (aNode->_left != nullptr){
	balance = (aNode->_left->getHeight()) - (-1);
	return balance;
      }
      else if (aNode->_right != nullptr){
	balance = (-1) - (aNode->_right->getHeight());
	
	return balance;
      }
    }
    
  }

  return balance;
}

Node* WordTree::reBalance(Node* aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  int balance = checkBalance(aNode);

  //checks which direction to rotate in
  int leftRotate = 1, rightRotate = -1;
  int rightLeftRotate = 0, leftRightRotate = 0;
  

  if (checkBalance(aNode) > 0 ||		\
      checkBalance(aNode) < 0){

    // if left tree is higher, then rotate on the
    //                        left side.
    if (balance  > leftRotate){
      
      if ((checkBalance(aNode->_left)) >  leftRightRotate){
	return leftRotation(aNode);
      }
      
      
      else{
	
	return leftRightRotation(aNode);
	
      }
      
    }

    // if right subtree is higher, then rotate on
    //                            right side.
    else if (balance < rightRotate){


      if (checkBalance(aNode->_right) > rightLeftRotate){
	
	return rightLeftRotation(aNode);
      }
      
      else{
	return rightRotation(aNode);
      }
    }

  }

  return aNode;
}

void WordTree::insert(const string& element){
    /***********************************
     *      To be implemented
     * ********************************/
  

  insert(element, _root);
  
}
Node* WordTree::insert(const string& element, Node*& aNode){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //recursively insert until the correct location is found

  
  
  if (aNode == nullptr){
    
    aNode = new Node(element);
    
    updateHeight(aNode);
    
    aNode->_count++;
    
    return aNode;
  }
  
  

  
  //notify if duplicate exists in tree
  else if(aNode->_value == element){
    
    aNode->_count++;

    return aNode;
  }

  //recursively insert
  else{
    
    if (element < aNode->_value){
    
      insert(element, aNode->_left);
      
    }
    else if (element > aNode->_value){
      
      insert(element, aNode->_right);
      
    }
    
  }

  //update height of aNode
  updateHeight(aNode);

  //rebalance aNode if needed
  aNode = reBalance(aNode);
  
  return aNode;
}

void WordTree::dump(std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    inOrder(_root, ostr);
}

int WordTree::searchCount(string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
  
  int counter = 0;

  //check if the root has the same word
  // if not call helper function
  if (_root->_value == word){
    return counter;
  }
  else{
    return searchCountHelp(_root, word, counter);
    
  }
  return counter;
}

int WordTree::searchCountHelp(Node* aNode, string word, int counter){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
  
  int newCounter = counter;
  Node *aNodeLeft = aNode->_left;
  Node *aNodeRight = aNode->_right;

  //recursively check right and left for word
  if (word == aNode->_value){
    return newCounter++;
  }
  else if (word < aNode->_value){
    if (aNodeLeft != nullptr){
      newCounter++;
      return searchCountHelp (aNodeLeft, word, newCounter);
    }
    else{
      return newCounter;
    }
  }
  else {
    if (aNodeRight != nullptr){
      
      newCounter++;
      
      return searchCountHelp (aNodeRight, word, newCounter);
    }
    else{
      return newCounter;
    }
  }
  return newCounter;
}

int WordTree::getRootHeight(){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  // check the height of root
  if (_root != nullptr){

    return (_root->_height);
  }
  return -1;
}

int WordTree::getNodeHeight(string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  // return the height of word
  int height = getNodeHeightHelp(_root, word), empty = -1;
  
  if (height == 0)
    return empty;
  
  return height;
  
}
  

int WordTree::getNodeHeightHelp(Node* aNode, string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  //return the height of the desired word
  Node *desiredNode = find (aNode, word);
  
  if (desiredNode)
    
    return desiredNode->_height;
  
  return -1;
}
