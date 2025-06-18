#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <string>
using std::string;

class BinaryNode {
  private:
	string key;
	int index;
	BinaryNode *left;
	BinaryNode *right;

  public:
	BinaryNode() : key(""), index(-1), left(nullptr), right(nullptr) {}
	BinaryNode(const string &key, int index)
		: key(key), index(index), left(nullptr), right(nullptr) {}
	BinaryNode(BinaryNode *left, BinaryNode *right, string key, int index)
		: key(key), index(index), left(left), right(right) {}

	void setLeft(BinaryNode *Ptr) { this->left = Ptr; }
	void setRight(BinaryNode *Ptr) { this->right = Ptr; }
	BinaryNode *getLeft() const { return left; }
	BinaryNode *getRight() const { return right; }
	void setKey(string k) { this->key = k; }
	string getKey() const { return key; }
	void setIndex(int idx) { this->index = idx; }
	int getIndex() const { return index; }
	bool isLeaf() { return this->left == nullptr && this->right == nullptr; }
};

#endif
