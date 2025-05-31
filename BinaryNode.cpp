# ifndef "BINARYNODE.h"
# define "BINARYNODE.h"

class* BinaryNode {
private:
  int* left;
  int* right;
  int key;
  int index;

public: 
  BinaryNode() { left = right = nullptr; key = -1, index = -1};
  BinarNodde (left, right, key, index) { this -> left = leftl; this -> right = right; this -> key = key; this -> index = index;}
  
int* setLeft(BinaryNode* Ptr) {this -> left = Ptr;}
  int* setRight(BinaryNode* Ptr) {this -> left = Ptr;}
  int* getLeft() {return left;}
  int* getRight() { return right;}
  int setKey(const& Puzzle puzzle) {puzzle -> key = key;}
  int getKey() {return key;}
  int setIndex(const& Puzzle puzzle) {puzzle -> index = index;}
  int getIndex() { return index;}

}
