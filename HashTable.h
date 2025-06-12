#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include <string>

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
	bool insert(const Puzzle &item);
	// Remove a Puzzle item by key, output the removed item
	bool remove(Puzzle &itemOut, const std::string &key);
	// Search for a Puzzle item by key, output the found item
	bool search(Puzzle &itemOut, const std::string &key) const;

	// Add accessors for saving to file
	int getOccupiedAt(int idx) const { return table[idx].getOccupied(); }
	Puzzle getItemAt(int idx) const { return table[idx].getItem(); }

  private:
	HashNode *table; // Pointer to the array of hash nodes
	int size;		 // Number of items in the table
	int capacity;	 // Size of the table

	// Hash function for string keys
	int hashFunction(const std::string &key) const;
	// Linear probing for collision resolution
	int linearProbe(int hashcode) const;
	// Rehash the table when load factor is too high
	void rehash();
};

#endif // HASHTABLE_H
