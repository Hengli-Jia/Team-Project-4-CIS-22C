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

int HashTable::linearProbe(const std::string& key, int& probeLength) const {
    int index = hashFunction(key);
    probeLength = 1;  // At least one probe
    
    while (true) {
        // Empty slot or matching key found
        if (table[index].getKey().empty() || table[index].getKey() == key) {
            return index;
        }
        
        // Linear probing
        index = (index + 1) % capacity;
        probeLength++;
        
        // Prevent infinite loops
        if (probeLength > capacity) {
            return -1;
        }
    }
}

void HashTable::insert(const Puzzle& puzzle) {
    // Rehash if load factor exceeds threshold
    if (static_cast<double>(size) / capacity > 0.7) {
        rehash();
    }

    int probeLength = 0;
    int index = linearProbe(puzzle.getKey(), probeLength);
    
    // Update collision statistics
    if (probeLength > longestCollisionPath) {
        longestCollisionPath = probeLength;
    }
    if (probeLength > 1) {
        collisionCount++;
    }

    // Insert into hash table
    if (table[index].getKey().empty()) {
        size++;
    }
    table[index] = puzzle;
    
    // Insert into BST with both key and index
    bst.insert(puzzle.getKey(), index);  // BST's insert method
}

Puzzle* HashTable::search(const std::string& key) {
    int probeLength = 0;
    int index = linearProbe(key, probeLength);
    
    if (index != -1 && !table[index].getKey().empty()) {
        return &table[index];
    }
    return nullptr;
}

bool HashTable::remove(const std::string& key) {
    int probeLength = 0;
    int index = linearProbe(key, probeLength);
    
    if (index != -1 && !table[index].getKey().empty()) {
        table[index] = Puzzle("", 0);  // Mark as empty
        size--;
        
        // Also remove from BST
        bst.remove(key);
        return true;
    }
    return false;
}

void HashTable::rehash() {
    int newCapacity = capacity * 2;
    std::vector<Puzzle> newTable(newCapacity);
    
    // Clear and rebuild BST
    BST newBST;
    bst = newBST;
    
    size = 0;
    longestCollisionPath = 0;
    
    // Reinsert all elements
    for (int i = 0; i < capacity; ++i) {
        if (!table[i].getKey().empty()) {
            int probeLength = 0;
            int newIndex = linearProbe(table[i].getKey(), probeLength);
            newTable[newIndex] = table[i];
            size++;
            
            // Insert into new BST
            bst.insert(table[i].getKey(), newIndex);
        }
    }
    
    table = std::move(newTable);
    capacity = newCapacity;
}

void HashTable::printStats() const {
    std::cout << "HashTable Statistics:\n";
    std::cout << " - Capacity: " << capacity << "\n";
    std::cout << " - Size: " << size << "\n";
    std::cout << " - Load Factor: " << static_cast<double>(size) / capacity << "\n";
    std::cout << " - Collision Count: " << collisionCount << "\n";
    std::cout << " - Longest Collision Path: " << longestCollisionPath << "\n";
    
    // Optional: Print BST statistics
    bst.printStats();
}