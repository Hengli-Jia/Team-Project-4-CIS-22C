#include "hashtable.h"
#include <iostream>

HashTable::HashTable(int initialCapacity)
    : capacity(initialCapacity), size(0),
      collisionCount(0), longestCollisionPath(0) {
    table.resize(capacity);
}

int HashTable::hashFunction(const std::string& key) const {
    int hash = 1;
    for (char c : key) {
        hash *= c;
    }
    return hash % capacity;
}


int HashTable::linearProbe(int hashcode) const {
    int index = hashcode % capacity;
    int probeLength = 1;
    while (probeLength <= capacity) {
        if (table[index].getKey().empty()) {
             break;
        }
        index = (index + 1) % capacity;
        probeLength++;
        
    }
    if (probeLength > 1) {
        collisionCount++;
    }
    if (probeLength > longestCollisionPath) {
        longestCollisionPath = probeLength;
    }
    return index;
}

void HashTable::insert(const Puzzle& puzzle) {
    if (static_cast<double>(size) / capacity > 0.7) {
        rehash();
    }
    int hashcode = hashFunction(puzzle.getKey());
    int probeLength = 0;
    int index = linearProbe(hashcode);

    if (table[index].getKey().empty()) {
        size++;
    }
    table[index] = puzzle;
}

Puzzle* HashTable::search(const std::string& key) {
    int hashcode = hashFunction(key);
    int probeLength = 0;
    int index = linearProbe(hashcode);
    if (!table[index].getKey().empty()) {
        return &table[index];
    }
    return nullptr;
}

bool HashTable::remove(const std::string& key) {
    int hashcode = hashFunction(key);
    int probeLength = 0;
    int index = linearProbe(hashcode);
    if (!table[index].getKey().empty()) {
        table[index] = Puzzle("", 0); 
        size--;
        return true;
    }
    return false;
}

void HashTable::rehash() {
    int newCapacity = capacity * 2;
    std::vector<Puzzle> newTable(newCapacity);

    int oldCapacity = capacity;
    auto oldTable = table;

    capacity = newCapacity;
    table = std::move(newTable);
    size = 0;
    collisionCount = 0;
    longestCollisionPath = 0;

    for (int i = 0; i < oldCapacity; ++i) {
        if (!oldTable[i].getKey().empty()) {
            insert(oldTable[i]);
        }
    }
}

void HashTable::printStats() const {
    std::cout << "HashTable Statistics:\n";
    std::cout << " - Capacity: " << capacity << "\n";
    std::cout << " - Size: " << size << "\n";
    std::cout << " - Load Factor: " << static_cast<double>(size) / capacity << "\n";
    std::cout << " - Collision Count: " << collisionCount << "\n";
    std::cout << " - Longest Collision Path: " << longestCollisionPath << "\n";
}

void HashTable::printAll() const {
    std::cout << "All Puzzles in HashTable:\n";
    for (const auto& puzzle : table) {
        if (!puzzle.getKey().empty()) {
            std::cout << "Key: " << puzzle.getKey() << ", Value: " << puzzle.getValue() << "\n";
        }
    }
}