#include "BST.h"

BinaryNode *BST::_insert(BinaryNode *nodePtr, BinaryNode *newPtr) {
	if (!nodePtr) {
		++count;
		return newPtr;
	}
	if (newPtr->getKey() < nodePtr->getKey()) {
		nodePtr->setLeft(_insert(nodePtr->getLeft(), newPtr));
	} else if (newPtr->getKey() > nodePtr->getKey()) {
		nodePtr->setRight(_insert(nodePtr->getRight(), newPtr));
	} else {
		delete newPtr;
		return nodePtr;
	}
	return nodePtr;
}

bool BST::_delete(const std::string &key, BinaryNode *nodePtr, bool &deleted) {
	if (!nodePtr)
		return false;
	if (key < nodePtr->getKey()) {
		return _delete(key, nodePtr->getLeft(), deleted);
	} else if (key > nodePtr->getKey()) {
		return _delete(key, nodePtr->getRight(), deleted);
	} else {
		// Node found
		deleted = true;
		--count;
		if (!nodePtr->getLeft() && !nodePtr->getRight()) {
			delete nodePtr;
			nodePtr = nullptr;
		} else if (!nodePtr->getLeft()) {
			BinaryNode *temp = nodePtr;
			nodePtr = nodePtr->getRight();
			delete temp;
		} else if (!nodePtr->getRight()) {
			BinaryNode *temp = nodePtr;
			nodePtr = nodePtr->getLeft();
			delete temp;
		} else {
			// Two children: find inorder successor
			BinaryNode *succParent = nodePtr;
			BinaryNode *succ = nodePtr->getRight();
			while (succ->getLeft()) {
				succParent = succ;
				succ = succ->getLeft();
			}
			nodePtr->setKey(succ->getKey());
			_delete(succ->getKey(), nodePtr->getRight(), deleted);
		}
		return true;
	}
}

void BST::_inorderTraversal(
	const std::function<void(const std::string &)> &visit,
	BinaryNode *nodePtr) const {
	if (nodePtr) {
		_inorderTraversal(visit, nodePtr->getLeft());
		visit(nodePtr->getKey());
		_inorderTraversal(visit, nodePtr->getRight());
	}
}

void BST::_indentedTree(
	const std::function<void(const std::string &, int)> &visit,
	BinaryNode *nodePtr, int level) const {
	if (nodePtr) {
		_indentedTree(visit, nodePtr->getRight(), level + 1);
		visit(nodePtr->getKey(), level);
		_indentedTree(visit, nodePtr->getLeft(), level + 1);
	}
}

void BST::_clear(BinaryNode *node) {
	if (node) {
		_clear(node->getLeft());
		_clear(node->getRight());
		delete node;
	}
}

bool BST::insert(const Puzzle &inputPuzzle) {
	BinaryNode *newNode = new BinaryNode(inputPuzzle);
	rootPtr = _insert(rootPtr, newNode);
	return true;
}

bool BST::remove(const std::string &key) {
	bool deleted = false;
	_delete(key, rootPtr, deleted);
	return deleted;
}

void BST::inorderTraversal(
	const std::function<void(const std::string &)> &visit) const {
	_inorderTraversal(visit, rootPtr);
}

void BST::indentedTree(
	const std::function<void(const std::string &, int)> &visit) const {
	_indentedTree(visit, rootPtr, 0);
}

void BST::clear() {
	_clear(rootPtr);
	rootPtr = nullptr;
	count = 0;
}
