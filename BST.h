#ifndef BST_H
#define BST_H

#include "BinaryNode.h"
#include <functional>
#include <string>

class BST {
  private:
	BinaryNode *rootPtr = nullptr;
	int count = 0;
	BinaryNode *_insert(BinaryNode *, BinaryNode *);
	bool _delete(const std::string &key, BinaryNode *, bool &);
	void
	_inorderTraversal(const std::function<void(const std::string &)> &visit,
					  BinaryNode *nodePtr) const;
	void
	_indentedTree(const std::function<void(const std::string &, int)> &visit,
				  BinaryNode *nodePtr, int level) const;
	void _clear(BinaryNode *node);

  public:
	BST() = default;
	~BST() { _clear(rootPtr); }
	bool isEmpty() const { return count == 0; }
	int getCount() const { return count; }
	bool insert(const Puzzle &inputPuzzle);
	bool remove(const std::string &key);
	void inorderTraversal(
		const std::function<void(const std::string &)> &visit) const;
	void indentedTree(
		const std::function<void(const std::string &, int)> &visit) const;
	void clear();
};

#endif
