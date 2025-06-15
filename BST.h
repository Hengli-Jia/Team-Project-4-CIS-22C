#ifndef BST_H
#define BST_H

#include "BinaryTree.h"
#include <functional>
using std::function;
using std::string;

template <typename T> class BST : public BinaryTree<T> {
  protected:
	using BinaryTree<T>::rootPtr;
	using BinaryTree<T>::count;
	BinaryNode<T> *_insert(BinaryNode<T> *, BinaryNode<T> *);
	bool _delete(const string &key, BinaryNode<T> *, bool &);
	void _inorderTraversal(const function<void(const string &)> &visit,
						   BinaryNode<T> *nodePtr) const;
	void _indentedTree(const function<void(const string &, int)> &visit,
					   BinaryNode<T> *nodePtr, int level) const;
	void _clear(BinaryNode<T> *node);

  public:
	BST() = default;
	virtual ~BST() { this->_clear(rootPtr); }
	bool insert(const T &inputData);
	bool remove(const string &key);
	void inorderTraversal(const function<void(const string &)> &visit) const;
	void indentedTree(const function<void(const string &, int)> &visit) const;
	void clear();
};

#include "BST.cpp"

#endif
