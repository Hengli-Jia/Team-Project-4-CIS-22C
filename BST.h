#ifndef BST.H
#define BST.H

# include <iostream>
#include "BinaryNode.cpp"

class BinaryTree {
private: 
  BinaryNode* rootPtr;
  int count;
  BinaryNode* _insertBST (BinaryNode*, BinaryNode*) const;
  void _deleteBST (const& Puzzle item) const;
  void _inorderTraversal (void visit(Puzzle& item), BinaryNode*) const;
  void _indetedTree (void visit (Puzzle&i tem), BinaryNode*, int) const;

public: 
  bool isEmpty () { return count == 0;}
  int  getCount () {return count;}
  bool insertBST (const& string newPuzzle) { 
    BinaryNode* newNode = new BinaryNode(newPuzzle);
    this -> rootPtr = _insertBST(this -> rootPtr, newNode) ;
    return true;
  }
  void deleteBST (const& string Puzzle) {
    BinaryNode* newNode = new BinaryNode(newPuzzle);
    if (_deleteBST(root-> Ptr, newNode))
    return true;
    else 
    return false;
  }
  void inorderTraversal (void visit(Puzzle currPuzzle), BinaryNode*) {_inorderTraversal (visit, rootPtr);}
  void indetedTree(void visit (Puzzle currPuzzle), BinaryNode*, int level) {_indetedTree(visit , rootPtr, 1);} 
};

#endif

