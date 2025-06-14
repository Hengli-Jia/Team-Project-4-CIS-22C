#pragma once
#include "BinaryTree.h"

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
