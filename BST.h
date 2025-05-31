#ifndef "BST.h"
#define "BST.h"

# include <iosteam>

class BinaryTree {
private:
  BinaryNode* nodePtr; 
  void _insertBST (const& Puzzle item) const;
  void _deleteBST (const& Puzzle item) const;
  void _inorderTraversal (void visit(Puzzle& item), BinaryNode*) const;
  void _indetedTree (void visit (Puzzle&i tem), BinaryNode*, int) const;

public: 
  void insertBST (const& string newPuzzle) { _insertBST(newPuzzle) ;}
  void deleteBST (const& string Puzzle) {_deleteBST(Puzzle);}
  void inorderTraversal (void visit(Puzzle currPuzzle), BinaryNode*) {_inorderTraversal (visit, BinaryNode*);}
  void indetedTree(void visit (Puzzle currPuzzle), BinaryNode*, int level) {_indetedTree(visit , BinaryNode*, 1);} 
};

#endif

