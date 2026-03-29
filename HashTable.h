#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Teams.h"
#include <string>

class HashTable {
private:
    static const int SIZE = 101;

    struct Entry {
        std::string key;
        Teams* value;
        bool occupied;

        Entry() : key(""), value(nullptr), occupied(false) {}
    };

    Entry table[SIZE];

    int hash(const std::string& key);

public:
    HashTable();
    void insert(const std::string& key, Teams* value);
    Teams* get(const std::string& key);
    void clear();
};

#endif