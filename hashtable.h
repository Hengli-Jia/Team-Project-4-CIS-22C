// hashtable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "puzzle.h"
#include <vector>
#include <functional>
#include <string>

// HashNode definition
class HashNode {
public:
    HashNode() : occupied(0), collisions(0) {}
    HashNode(const Puzzle& anItem) : item(anItem), occupied(0), collisions(0) {}
    HashNode(const Puzzle& anItem, int ocp, int nCol)
        : item(anItem), occupied(ocp), collisions(nCol) {}

    void setItem(const Puzzle& anItem) { item = anItem; }
    void setOccupied(int ocp) { occupied = ocp; }
    void setCollisions(int nCol) { collisions = nCol; }

    Puzzle getItem() const { return item; }
    int getOccupied() const { return occupied; }
    int getCollisions() const { return collisions; }

private:
    Puzzle item;
    int occupied;   // 1 -> occupied, 0 -> empty 
    int collisions; // number of collisions
};

class HashTable {
public:
    HashTable(int initialCapacity = 10);

    bool insert(const HashNode& node);
    bool search(HashNode& node, const std::string& key);
    bool remove(HashNode& node, const std::string& key);

private:
    std::vector<HashNode> table; 
    int size;     
    int capacity;
    int collisionCount;
    int longestCollisionPath;

    int hashFunction(const std::string& key) const;
    int linearProbe(int hashcode) const;
    void rehash();
};

#endif // HASHTABLE_H
