#include "BST.h"

#include <iostream>

BinaryNode *BinaryTree::_insertBST(BinaryNode *nodePtr, BinaryNode *newPtr) {
	BinaryNode *pwalk = nodePtr;
	while (!pwalk->isLeaf()) {
		// parent = pwalk;
		if (pwalk->getKey() < newPtr->getKey())
			pwalk = pwalk->getLeft();
		else
			pwalk = pwalk->getRight();
	}
	if (newPtr->getKey() < pwalk->getKey())
		pwalk->setLeft(newPtr);
	else
		pwalk->setRight(newPtr);
	this->count++;
	return newPtr;
}

bool BinaryTree::_deleteBST(const Puzzle & /*item*/,
							BinaryNode * /*node*/) const {
	return false; // stubbed, returns false to silence warning
}

void BinaryTree::_inorderTraversal(void visit(string key),
								   BinaryNode *nodePtr) const {
	if (nodePtr) {
		_inorderTraversal(visit, nodePtr->getLeft());
		visit(nodePtr->getKey());
		_inorderTraversal(visit, nodePtr->getRight());
	}
}
void BinaryTree::_indetedTree(void visit(string key), BinaryNode *nodePtr,
							  int level) const {
	if (nodePtr) {
		visit(nodePtr->getKey());
		_indetedTree(visit, nodePtr->getRight(), level + 1);
		_indetedTree(visit, nodePtr->getLeft(), level + 1);
	}
}