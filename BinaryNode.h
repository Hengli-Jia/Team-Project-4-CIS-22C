#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <string>
using std::string;

template <typename T> class BinaryNode {
  private:
	T data;
	BinaryNode<T> *left;
	BinaryNode<T> *right;
	string key;
	int index;

  public:
	BinaryNode() : left(nullptr), right(nullptr), key(""), index(-1) {}
	BinaryNode(BinaryNode<T> *left, BinaryNode<T> *right, string key, int index)
		: left(left), right(right), key(key), index(index) {}
	BinaryNode(const T &data)
		: data(data), left(nullptr), right(nullptr), key(data.getKey()),
		  index(-1) {}

	void setLeft(BinaryNode<T> *Ptr) { this->left = Ptr; }
	void setRight(BinaryNode<T> *Ptr) { this->right = Ptr; }
	BinaryNode<T> *getLeft() const { return left; }
	BinaryNode<T> *getRight() const { return right; }
	void setKey(string k) { this->key = k; }
	string getKey() const { return key; }
	void setIndex(int idx) { this->index = idx; }
	int getIndex() { return index; }
	T &getData() { return data; }
	const T &getData() const { return data; }
	bool isLeaf() { return this->left == nullptr && this->right == nullptr; }
};

#endif // BINARYNODE_H
