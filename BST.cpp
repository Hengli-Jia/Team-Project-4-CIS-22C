#include "BST.h"

#include <iostream>
#include <string>

BinaryNode *BinaryTree::_insertBST(BinaryNode *nodePtr, BinaryNode *newPtr) {
	std::cout << "[DEBUG] Inserting: " << newPtr->getKey() << std::endl;
	if (!nodePtr) {
		std::cout << "[DEBUG] Inserted at empty node." << std::endl;
		this->count++;
		return newPtr;
	}
	if (newPtr->getKey() < nodePtr->getKey()) {
		std::cout << "[DEBUG] Going left from node with key: "
				  << nodePtr->getKey() << std::endl;
		nodePtr->setLeft(_insertBST(nodePtr->getLeft(), newPtr));
	} else {
		std::cout << "[DEBUG] Going right from node with key: "
				  << nodePtr->getKey() << std::endl;
		nodePtr->setRight(_insertBST(nodePtr->getRight(), newPtr));
	}
	std::cout << "[DEBUG] Inserted: " << newPtr->getKey()
			  << " at node with key: " << nodePtr->getKey() << std::endl;
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