#ifndef BST_H
#define BST_H

#include "BinaryNode.h"
#include "Puzzle.h"
#include <iostream>

class BinaryTree {
  private:
	BinaryNode *rootPtr = nullptr;
	int count;
	BinaryNode *_insertBST(BinaryNode *, BinaryNode *);
	bool _deleteBST(const Puzzle &item, BinaryNode *node) const;
	void _inorderTraversal(void visit(string key), BinaryNode *nodePtr) const;
	void _indetedTree(void visit(string key), BinaryNode *nodePtr,
					  int level) const;

  public:
	bool isEmpty() { return count == 0; }
	int getCount() { return count; }
	bool insertBST(const Puzzle &inputPuzzle) {
		BinaryNode *newNode = new BinaryNode(inputPuzzle);
		this->rootPtr = _insertBST(this->rootPtr, newNode);
		return true;
	}
	bool deleteBST(const Puzzle &deletePuzzle) {
		if (_deleteBST(deletePuzzle, this->rootPtr))
			return true;
		else
			return false;
	}
	void inorderTraversal(void visit(string key) /*nodePtr*/) const {
		_inorderTraversal(visit, rootPtr);
	}
	void indetedTree(void visit(string currPuzzle) /*nodePtr*/,
					 int /*level*/) const {
		_indetedTree(visit, rootPtr, 1);
	}
};

#endif
