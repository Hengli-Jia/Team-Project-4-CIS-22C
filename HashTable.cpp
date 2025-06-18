#pragma once
#include "HashTable.h"

#include <cmath> // Include cmath for sqrt function
#include <cstdint>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

// Constructor: initializes the hash table with a given capacity
template <typename T>
HashTable<T>::HashTable(int initialCapacity) {
	capacity = initialCapacity;
	size = 0;
	table = new HashNode<T>[capacity];
}

// Destructor: releases allocated memory
template <typename T>
HashTable<T>::~HashTable() {
	delete[] table;
}

// Improved hash function for string keys using the FNV-1a algorithm
// This provides better distribution for typical string keys (like puzzle IDs)
template <typename T>
int HashTable<T>::hashFunction(const string &key) const {
	const uint64_t fnv_offset_basis = 14695981039346656037ULL;
	const uint64_t fnv_prime = 1099511628211ULL;
	uint64_t hash = fnv_offset_basis;
	for (unsigned char c : key) {
		hash ^= c;
		hash *= fnv_prime;
	}
	return static_cast<int>(hash % capacity);
}

// Linear probing for collision resolution
template <typename T>
int HashTable<T>::linearProbe(int hashcode) const {
	return (hashcode + 1) % capacity;
}

template <typename T>
bool HashTable<T>::isPrime(int n) const {
	if (n <= 1)
		return false;
	if (n <= 3)
		return true;
	if (n % 2 == 0 || n % 3 == 0)
		return false;
	if (n % 5 == 0 && n != 5)
		return false;
	if (n % 7 == 0 && n != 7)
		return false;
	int limit = static_cast<int>(sqrt(n)) + 1;
	for (int i = 11; i <= limit; i += 2) {
		if (n % i == 0)
			return false;
	}
	return true;
}

// Find next prime >= n
template <typename T>
int HashTable<T>::nextPrime(int n) const {
	if (n <= 2)
		return 2;
	if (n % 2 == 0)
		++n;
	while (!isPrime(n))
		n += 2;
	return n;
}

// Insert a Puzzle item into the hash table
// Returns the index where the item was inserted, or -1 if duplicate or error
template <typename T>
int HashTable<T>::insert(const T &item) {
	// Rehash if load factor >= 75%
	if (getLoadFactor() >= 75.0) {
		rehash();
	}
	string key = item.getKey();
	int index = hashFunction(key);
	int collisions = 0;

	for (int i = 0; i < capacity; ++i) {
		int currentIndex = (index + i) % capacity;
		if (currentIndex < 0 || currentIndex >= capacity) {
			cerr << "[ERROR] Out-of-bounds index: " << currentIndex << " (capacity: " << capacity << ")" << endl;
			abort();
		}
		if (table[currentIndex].getOccupied() != 1) {
			table[currentIndex].setItem(item);
			table[currentIndex].setOccupied(1);
			table[currentIndex].setCollisions(collisions);
			size++;
			return currentIndex;
		}
		// If duplicate key, do not insert
		if (table[currentIndex].getOccupied() == 1 && table[currentIndex].getItem().getKey() == key) {
			return -1;
		}
		collisions++;
	}
	return -1;
}

// Remove a Puzzle item by key, output the removed item
template <typename T>
bool HashTable<T>::remove(T &itemOut, const string &key) {
	int index = hashFunction(key);

	for (int i = 0; i < capacity; ++i) {
		int currentIndex = (index + i) % capacity;
		if (table[currentIndex].getOccupied() == 1 && table[currentIndex].getItem().getKey() == key) {
			itemOut = table[currentIndex].getItem();
			table[currentIndex].setOccupied(-1); // Mark as deleted
			size--;
			return true;
		} else if (table[currentIndex].getOccupied() == 0) {
			break; // Stop if an empty slot is found
		}
	}
	return false;
}

// Search for a Puzzle item by key, output the found item
template <typename T>
bool HashTable<T>::search(T &itemOut, const string &key) const {
	int index = hashFunction(key);

	for (int i = 0; i < capacity; ++i) {
		int currentIndex = (index + i) % capacity;
		if (table[currentIndex].getOccupied() == 1 && table[currentIndex].getItem().getKey() == key) {
			itemOut = table[currentIndex].getItem();
			return true;
		} else if (table[currentIndex].getOccupied() == 0) {
			break; // Stop if an empty slot is found
		}
	}
	return false;
}

// Rehash the table when load factor is too high
template <typename T>
void HashTable<T>::rehash() {
	int oldCapacity = capacity;
	int newCapacity = nextPrime(capacity * 2);
	HashNode<T> *oldTable = table;
	table = new HashNode<T>[newCapacity];
	capacity = newCapacity;
	size = 0;

	for (int i = 0; i < oldCapacity; ++i) {
		if (oldTable[i].getOccupied() == 1) {
			// optimized insertion for rehashing
			const T &item = oldTable[i].getItem();
			string key = item.getKey();
			int index = hashFunction(key) % capacity;
			// Linear probing for placement in new table
			int collisions = 0;
			while (table[index].getOccupied() == 1) {
				index = (index + 1) % capacity;
				++collisions;
			}
			table[index].setItem(item);
			table[index].setOccupied(1);
			table[index].setCollisions(collisions);
			size++;
		}
	}
	delete[] oldTable;
}
