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

bool BinaryTree::_deleteBST(BinaryNode * delPtr, BinaryNode * nodePtr) const {
	BinaryNode* parent = nullptr;
	// Empty tree
	if (!nodePtr) 
		return false;
	
	while (nodePtr) {
	if (delPtr -> getKey() < nodePtr -> getKey()) 
		parent = nodePtr;
		nodePtr = nodePtr -> getLeft();
	else if ( delPtr -> getKey() > nodePtr -> getKey())
		parent = nodePtr;
		nodePtr = nodePtr -> getRight();
	
	// Found the node
	else {
	//Case 1: Leaf node		
	if (nodePtr -> isLeaf()) {
		if (!parent)
			this -> rootPtr = nullptr;
		else if (nodePtr -> getLeft () -> getKey() == delPtr -> getKey())
			parent -> getLeft() = nullptr;
		else
			parent -> getRight() = nullptr;	
	}
	// Case 2: node with right child only
	if (!nodePtr -> getLeft()) {
		if (!parent)
			this -> rootPtr -> getRight() = nodePtr -> getRight();
		else if (nodePtr -> getLeft() ->  getKey() == delPtr -> getKey())
			parent -> getLeft() = nodePtr -> getLeft();
		else
			parent -> getRight() = nodePtr -> getRight();
	}	
	// Case 3: node with left child only
	else if (!nodePtr -> getRight()) {
		if (!parent)
			this -> rootPtr -> getLeft() = nodePtr -> getLeft();
		else if (nodePtr -> getLeft() ->  getKey() == delPtr -> getKey())
			parent -> getLeft() = nodePtr -> getLeft();
		else
			parent -> getRight() = nodePtr -> getRight();
	}	
	// Case 4: node with two children
	else {
		BinaryNode* successor = nodePtr -> getRight();
		while (successor -> getLeft()) {
			successor = successor -> getLeft();	
		}
			nodePtr -> getKey() = successor -> getKey();
			parent = nodePtr;
	}

	
	return true;
		}
	}
	return false; // Node not found
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
