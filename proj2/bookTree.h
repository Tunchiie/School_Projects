#ifndef BOOKTREE_H
#define BOOKTREE_H
#include "bNode.h"

class BookTree{
    public:
        BookTree();
        ~BookTree();
        void dump(bool verbose=false) const;
        void loadData(string dataFile);//reads data from file and insert into data structure
        int findFrequency(string title, string word);//returns number of occurrences of a word in a book
        void dumpTitle(string title);//dumps all nodes in the word tree of a book
        int searchCount(string title, string word);//returns the number of operations for a search in word tree of a book
        int getTextTreeHeight(string title);//returns height of wrod tree for a book
        int getWordHeight(string title, string word);//returns height of a node in word tree of a book
        string getRootKey();//returns the book title at root
        

        /****************************************************************
        * your public member functions start here
        * *************************************************************/
  
        /****************************************************************
        * your public member functions end here
        * *************************************************************/
    private:
        BNode* _root;
        bool insert(string key, string author, string text);
        BNode* makeSplay(BNode* root, string key);
        BNode* rightRotate(BNode* x);
        BNode* leftRotate(BNode* x);
        void clear(BNode* root);
        void inorderHelp(BNode* root, bool verbose=false) const;
        /****************************************************************
        * your private member functions start here
        * *************************************************************/
        int searchCountHelp(Node* aNode, string title, string word);
  
        bool insertHelp(const string& key, const string& author, const string& text, BNode*& aNode);
  
        BNode* find(BNode* aNode, string title);
        /****************************************************************
        * your private member functions end here
        * *************************************************************/
};
#endif
