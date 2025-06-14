#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"
#include <string>

class BinaryTree {
  private:
	BinaryNode *rootPtr = nullptr;
	int count = 0;
	void _clear(BinaryNode *node);

  public:
	BinaryTree() = default;
	~BinaryTree() { _clear(rootPtr); }
	bool isEmpty() const { return count == 0; }
	int getCount() const { return count; }
	void clear();
};

#endif
