#ifndef BST_H
#define BST_H

#include "BinaryTree.h"
#include <functional>
using std::function;
using std::string;

class BST : public BinaryTree {
  protected:
	BinaryNode *_insert(BinaryNode *, const string &key, int index);
	bool _delete(const string &key, BinaryNode *, bool &);
	void _inorderTraversal(const function<void(const string &, int)> &visit,
						   BinaryNode *nodePtr) const;
	void _indentedTree(const function<void(const string &, int)> &visit,
					   BinaryNode *nodePtr, int level) const;
	void _clear(BinaryNode *node);

  public:
	BST() = default;
	virtual ~BST() { this->_clear(rootPtr); }
	bool insert(const string &key, int index);
	bool remove(const string &key);
	void
	inorderTraversal(const function<void(const string &, int)> &visit) const;
	void indentedTree(const function<void(const string &, int)> &visit) const;
	void clear();
};

#include "BST.cpp"

#endif
