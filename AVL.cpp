#pragma once
#include "AVL.h"
#include <algorithm>

int AVL::_getHeight(AVLNode *node) const { return node ? node->getHeight() : 0; }

int AVL::_getBalance(AVLNode *node) const {
	if (!node)
		return 0;
	return _getHeight(static_cast<AVLNode *>(node->getLeft())) - _getHeight(static_cast<AVLNode *>(node->getRight()));
}

AVLNode *AVL::_rotateRight(AVLNode *y) {
	AVLNode *x = static_cast<AVLNode *>(y->getLeft());
	AVLNode *T2 = static_cast<AVLNode *>(x->getRight());
	x->setRight(y);
	y->setLeft(T2);
	y->setHeight(
		std::max(_getHeight(static_cast<AVLNode *>(y->getLeft())), _getHeight(static_cast<AVLNode *>(y->getRight()))) +
		1);
	x->setHeight(
		std::max(_getHeight(static_cast<AVLNode *>(x->getLeft())), _getHeight(static_cast<AVLNode *>(x->getRight()))) +
		1);
	return x;
}

AVLNode *AVL::_rotateLeft(AVLNode *x) {
	AVLNode *y = static_cast<AVLNode *>(x->getRight());
	AVLNode *T2 = static_cast<AVLNode *>(y->getLeft());
	y->setLeft(x);
	x->setRight(T2);
	x->setHeight(
		std::max(_getHeight(static_cast<AVLNode *>(x->getLeft())), _getHeight(static_cast<AVLNode *>(x->getRight()))) +
		1);
	y->setHeight(
		std::max(_getHeight(static_cast<AVLNode *>(y->getLeft())), _getHeight(static_cast<AVLNode *>(y->getRight()))) +
		1);
	return y;
}

// Insert
// node: current node, key: puzzle key, index: hash table index
// Returns new root after insertion

AVLNode *AVL::_insert(AVLNode *node, const string &key, int index) {
	if (!node) {
		++this->count;
		return new AVLNode(key, index);
	}
	if (key < node->getKey()) {
		node->setLeft(_insert(static_cast<AVLNode *>(node->getLeft()), key, index));
	} else if (key > node->getKey()) {
		node->setRight(_insert(static_cast<AVLNode *>(node->getRight()), key, index));
	} else {
		return node;
	}
	node->setHeight(std::max(_getHeight(static_cast<AVLNode *>(node->getLeft())),
							 _getHeight(static_cast<AVLNode *>(node->getRight()))) +
					1);
	int balance = _getBalance(node);
	// Left Left
	if (balance > 1 && key < node->getLeft()->getKey())
		return _rotateRight(node);
	// Right Right
	if (balance < -1 && key > node->getRight()->getKey())
		return _rotateLeft(node);
	// Left Right
	if (balance > 1 && key > node->getLeft()->getKey()) {
		node->setLeft(_rotateLeft(static_cast<AVLNode *>(node->getLeft())));
		return _rotateRight(node);
	}
	// Right Left
	if (balance < -1 && key < node->getRight()->getKey()) {
		node->setRight(_rotateRight(static_cast<AVLNode *>(node->getRight())));
		return _rotateLeft(node);
	}
	return node;
}

bool AVL::insert(const string &key, int index) {
	this->rootPtr = _insert(static_cast<AVLNode *>(this->rootPtr), key, index);
	return true;
}

// Remove (with rebalancing)
AVLNode *AVL::_remove(AVLNode *node, const string &key, bool &deleted) {
	if (!node)
		return nullptr;
	if (key < node->getKey()) {
		node->setLeft(_remove(static_cast<AVLNode *>(node->getLeft()), key, deleted));
	} else if (key > node->getKey()) {
		node->setRight(_remove(static_cast<AVLNode *>(node->getRight()), key, deleted));
	} else {
		deleted = true;
		if (!node->getLeft() || !node->getRight()) {
			AVLNode *temp =
				node->getLeft() ? static_cast<AVLNode *>(node->getLeft()) : static_cast<AVLNode *>(node->getRight());
			if (!temp) {
				temp = node;
				node = nullptr;
			} else {
				*node = *temp;
			}
			delete temp;
			--this->count;
		} else {
			AVLNode *succ = static_cast<AVLNode *>(node->getRight());
			while (succ->getLeft()) {
				succ = static_cast<AVLNode *>(succ->getLeft());
			}
			node->setKey(succ->getKey());
			node->setIndex(succ->getIndex());
			node->setRight(_remove(static_cast<AVLNode *>(node->getRight()), succ->getKey(), deleted));
		}
	}
	if (!node)
		return node;
	node->setHeight(std::max(_getHeight(static_cast<AVLNode *>(node->getLeft())),
							 _getHeight(static_cast<AVLNode *>(node->getRight()))) +
					1);
	int balance = _getBalance(node);
	// Left Left
	if (balance > 1 && _getBalance(static_cast<AVLNode *>(node->getLeft())) >= 0)
		return _rotateRight(node);
	// Left Right
	if (balance > 1 && _getBalance(static_cast<AVLNode *>(node->getLeft())) < 0) {
		node->setLeft(_rotateLeft(static_cast<AVLNode *>(node->getLeft())));
		return _rotateRight(node);
	}
	// Right Right
	if (balance < -1 && _getBalance(static_cast<AVLNode *>(node->getRight())) <= 0)
		return _rotateLeft(node);
	// Right Left
	if (balance < -1 && _getBalance(static_cast<AVLNode *>(node->getRight())) > 0) {
		node->setRight(_rotateRight(static_cast<AVLNode *>(node->getRight())));
		return _rotateLeft(node);
	}
	return node;
}

bool AVL::remove(const string &key) {
	bool deleted = false;
	this->rootPtr = _remove(static_cast<AVLNode *>(this->rootPtr), key, deleted);
	return deleted;
}

void AVL::_clear(AVLNode *node) {
	if (node) {
		_clear(static_cast<AVLNode *>(node->getLeft()));
		_clear(static_cast<AVLNode *>(node->getRight()));
		delete node;
	}
}

void AVL::_inorderTraversal(const function<void(const string &, int)> &visit, AVLNode *node) const {
	if (node) {
		_inorderTraversal(visit, static_cast<AVLNode *>(node->getLeft()));
		visit(node->getKey(), node->getIndex());
		_inorderTraversal(visit, static_cast<AVLNode *>(node->getRight()));
	}
}

void AVL::inorderTraversal(const function<void(const string &, int)> &visit) const {
	_inorderTraversal(visit, static_cast<AVLNode *>(this->rootPtr));
}
