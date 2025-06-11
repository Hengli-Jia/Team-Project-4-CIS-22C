#ifndef BST_H
#define BST_H

# include <iostream>
#include "BinaryNode.cpp"
# include "Puzzle.h"

class BinaryTree {
private: 
  BinaryNode* rootPtr;
  int count;
  BinaryNode* _insertBST (BinaryNode*, BinaryNode*);
  bool _deleteBST (const Puzzle& item, BinaryNode* node) const;
  void _inorderTraversal (void visit(string& key), BinaryNode* nodePtr) const;
  void _indetedTree (void visit (string& key), BinaryNode* nodePtr, int level) const;

public: 
  bool isEmpty () { return count == 0;}
  int  getCount () {return count;}
  bool insertBST (const Puzzle& inputPuzzle) { 
    BinaryNode* newNode = new BinaryNode(inputPuzzle);
    this -> rootPtr = _insertBST(this -> rootPtr, newNode) ;
    return true;
  }
  bool deleteBST (const Puzzle& deletePuzzle) {
    BinaryNode* newNode = new BinaryNode(deletePuzzle);
    if (_deleteBST(deletePuzzle, this->rootPtr))
      return true;
    else 
      return false;
  }
  void inorderTraversal (void visit(string& key), BinaryNode* nodePtr) {_inorderTraversal (visit, rootPtr);}
  void indetedTree(void visit (string& currPuzzle), BinaryNode*, int level) {_indetedTree(visit , rootPtr, 1);} 
};

#endif

