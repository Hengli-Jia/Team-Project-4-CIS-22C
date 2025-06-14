#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

// Constructor: initializes the hash table with a given capacity
template <typename T> HashTable<T>::HashTable(int initialCapacity) {
	capacity = initialCapacity;
	size = 0;
	table = new HashNode<T>[capacity];
}

// Destructor: releases allocated memory
template <typename T> HashTable<T>::~HashTable() { delete[] table; }

// Simple hash function for string keys
template <typename T> int HashTable<T>::hashFunction(const string &key) const {
	int hash = 1;
	for (char c : key) {
		hash = 31 * hash + static_cast<unsigned char>(c);
	}
	return hash % capacity;
}

// Linear probing for collision resolution
template <typename T> int HashTable<T>::linearProbe(int hashcode) const {
	return (hashcode + 1) % capacity;
}

// Insert a Puzzle item into the hash table
template <typename T> bool HashTable<T>::insert(const T &item) {
	if (isFull()) {
		rehash();
	}
	string key = item.getKey();
	int index = hashFunction(key);
	int collisions = 0;

	for (int i = 0; i < capacity; ++i) {
		int currentIndex = (index + i) % capacity;
		if (currentIndex < 0 || currentIndex >= capacity) {
			cerr << "[ERROR] Out-of-bounds index: " << currentIndex
				 << " (capacity: " << capacity << ")" << endl;
			abort();
		}
		if (table[currentIndex].getOccupied() != 1) {
			table[currentIndex].setItem(item);
			table[currentIndex].setOccupied(1);
			table[currentIndex].setCollisions(collisions);
			size++;
			return true;
		}
		// If duplicate key, do not insert
		if (table[currentIndex].getOccupied() == 1 &&
			table[currentIndex].getItem().getKey() == key) {
			return false;
		}
		collisions++;
	}
	return false;
}

// Remove a Puzzle item by key, output the removed item
template <typename T> bool HashTable<T>::remove(T &itemOut, const string &key) {
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
template <typename T>
bool HashTable<T>::search(T &itemOut, const string &key) const {
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
template <typename T> void HashTable<T>::rehash() {
	int oldCapacity = capacity;
	capacity *= 2;
	HashNode<T> *oldTable = table;
	table = new HashNode<T>[capacity];
	size = 0;

	for (int i = 0; i < oldCapacity; ++i) {
		if (oldTable[i].getOccupied() == 1) {
			insert(oldTable[i].getItem());
		}
	}
	delete[] oldTable;
}
