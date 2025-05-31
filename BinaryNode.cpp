# ifndef "BINARYNODE.h"
# define "BINARYNODE.h"

class* BinaryNode {
private:
  int* left;
  int* right;
  int key;
  int index;

public: 
  int* setLeft();
  int* setRight();
  int* getLeft() {return left;}
  int* getRight() { return right;}
  int setKey();
  int getKey() {return key;}
  int setIndex();
  int getIndex() { return index;}

}
