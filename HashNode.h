#ifndef HASHNODE_H
#define HASHNODE_H

#include <string>

// HashNode definition
template <typename T> class HashNode {
  private:
	T item = T();
	int occupied;	// 1 -> occupied, 0 -> empty, -1 -> deleted
	int collisions; // number of collisions
  public:
	HashNode() : occupied(0), collisions(0) {}
	HashNode(const T &anItem) : item(anItem), occupied(1), collisions(0) {}
	HashNode(const T &anItem, int ocp, int nCol)
		: item(anItem), occupied(ocp), collisions(nCol) {}

	void setItem(const T &anItem) { item = anItem; }
	void setOccupied(int ocp) { occupied = ocp; }
	void setCollisions(int nCol) { collisions = nCol; }

	T getItem() const { return item; }
	int getOccupied() const { return occupied; }
	int getCollisions() const { return collisions; }
};

#endif // HASHNODE_H
