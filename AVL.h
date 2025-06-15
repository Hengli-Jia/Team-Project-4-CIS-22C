#ifndef AVL_H
#define AVL_H

#include "BST.h"
#include <algorithm>
#include <functional>
using std::function;
using std::string;

// AVL Node extends BinaryNode to add height
// Alternatively, you can add height to BinaryNode directly if you want

template <typename T> class AVLNode : public BinaryNode<T> {
  private:
	int height;

  public:
	AVLNode(const T &data) : BinaryNode<T>(data), height(1) {}
	AVLNode() : BinaryNode<T>(), height(1) {}
	void setHeight(int h) { height = h; }
	int getHeight() const { return height; }
};

template <typename T> class AVL : public BST<T> {
  protected:
	using BST<T>::rootPtr;
	using BST<T>::count;
	// Helper functions
	AVLNode<T> *_insert(AVLNode<T> *node, const T &data);
	AVLNode<T> *_remove(AVLNode<T> *node, const string &key, bool &deleted);
	AVLNode<T> *_rotateLeft(AVLNode<T> *node);
	AVLNode<T> *_rotateRight(AVLNode<T> *node);
	int _getHeight(AVLNode<T> *node) const;
	int _getBalance(AVLNode<T> *node) const;
	void _clear(AVLNode<T> *node);
	void _inorderTraversal(const function<void(const string &)> &visit,
						   AVLNode<T> *node) const;

  public:
	AVL() = default;
	virtual ~AVL() { this->_clear(static_cast<AVLNode<T> *>(this->rootPtr)); }
	bool insert(const T &data);
	bool remove(const string &key);
	void inorderTraversal(const function<void(const string &)> &visit) const;
	void clear() {
		this->_clear(static_cast<AVLNode<T> *>(this->rootPtr));
		this->rootPtr = nullptr;
		this->count = 0;
	}
};

#include "AVL.cpp"

#endif
