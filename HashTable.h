#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"

using std::string;

const int DEFAULT_HASH_SIZE = 53;

// HashTable definition
template <typename T>
class HashTable {
  private:
	HashNode<T> *table; // Pointer to the array of hash nodes
	int size;			// Number of items in the table
	int capacity;		// Size of the table

	// Hash function for string keys
	int hashFunction(const string &key) const;
	// Linear probing for collision resolution
	int linearProbe(int hashcode) const;
	// Rehash the table when load factor is too high
	void rehash();
	bool isFull() const { return size == capacity; }
	// Helper to find next prime number >= n
	

  public:
	// Constructor: initializes the hash table with a given capacity
	HashTable(int initialCapacity = 53);
	// Destructor: releases allocated memory
	~HashTable();

	int getSize() const { return size; }
	int getCapacity() const { return capacity; }
	double getLoadFactor() const { return 100.0 * size / capacity; }
	bool isEmpty() const { return size == 0; }
	int nextPrime(int n) const;
	bool isPrime(int n) const;

	// Insert an item into the hash table
	// Returns the index where the item was inserted, or -1 if duplicate or
	// error
	int insert(const T &item);
	// Remove an item by key, output the removed item
	bool remove(T &itemOut, const string &key);
	// Search for an item by key, output the found item
	bool search(T &itemOut, const string &key) const;

	// Add accessors for saving to file
	int getOccupiedAt(int idx) const { return table[idx].getOccupied(); }
	T getItemAt(int idx) const { return table[idx].getItem(); }
	int getCollisionsAt(int idx) const { return table[idx].getCollisions(); }
};

#include "HashTable.cpp"

#endif
