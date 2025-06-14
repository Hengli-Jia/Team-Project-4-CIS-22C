#ifndef TREENODE_H
#define TREENODE_H

#include "Puzzle.h"

class TreeNode {
  private:
	Puzzle puzzle;
	TreeNode *left;
	TreeNode *right;
	string key;
	int index;

  public:
	TreeNode() {
		left = right = nullptr;
		key = "";
		index = -1;
	}
	TreeNode(TreeNode *left, TreeNode *right, string key, int index) {
		this->left = left;
		this->right = right;
		this->key = key;
		this->index = index;
	}
	TreeNode(const Puzzle &puzzle);

	void setLeft(TreeNode *Ptr) { this->left = Ptr; }
	void setRight(TreeNode *Ptr) { this->right = Ptr; }
	TreeNode *getLeft() const { return left; }
	TreeNode *getRight() const { return right; }
	void setKey(string puzzleKey) { this->key = puzzleKey; }
	string getKey() const { return key; }
	void setIndex(int puzzleIndex) { this->index = puzzleIndex; }
	int getIndex() { return index; }

	bool isLeaf() { return this->left == nullptr && this->right == nullptr; }
};

TreeNode::TreeNode(const Puzzle &puzzle) {
	this->puzzle = puzzle;
	this->key = puzzle.puzzleId();
	this->left = nullptr;
	this->right = nullptr;
	this->index = -1;
}

#endif
