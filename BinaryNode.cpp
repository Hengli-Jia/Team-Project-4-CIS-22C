
# include <iostream>
# include "Puzzle.h"

class BinaryNode {
private:
  Puzzle puzzle;
  BinaryNode* left;
  BinaryNode* right;
  string key;
  int index;

public: 
  BinaryNode() { left = right = nullptr; key = ""; index = -1;}
  BinaryNode(BinaryNode* left, BinaryNode* right, int key, int index) { this -> left = left; this -> right = right; this -> key = key; this -> index = index;}

  //not implemeneted
  BinaryNode(const Puzzle& puzzle);
  
  void setLeft(BinaryNode* Ptr) {this -> left = Ptr;}
  void setRight(BinaryNode* Ptr) {this -> right = Ptr;}
  BinaryNode* getLeft() const {return left;}
  BinaryNode* getRight() const { return right;}
  void setKey(int puzzleKey) {this -> key = puzzleKey;}
  string getKey() const {return key;}
  void setIndex(int puzzleIndex) {this -> index = puzzleIndex;}
  int getIndex() { return index;}

  bool isLeaf () { return this -> left == nullptr && this -> right == nullptr;}

};
