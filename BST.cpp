# include "BST.h"
# include <iosream>

using namespace std;

BinaryNode* _insertBST (BinaryNode* nodePtr, BinaryNode* newPtr) const {
  BinaryNode* pwalk = nodePtr;
  while (!pwalk -> isLeaf()) {
    // parent = pwalk;
  if (pwalk -> getItem() < newPtr.getItem() )
    pwalk = pwalk -> getLeft();
  else 
    pwalk = pwalk -> getRight();
  }
  if (newPtr -> getItem() < pwalk.getItem())
    pwalk -> setLeft(newPtr);
  else 
    pwalk -> setRight(newPtr);
  return newPtr;
}

void _deleteBST (const& Puzzle item) const  {

  
}
void _inorderTraversal (void visit(Puzzle& item), BinaryNode* nodePtr) const {
  Puzzle puzzle = nodePtr -> getItem();
  if (nodePtr) {
  _inorderTraversal (visit, nodePtr -> getLeft());
  visit(puzzle);
  _inordeTraversal (visit, nodePtr -> getRight());
  }
}
void _indetedTree(void visit (Puzzle& item), BinaryNode* nodePtr, int level) const {
  Puzzle puzzle = nodePtr -> getItem();
  if (nodePtr) {
  visit(puzzle);
  _indentedTree(visit, nodePtr -> getRight(), level + 1);
  _indentedTree (visit, nodePtr -> getLeft(), level + 1);
  }
}


