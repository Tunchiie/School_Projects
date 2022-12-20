#include "bookTree.h"

BookTree::BookTree(){
  _root = nullptr;
}

BookTree::~BookTree(){
  /***********************************
   *      To be implemented
   * ********************************/

  //clear nodes recursively
  if (_root != nullptr){
    clear(_root->_left);
    clear(_root->_right);
    
  }
  delete _root;
  _root = nullptr;
}

BNode* BookTree::makeSplay(BNode* root, string key){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/
  
  //make the most recently accessed node the new root
  if (root == nullptr || root->_key == key){
    
    
    return root;
  }
  else{
    
    if (key < root->_key){
      
      if (root->_left != nullptr){

	
	if (root->_left->_key == key){

	  return leftRotate(root);
	}
	
	else {
	  
	  root->_left = makeSplay(root->_left, key);
	  
	  if (root->_left != nullptr)
	    
	    return leftRotate(root);
	  	  
	}
	
      }
         
    }
    else if (key > root->_key){
      
      if (root->_right != nullptr){
	
	if (root->_right->_key == key){
	  
	  return rightRotate(root);
	}
	else{
	  
	  root->_right = makeSplay(root->_right, key);
	  
	  if (root->_right != nullptr)
	    return rightRotate(root);	    
	  
	}
      }
    }
  }
  
  return root;
}
BNode* BookTree::rightRotate(BNode* x){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //rotate the right to the left
  BNode *newRoot = x->_right;
  x->_right = newRoot->_left;
  newRoot->_left = x;

  return newRoot;
}
BNode* BookTree::leftRotate(BNode* x){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //rotate the left to the right
  BNode *newRoot = x->_left;
  x->_left = newRoot->_right;
  newRoot->_right = x;
  
  return newRoot;
}

bool BookTree::insert(string key, string author, string text){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //call helper function to insert recursively
  bool newNode = insertHelp(key, author, text, _root);
  
  return newNode;
}
bool BookTree::insertHelp(const string& key, const string& author, const string& text, BNode*& aNode){

  //if the title doesn't exist, create a new node
  if (aNode == nullptr){
    
    aNode = new BNode(key, author, text);

    return true;
  }
  else if (aNode->_key == key){;
    
    return false;
  }
  
  //recursively insert
  else{

    
    if (key < aNode->_key){

      return insertHelp(key, author, text, aNode->_left);
    }

    else if (key > aNode->_key){

      return insertHelp(key, author, text, aNode->_right);

    }
    
  }
  return true;
}

void BookTree::clear(BNode* root){
  /***********************************
   *      To be implemented
   * ********************************/

  //recursively clear left and right nodes
  if (root != nullptr){
    clear(root->_left);
    clear(root->_right);
    delete root;
    root = nullptr;
  }
}

BNode* BookTree::find(BNode* aNode, string title){

  // find required nodes and make that node the new root
  if (aNode != nullptr && aNode->_key == title){
    
    
    _root = makeSplay(_root, title);
    
    return aNode;
  }

  //recursively find the title
  else if (aNode != nullptr){
    
    if (title < aNode->_key){
      return find(aNode->_left, title);
      
    }
    else if (title > aNode->_key){
      return find(aNode->_right, title);
      
    }

  }


  
  
  
  return nullptr;
  
}
void BookTree::inorderHelp(BNode* root, bool verbose) const{
     /***********************************
     *      Do not modify
     * ********************************/
    if (root != nullptr){
        if (verbose){
            cout << "(";
            inorderHelp( root->_left, verbose );
            cout << root->_key << ":" << root->_author;
	    root->_tree.dump();
            inorderHelp( root->_right, verbose );
            cout << ")";
        }
        else{
	  inorderHelp( root->_left, verbose );
	  cout << root->_key;
	  inorderHelp( root->_right, verbose );
        }
    }
}

void BookTree::dump(bool verbose) const{
     /***********************************
     *      Do not modify
     * ********************************/
    inorderHelp(_root, verbose);
}

int BookTree::findFrequency(string title, string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //find the number of times a word is used in wordtree
  int frequency = 0;
  if (_root != nullptr){
    
    if (_root->_key == title){
      
      frequency = _root->findFrequency(word);
    }
    else{
      
      BNode *node = find(_root, title);
      
      if (node != nullptr)
	frequency = node->findFrequency(word);
    }
  }  
  return frequency;
}
  
void BookTree::dumpTitle(string title){
  /***********************************
   *      To be implemented
   * ********************************/

  //dump wordtree of the title required
  BNode *node = find(_root, title);
  if (node != nullptr)
    node->_tree.dump();
  
}

int BookTree::searchCount(string title, string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //return number of nodes passed to get the required node
  if (_root != nullptr){
    
    if (_root->_key == title){
      return (_root->searchCount(word));
    }
    
    //find required node
    else{
      
      BNode *node = find (_root, title);
      if (node != nullptr)
	return (node->searchCount(word));
    }
  }
  
  return 0;
}

int BookTree::getTextTreeHeight(string title){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //get wordtree height
  BNode *node = find (_root, title);
  if (node != nullptr)
    return (node->getTextTreeHeight());
  return 0;
}
int BookTree::getWordHeight(string title, string word){
  /***********************************
   *      To be implemented
   * Note: to avoid warnings, a
   * fictional return value is added,
   * your implementaion should return
   * a correct value.
   * ********************************/

  //get a specific words height in a tree
  BNode *node = find (_root, title);

  if (node != nullptr)
    return (node->getNodeHeight(word));
  return 0;
}

string BookTree::getRootKey(){
  /***********************************
   *      Do not modify
   * ********************************/
  return _root->_key;
}

void BookTree::loadData(string dataFile){
  /***********************************
   *      This function is implemented
   *      to help you. You should't need
   *      to modify it.
   * ********************************/
  //read the entire file at once
  std::ifstream t(dataFile);
  std::stringstream buffer;
  buffer << t.rdbuf();

  //time to parse the information
  string titleDelimiter = "<==>";
  string itemsDeleimiter = "<=>";
  string s = buffer.str();
  size_t pos = 0;
  string token;
  while ((pos = s.find(titleDelimiter)) != string::npos) {
    token = s.substr(0, pos);//token is complete data for one title
    //get the title
    int tempPos = token.find(itemsDeleimiter);
    string title = token.substr(0,tempPos);
		//convert title to lower case
    std::transform (title.begin(), title.end(), title.begin(), ::tolower);
    token.erase(0, tempPos + itemsDeleimiter.length()+1);
    //get the author
    tempPos = token.find(itemsDeleimiter);
    string author = token.substr(0,tempPos);
    //convert author to lower case
    std::transform (author.begin(), author.end(), author.begin(), ::tolower);
    token.erase(0, tempPos + itemsDeleimiter.length()+1);
    //get the text
    string text = token.substr(0,token.length() - 1);//remove last newline
    //clean up the text, remove all non-alphanumeric characters
    for( std::string::iterator iter = text.begin() ; iter != text.end() ; ){
      if( !std::isalnum(*iter) && *iter != ' ') 
	iter = text.erase(iter) ;
      else 
	++iter ; // not erased, increment iterator
    }
    //convert text to lower case
    std::transform (text.begin(), text.end(), text.begin(), ::tolower);
    
    insert(title,author,text);
    
    //move to info for the next title
    s.erase(0, pos + titleDelimiter.length()+1);
  }
  
  cout << endl;
}
