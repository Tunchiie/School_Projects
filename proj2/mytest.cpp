#include <iostream>
# include "bookTree.cpp"

using namespace std;

int main(){
  
  auto wt = WordTree();
  string element;
  int response;
  cout << "which program would you like to run" << endl;
  cout << "1. wordTree.cpp" << endl;
  cout << "2. bookTree.cpp" << endl;
  cin >> response;
  
  if (response == 1)
    while (response != 7)
      {
	cout << "Which action would you like the program to perform" << endl;
	cout << "1. Insert" << endl;
	cout << "2. Search count" << endl;
	cout << "3. Find word" << endl;
	cout << "4. Get tree height" << endl;
	cout << "5: Get word height" << endl;
	cout << "6. dump tree" << endl;
	cout << "7. STOP" << endl;
	cout << "Enter Action: ";
	cin >> response;
	
	while (cin.fail() || ((response < 1) || (response > 7))){
	  cout << "Which action would you like the program to perform" << endl;
	  cout << "1. Insert" << endl;
	  cout << "2. Search count" << endl;
	  cout << "3. Find word" << endl;
	  cout << "4. Get tree height" << endl;
	  cout << "5: Get word height" << endl;
	  cout << "6. dump tree" << endl;
	  cout << "7. STOP" << endl;
	  cout << "Enter Action: ";
	  cin.clear();
	  cin.ignore();
	  cin >> response;
	}
	
	switch (response){
	  
	case 1:
	  cout << endl << "Enter a new element: ";
	  cin >> element;
	  wt.insert(element);
	  cout << endl;
	  break;
	  
	case 2:
	  cout << endl << "Enter a new word to search for: ";
	  cin >> element;
	  cout << "The serch count for " << element;
	  cout << " is: " << wt.searchCount(element) << endl;
	  cout << endl;
	  break;
	  
	case 3:
	  cout << endl << "Enter a new word to search for: ";
	  cin >> element;
	  
	  if (wt.find(element))
	    cout << "The word is in the word tree" << endl;
	  
	  else
	    cout << "The word is not in the word tree" << endl;
	  cout << endl;
	  break;
	  
	case 4:
	  
	  if (wt.getRootHeight()  != -1){
	    cout << "The height of your word tree is: ";
	    cout << wt.getRootHeight() << endl;
	  }
	  else{
	    cout << "The tree is empty" << endl;
	  }
	  cout << endl;
	  break;
	  
	case 5:
	  cout << endl << "Enter a new word to search for: ";
	  cin >> element;
	  
	  if (wt.getNodeHeight(element) != -1){
	    
	    cout << "The height of your word in the word tree is: ";
	    cout << wt.getNodeHeight(element) << endl;
	  }
	  else{
	    cout << element <<" doesn't exist in word tree" << endl;
	  }
	  cout << endl;
	  break;
	  
	case 6:
	  wt.dump();
	  cout << endl;
	  break;
	  
	case 7:
	  response = 7;
	  break;
	  
	}
	
      }
  
  
  if (response == 2){
    
    
    
    string title = "";
    BookTree aTree;
    aTree.loadData("data.txt");
    
    cout << "These are the stories available for studying:" << endl;
    cout << endl;
    aTree.dump();
    cout << endl;
    while (response != 7)
      {
	cout << "Which action would you like the program to perform" << endl;
	cout << "1. Find Frequency" << endl;
	cout << "2. dump list of stories" << endl;
	cout << "3. dump the word tree for a specific story" << endl;
	cout << "4. Get the word tree height of a specific story" << endl;
	cout << "5: Get height of a word in a specific story" << endl;
	cout << "6. search count of word" << endl;
	cout << "7. STOP" << endl;
	cout << "Enter Action: ";
	cin >> response;
	while (cin.fail() || ((response < 1) || (response > 7))){
	  cout << "Which action would you like the program to perform" << endl;
	  cout << "1. Find Frequency" << endl;
	  cout << "2. dump list of stories" << endl;
	  cout << "3. dump the word tree for a specific story" << endl;
	  cout << "4. Get the word tree height of a specific story" << endl;
	  cout << "5: Get height of a word in a specific story" << endl;
	  cout << "6. search count of word" << endl;
	  cout << "7. STOP" << endl;
	  cout << "Enter Action: ";
	  cin.clear();
          cin.ignore();
	  cin >> response;
	  
	}
	

	switch (response){
	  
	case 1:
	  cout << endl << "which story would you like to search: ";
	  cin.ignore();
	  getline(cin, title);
	  cout << "Which word are you searching for: ";
	  cin >> element;
	  if (aTree.findFrequency(title, element) != 0){
	    cout << "Frequency of " << element << " in ";
	    cout << title << ": " << endl;
	    cout << "\t" << aTree.findFrequency(title, element) << endl;
	    cout << endl;
	    break;
	  }
	  cout << endl;
	  cout << "The word " << element << " doesn't exist in the story ";
	  cout << "or the story doesn't exist" << endl;
	  cout << endl;
	  break;
	  
	case 2:
	  cout << endl;
	  cout << "These are the stories available for studying:" << endl;
	  cout << endl;
	  aTree.dump();
	  cout << endl;
	  break;
	  
	case 3:
	  cout << endl << "Which story would you like to see: ";
	  cin.ignore();
	  getline(cin, title);
	  
	  cout << "Dumping the word tree for " << title << ":" << endl;
	  cout << endl;
	  aTree.dumpTitle(title);
	  cout << endl;
	  break;
	  
	case 4:
	  cout << endl << "Which story would you like to search: ";
	  cin.ignore();
	  getline(cin, title);
	  
	  if (aTree.getTextTreeHeight(title)  != -1){
	    cout << "The height of word tree for " << title << ":" << endl;;
	    cout << "\t" << aTree.getTextTreeHeight(title) << endl << endl;;
	  }
	  else{
	    cout << "The tree is empty" << endl;
	  }
	  cout << endl;
	  break;
	  
	case 5:
	  cout << endl << "Which story would you like to search: ";
	  cin.ignore();
	  getline(cin, title);
	  
	  cout << "Enter a word to search for: ";
	  cin >> element;
	  
	  if (aTree.getWordHeight(title, element) != -1){
	    
	    cout << "The height of the node containing " << element <<" in ";
	    cout << title << ":" << endl;
	    cout << "\t" << aTree.getWordHeight(title, element) << endl << endl;
	  }
	  else{
	    cout << element <<" doesn't exist in word tree of ";
	    cout << title << " or the story doesn't exist " << endl;
	  }
	  cout << endl;
	  break;
	  
	case 6:
	  cout << endl << "which story would you like to search: ";
	  cin.ignore();
	  getline(cin, title);
	  cout << "Enter a word to search for: ";
	  cin >> element;
	  if (aTree.searchCount(title, element) != 0){
	    cout << "Count of search operation for " << element << "in";
	    cout << title << ":" << endl;
	    cout << "\t" << aTree.searchCount(title, element) << endl << endl;
	  }
	  else{
	    cout << "The word " << element << " is either the root or doesn`t exist" << endl;
	    cout << endl;
	  }
	  break;
	  
	case 7:
	  response = 7;
	  break;
	  
	  
	  
	}
      }
  }

  return 0;
}
