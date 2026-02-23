#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Teams.h"
#include <string>

class HashTable {

private:

    struct Node {
        std::string key;
        Teams team;
        Node* next;

        Node(std::string k, Teams t)
            : key(k), team(t), next(nullptr) {}
    };

    static const int TABLE_SIZE = 23;

    Node* table[TABLE_SIZE];

    int hashFunction(const std::string& key) const;

public:
    HashTable();
    ~HashTable();

    void insert(const std::string& key, const Teams& team);
    Teams* search(const std::string& key);

    void displayAll() const;

    int getCount() const;
    Teams* getByIndex(int index);
};

#endif