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
    int index = hashcode;
    int probeCount = 0;
    while (table[index].getOccupied() == 1) {
        index = (index + 1) % capacity;
        probeCount++;
        if (probeCount >= capacity) break; // Table full
    }
    return index;
}

void HashTable::rehash() {
    int oldCapacity = capacity;
    capacity *= 2;
    std::vector<HashNode> oldTable = table;
    table.clear();
    table.resize(capacity);
    size = 0;
    for (const auto& node : oldTable) {
        if (node.getOccupied() == 1) {
            insert(node.getItem());
        }
    }
}

bool HashTable::insert(const HashNode& node) {
    if (size >= capacity * 0.7) {
        rehash();
    }
    std::string key = node.getItem().getKey(); // You must implement getKey() in Puzzle
    int hashcode = hashFunction(key);
    int index = hashcode;
    int collisions = 0;
    while (table[index].getOccupied() == 1) {
        if (table[index].getItem().getKey() == key) {
            // Already exists, do not insert
            return false;
        }
        index = (index + 1) % capacity;
        collisions++;
    }
    HashNode newNode = node;
    newNode.setOccupied(1);
    newNode.setCollisions(collisions);
    table[index] = newNode;
    size++;
    if (collisions > longestCollisionPath) longestCollisionPath = collisions;
    collisionCount += collisions;
    return true;
}

bool HashTable::search(HashNode& node, const std::string& key) {
    int hashcode = hashFunction(key);
    int index = hashcode;
    int probeCount = 0;
    while (table[index].getOccupied() == 1 && probeCount < capacity) {
        if (table[index].getItem().getKey() == key) {
            node = table[index];
            return true;
        }
        index = (index + 1) % capacity;
        probeCount++;
    }
    return false;
}

bool HashTable::remove(HashNode& node, const std::string& key) {
    int hashcode = hashFunction(key);
    int index = hashcode;
    int probeCount = 0;
    while (table[index].getOccupied() == 1 && probeCount < capacity) {
        if (table[index].getItem().getKey() == key) {
            node = table[index];
            table[index].setOccupied(0);
            size--;
            return true;
        }
        index = (index + 1) % capacity;
        probeCount++;
    }
    return false;
}
