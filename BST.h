#ifndef BST.H
#define BST.H

# include <iostream>
#include "BinaryNode.cpp"
# include "Puzzle.h"

class BinaryTree {
private: 
  BinaryNode* rootPtr;
  int count;
  BinaryNode* _insertBST (BinaryNode*, BinaryNode*) const;
  bool _deleteBST (const Puzzle& item, BinaryNode* node) const;
  void _inorderTraversal (void visit(Puzzle& item), BinaryNode*) const;
  void _indetedTree (void visit (Puzzle& item), BinaryNode*, int) const;

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
  void inorderTraversal (void visit(Puzzle& currPuzzle), BinaryNode*) {_inorderTraversal (visit, rootPtr);}
  void indetedTree(void visit (Puzzle& currPuzzle), BinaryNode*, int level) {_indetedTree(visit , rootPtr, 1);} 
};

#endif

