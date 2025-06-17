#pragma once
#include "BST.h"

using std::function;
using std::string;

template <typename T>
BinaryNode<T> *BST<T>::_insert(BinaryNode<T> *nodePtr, BinaryNode<T> *newPtr) {
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

template <typename T>
bool BST<T>::_delete(const string &key, BinaryNode<T> *nodePtr, bool &deleted) {
	if (!nodePtr)
		return false;
	if (key < nodePtr->getKey()) {
		return _delete(key, nodePtr->getLeft(), deleted);
	} else if (key > nodePtr->getKey()) {
		return _delete(key, nodePtr->getRight(), deleted);
	} else {
		deleted = true;
		--count;
		if (!nodePtr->getLeft() && !nodePtr->getRight()) {
			delete nodePtr;
			nodePtr = nullptr;
		} else if (!nodePtr->getLeft()) {
			BinaryNode<T> *temp = nodePtr;
			nodePtr = nodePtr->getRight();
			delete temp;
		} else if (!nodePtr->getRight()) {
			BinaryNode<T> *temp = nodePtr;
			nodePtr = nodePtr->getLeft();
			delete temp;
		} else {
			BinaryNode<T> *succ = nodePtr->getRight();
			while (succ->getLeft()) {
				succ = succ->getLeft();
			}
			nodePtr->setKey(succ->getKey());
			_delete(succ->getKey(), nodePtr->getRight(), deleted);
		}
		return true;
	}
}

template <typename T>
void BST<T>::_inorderTraversal(const function<void(const string &)> &visit,
							   BinaryNode<T> *nodePtr) const {
	if (nodePtr) {
		_inorderTraversal(visit, nodePtr->getLeft());
		visit(nodePtr->getKey());
		_inorderTraversal(visit, nodePtr->getRight());
	}
}

template <typename T>
void BST<T>::_indentedTree(const function<void(const string &, int)> &visit,
						   BinaryNode<T> *nodePtr, int level) const {
	if (nodePtr) {
		_indentedTree(visit, nodePtr->getRight(), level + 1);
		visit(nodePtr->getKey(), level);
		_indentedTree(visit, nodePtr->getLeft(), level + 1);
	}
}

template <typename T> 
void BST<T>::_clear(BinaryNode<T> *node) {
	if (node) {
		_clear(node->getLeft());
		_clear(node->getRight());
		delete node;
	}
}

template <typename T> 
bool BST<T>::insert(const T &inputData) {
	BinaryNode<T> *newNode = new BinaryNode<T>(inputData);
	rootPtr = _insert(rootPtr, newNode);
	return true;
}

template <typename T> 
bool BST<T>::remove(const string &key) {
	bool deleted = false;
	_delete(key, rootPtr, deleted);
	return deleted;
}

template <typename T>
void BST<T>::inorderTraversal(
	const function<void(const string &)> &visit) const {
	_inorderTraversal(visit, rootPtr);
}

template <typename T>
void BST<T>::indentedTree(
	const function<void(const string &, int)> &visit) const {
	_indentedTree(visit, rootPtr, 0);
}

template <typename T> 
void BST<T>::clear() {
	_clear(rootPtr);
	rootPtr = nullptr;
	count = 0;
}
