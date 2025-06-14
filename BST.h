#ifndef BST_H
#define BST_H

#include "BinaryTree.cpp"
#include <functional>

template <typename T> class BST {
  private:
	BinaryNode<T> *rootPtr = nullptr;
	int count = 0;
	BinaryNode<T> *_insert(BinaryNode<T> *, BinaryNode<T> *);
	bool _delete(const std::string &key, BinaryNode<T> *, bool &);
	void
	_inorderTraversal(const std::function<void(const std::string &)> &visit,
					  BinaryNode<T> *nodePtr) const;
	void
	_indentedTree(const std::function<void(const std::string &, int)> &visit,
				  BinaryNode<T> *nodePtr, int level) const;
	void _clear(BinaryNode<T> *node);

  public:
	BST() = default;
	~BST() { _clear(rootPtr); }
	bool isEmpty() const { return count == 0; }
	int getCount() const { return count; }
	bool insert(const T &inputData);
	bool remove(const std::string &key);
	void inorderTraversal(
		const std::function<void(const std::string &)> &visit) const;
	void indentedTree(
		const std::function<void(const std::string &, int)> &visit) const;
	void clear();
};

#include "BST.cpp"

#endif
