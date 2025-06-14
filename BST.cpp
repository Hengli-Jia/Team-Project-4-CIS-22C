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

bool BinaryTree::_deleteBST(BinaryNode* delPtr, BinaryNode * nodePtr) const {
	
	if (!nodePtr) 
		return nodePtr;
	if (delPtr -> getKey() < nodePtr -> getKey()) 
		nodePtr -> getLeft() = _deleteBST(delPtr, nodePtr -> getLeft());
	else if ( delPtr -> getKey() > nodePtr -> getKey())
		nodePtr -> getRight() = _deleteBST(delPtr, nodePtr -> getRight());
	// Found the node
	else {
	//Case 1: Leaf node
	if (nodePtr -> isLeaf()) {
		delete delPtr;
		delete nodePtr;
		return true;
	}
	// Case 2: root with right child only
	if (!nodePtr -> getLeft()) {
		nodePtr = nodePtr -> getRight();
		delete delPtr;
		delete
	}
		

	// Case 3: root with left child only
		
	// Case 4: root with two children

	
	return true;
		}
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
