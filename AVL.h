#ifndef AVL_H
#define AVL_H

#include "BST.h"
#include <algorithm>
#include <functional>
using std::function;
using std::string;

class AVLNode : public BinaryNode {
  private:
	int height;

  public:
	AVLNode(const string &key, int index) : BinaryNode(key, index), height(1) {}
	AVLNode() : BinaryNode(), height(1) {}
	void setHeight(int h) { height = h; }
	int getHeight() const { return height; }
};

class AVL : public BST {
  protected:
	AVLNode *_insert(AVLNode *node, const string &key, int index);
	AVLNode *_remove(AVLNode *node, const string &key, bool &deleted);
	AVLNode *_rotateLeft(AVLNode *node);
	AVLNode *_rotateRight(AVLNode *node);
	int _getHeight(AVLNode *node) const;
	int _getBalance(AVLNode *node) const;
	void _clear(AVLNode *node);
	void _inorderTraversal(const function<void(const string &, int)> &visit,
						   AVLNode *node) const;

  public:
	AVL() = default;
	virtual ~AVL() { this->_clear(static_cast<AVLNode *>(this->rootPtr)); }
	bool insert(const string &key, int index);
	bool remove(const string &key);
	void
	inorderTraversal(const function<void(const string &, int)> &visit) const;
	void clear() {
		this->_clear(static_cast<AVLNode *>(this->rootPtr));
		this->rootPtr = nullptr;
		this->count = 0;
	}
};

#include "AVL.cpp"

#endif
