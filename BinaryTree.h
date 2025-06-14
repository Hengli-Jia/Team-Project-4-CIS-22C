#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"

template <typename T> class BinaryTree {
  private:
	BinaryNode<T> *rootPtr = nullptr;
	int count = 0;
	void _clear(BinaryNode<T> *node);

  public:
	BinaryTree() = default;
	~BinaryTree() { _clear(rootPtr); }
	bool isEmpty() const { return count == 0; }
	int getCount() const { return count; }
	void clear();
};

template <typename T> void BinaryTree<T>::_clear(BinaryNode<T> *node) {
	if (node) {
		_clear(node->getLeft());
		_clear(node->getRight());
		delete node;
	}
}

template <typename T> void BinaryTree<T>::clear() {
	_clear(rootPtr);
	rootPtr = nullptr;
	count = 0;
}

#endif
