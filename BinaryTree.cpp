#include "BinaryTree.h"

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
