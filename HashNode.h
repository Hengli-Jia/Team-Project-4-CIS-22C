#ifndef HASHNODE_H
#define HASHNODE_H

#include "puzzle.h"
#include <string>

class HashNode {
  public:
	HashNode() : occupied(0), collisions(0) {}
	HashNode(const Puzzle &anItem) : item(anItem), occupied(1), collisions(0) {}
	HashNode(const Puzzle &anItem, int ocp, int nCol)
		: item(anItem), occupied(ocp), collisions(nCol) {}

	void setItem(const Puzzle &anItem) { item = anItem; }
	void setOccupied(int ocp) { occupied = ocp; }
	void setCollisions(int nCol) { collisions = nCol; }

	Puzzle getItem() const { return item; }
	int getOccupied() const { return occupied; }
	int getCollisions() const { return collisions; }

  private:
	Puzzle item;
	int occupied;	// 1 -> occupied, 0 -> empty, -1 -> deleted
	int collisions; // number of collisions
};

#endif // HASHNODE_H
