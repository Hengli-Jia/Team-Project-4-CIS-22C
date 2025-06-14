#include "BST.h"

BinaryNode *BinaryTree::_insertBST(BinaryNode *nodePtr, BinaryNode *newPtr) {
	if (!nodePtr) {
		this->count++;
		return newPtr;
	}
	if (newPtr->getKey() < nodePtr->getKey()) {
		nodePtr->setLeft(_insertBST(nodePtr->getLeft(), newPtr));
	} else if (newPtr->getKey() > nodePtr->getKey()) {
		nodePtr->setRight(_insertBST(nodePtr->getRight(), newPtr));
	} else {
		delete newPtr;
		return nodePtr;
	}
	return nodePtr;
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