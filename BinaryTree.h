#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"

class BinaryTree {
  protected:
	BinaryNode *rootPtr = nullptr;
	int count = 0;
	void _clear(BinaryNode *node);

  public:
	BinaryTree() = default;
	virtual ~BinaryTree() { _clear(rootPtr); }
	bool isEmpty() const { return count == 0; }
	int getCount() const { return count; }
	void clear();
	BinaryNode *getRoot() const { return rootPtr; }
};

void BinaryTree::_clear(BinaryNode *node) {
	if (node) {
		_clear(node->getLeft());
		_clear(node->getRight());
		delete node;
	}
}

void BinaryTree::clear() {
	_clear(rootPtr);
	rootPtr = nullptr;
	count = 0;
}

#endif
