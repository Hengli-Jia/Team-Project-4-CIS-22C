#pragma once
#include "BST.h"

using std::function;
using std::string;

BinaryNode *BST::_insert(BinaryNode *nodePtr, const string &key, int index) {
	if (!nodePtr) {
		++count;
		return new BinaryNode(key, index);
	}
	if (key < nodePtr->getKey()) {
		nodePtr->setLeft(_insert(nodePtr->getLeft(), key, index));
	} else if (key > nodePtr->getKey()) {
		nodePtr->setRight(_insert(nodePtr->getRight(), key, index));
	} else {
		return nodePtr;
	}
	return nodePtr;
}

bool BST::_delete(const string &key, BinaryNode *nodePtr, bool &deleted) {
	if (!nodePtr)
		return false;
	if (key < nodePtr->getKey()) {
		return _delete(key, nodePtr->getLeft(), deleted);
	} else if (key > nodePtr->getKey()) {
		return _delete(key, nodePtr->getRight(), deleted);
	} else {
		deleted = true;
		--count;
		if (nodePtr->isLeaf()) {
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
			BinaryNode *succ = nodePtr->getRight();
			while (succ->getLeft()) {
				succ = succ->getLeft();
			}
			nodePtr->setKey(succ->getKey());
			nodePtr->setIndex(succ->getIndex());
			_delete(succ->getKey(), nodePtr->getRight(), deleted);
		}
		return true;
	}
}

void BST::_inorderTraversal(const function<void(const string &, int)> &visit, BinaryNode *nodePtr) const {
	if (nodePtr) {
		_inorderTraversal(visit, nodePtr->getLeft());
		visit(nodePtr->getKey(), nodePtr->getIndex());
		_inorderTraversal(visit, nodePtr->getRight());
	}
}

void BST::_indentedTree(const function<void(const string &, int)> &visit, BinaryNode *nodePtr, int level) const {
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

bool BST::insert(const string &key, int index) {
	rootPtr = _insert(rootPtr, key, index);
	return true;
}

bool BST::remove(const string &key) {
	bool deleted = false;
	_delete(key, rootPtr, deleted);
	return deleted;
}

int BST::search(const std::string &key) const {
	BinaryNode *curr = getRoot();
	while (curr) {
		if (key == curr->getKey())
			return curr->getIndex();
		else if (key < curr->getKey())
			curr = curr->getLeft();
		else
			curr = curr->getRight();
	}
	return -1;
int BST::search(const std::string& key) const {
    return _search(getRoot(), key);
}

void BST::inorderTraversal(const function<void(const string &, int)> &visit) const {
	_inorderTraversal(visit, rootPtr);
}

void BST::indentedTree(const function<void(const string &, int)> &visit) const { _indentedTree(visit, rootPtr, 0); }

void BST::clear() {
	_clear(rootPtr);
	rootPtr = nullptr;
	count = 0;
}
