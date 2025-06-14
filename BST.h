#ifndef BST_H
#define BST_H

#include "TreeNode.h"
#include <functional>
#include <string>

class BST {
  private:
	TreeNode *rootPtr = nullptr;
	int count = 0;
	TreeNode *_insert(TreeNode *, TreeNode *);
	bool _delete(const std::string &key, TreeNode *, bool &);
	void
	_inorderTraversal(const std::function<void(const std::string &)> &visit,
					  TreeNode *nodePtr) const;
	void
	_indentedTree(const std::function<void(const std::string &, int)> &visit,
				  TreeNode *nodePtr, int level) const;
	void _clear(TreeNode *node);

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
