#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "puzzle.h"
#include <string>

// HashNode definition
class HashNode {
public:
    HashNode() : occupied(0), collisions(0) {}
    HashNode(const Puzzle& anItem) : item(anItem), occupied(1), collisions(0) {}
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
    int occupied;   // 1 -> occupied, 0 -> empty, -1 -> deleted
    int collisions; // number of collisions
};

// HashTable definition
class HashTable {
public:
    // Constructor: initializes the hash table with a given capacity
    HashTable(int initialCapacity = 50);
    // Destructor: releases allocated memory
    ~HashTable();

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    double getLoadFactor() const { return 100.0 * size / capacity; }
    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }

    // Insert a Puzzle item into the hash table
    bool insert(const Puzzle& item);
    // Remove a Puzzle item by key, output the removed item
    bool remove(Puzzle& itemOut, const std::string& key);
    // Search for a Puzzle item by key, output the found item
    bool search(Puzzle& itemOut, const std::string& key) const;

private:
    HashNode* table;   // Pointer to the array of hash nodes
    int size;          // Number of items in the table
    int capacity;      // Size of the table

    // Hash function for string keys
    int hashFunction(const std::string& key) const;
    // Linear probing for collision resolution
    int linearProbe(int hashcode) const;
    // Rehash the table when load factor is too high
    void rehash();
};

#endif // HASHTABLE_H
