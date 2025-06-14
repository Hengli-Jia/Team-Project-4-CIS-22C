#include "HashTable.h"
#include <iostream>

// Constructor: initializes the hash table with a given capacity
HashTable::HashTable(int initialCapacity) {
	capacity = initialCapacity;
	size = 0;
	table = new HashNode[capacity];
}

// Destructor: releases allocated memory
HashTable::~HashTable() { delete[] table; }

// Simple hash function for string keys
int HashTable::hashFunction(const std::string &key) const {
	int hash = 1;
	for (char c : key) {
		hash *= c;
	}
	return hash % capacity;
}

// Linear probing for collision resolution
int HashTable::linearProbe(int hashcode) const {
	return (hashcode + 1) % capacity;
}

// Insert a Puzzle item into the hash table
bool HashTable::insert(const Puzzle &item) {
	if (isFull()) {
		std::cout << "[DEBUG] Table is full, rehashing..." << std::endl;
		rehash();
	}
	std::string key = item.getKey();
	int index = hashFunction(key);
	int collisions = 0;

	std::cout << "[DEBUG] Inserting key: " << key
			  << ", initial index: " << index << ", capacity: " << capacity
			  << std::endl;

	for (int i = 0; i < capacity; ++i) {
		int currentIndex = (index + i) % capacity;
		std::cout << "[DEBUG] Attempting to insert at index: " << currentIndex
				  << std::endl;
		if (currentIndex < 0 || currentIndex >= capacity) {
			std::cerr << "[ERROR] Out-of-bounds index: " << currentIndex
					  << " (capacity: " << capacity << ")" << std::endl;
			abort();
		}
		if (table[currentIndex].getOccupied() != 1) {
			std::cout << "[DEBUG] Setting item at index: " << currentIndex
					  << ", HashNode address: " << &table[currentIndex]
					  << std::endl;
			table[currentIndex].setItem(item);
			std::cout << "[DEBUG] Set item at index: " << currentIndex
					  << std::endl;
			table[currentIndex].setOccupied(1);
			table[currentIndex].setCollisions(collisions);
			size++;
			std::cout << "[DEBUG] Inserted item at index: " << currentIndex
					  << ", total size: " << size << std::endl;
			return true;
		}
		// If duplicate key, do not insert
		if (table[currentIndex].getOccupied() == 1 &&
			table[currentIndex].getItem().getKey() == key) {
			std::cout << "[DEBUG] Duplicate key found at index: "
					  << currentIndex << ", not inserting." << std::endl;
			return false;
		}
		collisions++;
		std::cout << "[DEBUG] Collision at index: " << currentIndex
				  << ", total collisions: " << collisions << std::endl;
	}
	return false;
}

// Remove a Puzzle item by key, output the removed item
bool HashTable::remove(Puzzle &itemOut, const std::string &key) {
	int index = hashFunction(key);

	for (int i = 0; i < capacity; ++i) {
		int currentIndex = (index + i) % capacity;
		if (table[currentIndex].getOccupied() == 1 &&
			table[currentIndex].getItem().getKey() == key) {
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
bool HashTable::search(Puzzle &itemOut, const std::string &key) const {
	int index = hashFunction(key);

	for (int i = 0; i < capacity; ++i) {
		int currentIndex = (index + i) % capacity;
		if (table[currentIndex].getOccupied() == 1 &&
			table[currentIndex].getItem().getKey() == key) {
			itemOut = table[currentIndex].getItem();
			return true;
		} else if (table[currentIndex].getOccupied() == 0) {
			break; // Stop if an empty slot is found
		}
	}
	return false;
}
// Rehash the table when load factor is too high
void HashTable::rehash() {
	int oldCapacity = capacity;
	capacity *= 2;
	HashNode *oldTable = table;
	table = new HashNode[capacity];
	size = 0;

	for (int i = 0; i < oldCapacity; ++i) {
		if (oldTable[i].getOccupied() == 1) {
			insert(oldTable[i].getItem());
		}
	}
	delete[] oldTable;
}
