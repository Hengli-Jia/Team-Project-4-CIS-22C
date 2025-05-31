#ifndef "BST.h"
#define "BST.h"
class BinaryTree {
private:
  BinaryNode* nodePtr; 
  void _insertBST (const& string, const& string) const;
  void _deleteBST (const& string) const;
  void _inorderTraversal (void visit(string&), BinaryNode*) const;
  void _indetedTree(void visit (string&), BinaryNode*, int level) const;

public: 
  void insertBST (const& string newPuzzle) { _insertBST(newPuzzle) ;}
  void deleteBST (const& string Puzzle) {_deleteBST(Puzzle);}
  void inorderTraversal (void visit(Puzzle currPuzzle), BinaryNode*) {_inorderTraversal (visit(currPuzzle), BinaryNode*) const;}
  void indetedTree(BinaryNode*) {_indetedTree(void visit (visit (string&), BinaryNode*, int level) const;} 
};

#endif

