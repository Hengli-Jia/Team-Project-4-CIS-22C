
# include <iostream>
# include "Puzzle.h"

class* BinaryNode {
private:
  Puzzle puzzle;
  int* left;
  int* right;
  int key;
  int index;

public: 
  BinaryNode() { left = right = nullptr; key = -1, index = -1};
  BinarNodde (left, right, key, index) { this -> left = leftl; this -> right = right; this -> key = key; this -> index = index;}
  
  int* setLeft(BinaryNode* Ptr) {this -> left = Ptr;}
  int* setRight(BinaryNode* Ptr) {this -> right = Ptr;}
  int* getLeft() {return left;}
  int* getRight() { return right;}
  int setKey(const& Puzzle puzzle) {puzzle -> key = key;}
  int getKey() {return key;}
  int setIndex(const& Puzzle puzzle) {puzzle -> index = index;}
  int getIndex() { return index;}

  bool isLeaf () { return this -> left == nullptr && this -> right = nullptr;}

}
