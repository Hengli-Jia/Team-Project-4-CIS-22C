// hashtable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "puzzle.h"
#include <vector>
#include <functional>
#include <string>

class HashTable {
public:
    // Constructor with default initial capacity
    HashTable(int initialCapacity = 10);
    
    // Insert puzzle into hash table
    void insert(const Puzzle& puzzle);
    
    // search puzzle by key
    Puzzle* search(const std::string& key);
    
    // Remove puzzle by key
    bool remove(const std::string& key);
    
    // Print statistics
    void printStats() const;

    // print all puzzles in the hash table
    void printAll() const;

private:
    std::vector<Puzzle> table;      // Hash table array
    int capacity;                   // Total capacity
    int size;                       // Current size
    int collisionCount;             // Number of collisions
    int longestCollisionPath;       // Longest probe sequence

    // Hash function to compute index
    int hashFunction(const std::string& key) const;
    
    // Linear probing to resolve collisions
    int linearProbe(int hashcode) const;
    
    // Resize and rehash when load factor is high
    void rehash();
};

#endif // HASHTABLE_H