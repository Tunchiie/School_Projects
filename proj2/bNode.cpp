#include "bNode.h"
BNode::BNode(){}
BNode::BNode(string key, string author, string text){
  _key = key;
  _author = author;
  _left = nullptr;
  _right = nullptr;
  _flag = false;
  _parent = nullptr;
  createTextTree(text);
}
BNode::~BNode(){

  _key = "";
  _author = "";
  
}

void BNode::createTextTree(string text){
  istringstream iss(text);
  vector<string> tokens;
  copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
  for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
    _tree.insert(*it);
  }
}

int BNode::findFrequency(string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
  
  //call get frequency function in wordtree
  if (_tree.getRootHeight() != -1){
    Node* current = _tree.find(word);
    int frequency = current->getFrequency();
    return frequency;
  }
  return 0;
}

int BNode::searchCount(string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //counts number of nodes passed to get to word
  if (_tree.getRootHeight() != -1){
    int no_visited_nodes = _tree.searchCount(word);
    return no_visited_nodes;
  }
  return 0;
}

int BNode::getTextTreeHeight(){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //get the height of the root
  if (_tree.getRootHeight() != -1){
    int height = _tree.getRootHeight();
    return height;
  }
  return 0;
}

int BNode::getNodeHeight(string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //get height of a word
  if (_tree.getRootHeight() != -1){
    int height = _tree.getNodeHeight(word);
    return height;
  }
  return 0;
}
