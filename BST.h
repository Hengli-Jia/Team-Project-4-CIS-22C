#ifndef BST_H
#define BST_H

#include "BinaryNode.h"

class BinaryTree {
  private:
	BinaryNode *rootPtr = nullptr;
	int count;
	BinaryNode* _insertBST(BinaryNode *, BinaryNode *) const;
	bool _deleteBST(BinaryNode * , BinaryNode *) const;
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
		BinaryNode* deleteNode = new BinaryNode (deletePuzzle);
		if (_deleteBST(deleteNode, this->rootPtr)) {
			return true;
		}
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
	~BinaryTree() { clear(rootPtr); }
	void clear(BinaryNode *node) {
		if (node) {
			clear(node->getLeft());
			clear(node->getRight());
			delete node;
		}
	}
};

#endif
