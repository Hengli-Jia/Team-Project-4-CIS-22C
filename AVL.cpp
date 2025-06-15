#pragma once
#include "AVL.h"
#include <algorithm>

// Get height of node
template <typename T> int AVL<T>::_getHeight(AVLNode<T> *node) const {
	return node ? node->getHeight() : 0;
}

// Get balance factor
template <typename T> int AVL<T>::_getBalance(AVLNode<T> *node) const {
	if (!node)
		return 0;
	return _getHeight(static_cast<AVLNode<T> *>(node->getLeft())) -
		   _getHeight(static_cast<AVLNode<T> *>(node->getRight()));
}

// Right rotation
template <typename T> AVLNode<T> *AVL<T>::_rotateRight(AVLNode<T> *y) {
	AVLNode<T> *x = static_cast<AVLNode<T> *>(y->getLeft());
	AVLNode<T> *T2 = static_cast<AVLNode<T> *>(x->getRight());
	x->setRight(y);
	y->setLeft(T2);
	y->setHeight(
		std::max(_getHeight(static_cast<AVLNode<T> *>(y->getLeft())),
				 _getHeight(static_cast<AVLNode<T> *>(y->getRight()))) +
		1);
	x->setHeight(
		std::max(_getHeight(static_cast<AVLNode<T> *>(x->getLeft())),
				 _getHeight(static_cast<AVLNode<T> *>(x->getRight()))) +
		1);
	return x;
}

// Left rotation
template <typename T> AVLNode<T> *AVL<T>::_rotateLeft(AVLNode<T> *x) {
	AVLNode<T> *y = static_cast<AVLNode<T> *>(x->getRight());
	AVLNode<T> *T2 = static_cast<AVLNode<T> *>(y->getLeft());
	y->setLeft(x);
	x->setRight(T2);
	x->setHeight(
		std::max(_getHeight(static_cast<AVLNode<T> *>(x->getLeft())),
				 _getHeight(static_cast<AVLNode<T> *>(x->getRight()))) +
		1);
	y->setHeight(
		std::max(_getHeight(static_cast<AVLNode<T> *>(y->getLeft())),
				 _getHeight(static_cast<AVLNode<T> *>(y->getRight()))) +
		1);
	return y;
}

// Insert
template <typename T>
AVLNode<T> *AVL<T>::_insert(AVLNode<T> *node, const T &data) {
	if (!node) {
		++this->count;
		return new AVLNode<T>(data);
	}
	if (data.getKey() < node->getKey()) {
		node->setLeft(
			_insert(static_cast<AVLNode<T> *>(node->getLeft()), data));
	} else if (data.getKey() > node->getKey()) {
		node->setRight(
			_insert(static_cast<AVLNode<T> *>(node->getRight()), data));
	} else {
		return node; // duplicate keys not allowed
	}
	node->setHeight(
		std::max(_getHeight(static_cast<AVLNode<T> *>(node->getLeft())),
				 _getHeight(static_cast<AVLNode<T> *>(node->getRight()))) +
		1);
	int balance = _getBalance(node);
	// Left Left
	if (balance > 1 && data.getKey() < node->getLeft()->getKey())
		return _rotateRight(node);
	// Right Right
	if (balance < -1 && data.getKey() > node->getRight()->getKey())
		return _rotateLeft(node);
	// Left Right
	if (balance > 1 && data.getKey() > node->getLeft()->getKey()) {
		node->setLeft(_rotateLeft(static_cast<AVLNode<T> *>(node->getLeft())));
		return _rotateRight(node);
	}
	// Right Left
	if (balance < -1 && data.getKey() < node->getRight()->getKey()) {
		node->setRight(
			_rotateRight(static_cast<AVLNode<T> *>(node->getRight())));
		return _rotateLeft(node);
	}
	return node;
}

template <typename T> bool AVL<T>::insert(const T &data) {
	this->rootPtr = _insert(static_cast<AVLNode<T> *>(this->rootPtr), data);
	return true;
}

// Remove (with rebalancing)
template <typename T>
AVLNode<T> *AVL<T>::_remove(AVLNode<T> *node, const string &key,
							bool &deleted) {
	if (!node)
		return nullptr;
	if (key < node->getKey()) {
		node->setLeft(
			_remove(static_cast<AVLNode<T> *>(node->getLeft()), key, deleted));
	} else if (key > node->getKey()) {
		node->setRight(
			_remove(static_cast<AVLNode<T> *>(node->getRight()), key, deleted));
	} else {
		deleted = true;
		--this->count;
		if (!node->getLeft() || !node->getRight()) {
			AVLNode<T> *temp =
				node->getLeft() ? static_cast<AVLNode<T> *>(node->getLeft())
								: static_cast<AVLNode<T> *>(node->getRight());
			delete node;
			return temp;
		} else {
			AVLNode<T> *succ = static_cast<AVLNode<T> *>(node->getRight());
			while (succ->getLeft())
				succ = static_cast<AVLNode<T> *>(succ->getLeft());
			node->setKey(succ->getKey());
			node->setRight(_remove(static_cast<AVLNode<T> *>(node->getRight()),
								   succ->getKey(), deleted));
		}
	}
	node->setHeight(
		std::max(_getHeight(static_cast<AVLNode<T> *>(node->getLeft())),
				 _getHeight(static_cast<AVLNode<T> *>(node->getRight()))) +
		1);
	int balance = _getBalance(node);
	// Left Left
	if (balance > 1 &&
		_getBalance(static_cast<AVLNode<T> *>(node->getLeft())) >= 0)
		return _rotateRight(node);
	// Left Right
	if (balance > 1 &&
		_getBalance(static_cast<AVLNode<T> *>(node->getLeft())) < 0) {
		node->setLeft(_rotateLeft(static_cast<AVLNode<T> *>(node->getLeft())));
		return _rotateRight(node);
	}
	// Right Right
	if (balance < -1 &&
		_getBalance(static_cast<AVLNode<T> *>(node->getRight())) <= 0)
		return _rotateLeft(node);
	// Right Left
	if (balance < -1 &&
		_getBalance(static_cast<AVLNode<T> *>(node->getRight())) > 0) {
		node->setRight(
			_rotateRight(static_cast<AVLNode<T> *>(node->getRight())));
		return _rotateLeft(node);
	}
	return node;
}

template <typename T> bool AVL<T>::remove(const string &key) {
	bool deleted = false;
	this->rootPtr =
		_remove(static_cast<AVLNode<T> *>(this->rootPtr), key, deleted);
	return deleted;
}

template <typename T> void AVL<T>::_clear(AVLNode<T> *node) {
	if (node) {
		_clear(static_cast<AVLNode<T> *>(node->getLeft()));
		_clear(static_cast<AVLNode<T> *>(node->getRight()));
		delete node;
	}
}

template <typename T>
void AVL<T>::_inorderTraversal(const function<void(const string &)> &visit,
							   AVLNode<T> *node) const {
	if (node) {
		_inorderTraversal(visit, static_cast<AVLNode<T> *>(node->getLeft()));
		visit(node->getKey());
		_inorderTraversal(visit, static_cast<AVLNode<T> *>(node->getRight()));
	}
}

template <typename T>
void AVL<T>::inorderTraversal(
	const function<void(const string &)> &visit) const {
	_inorderTraversal(visit, static_cast<AVLNode<T> *>(this->rootPtr));
}
