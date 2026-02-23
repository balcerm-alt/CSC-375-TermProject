#include "HashTable.h"
#include <iostream>

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = table[i];

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

int HashTable::hashFunction(const std::string& key) const {

    int sum = 0;

    for (char c : key) {
        sum += c;
    }

    return sum % TABLE_SIZE;
}

void HashTable::insert(const std::string& key, const Teams& team) {

    int index = hashFunction(key);

    Node* newNode = new Node(key, team);

    if (table[index] == nullptr) {
        table[index] = newNode;
    }
    else {
        // Insert at beginning of linked list
        newNode->next = table[index];
        table[index] = newNode;
    }
}

Teams* HashTable::search(const std::string& key) {

    int index = hashFunction(key);

    Node* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            return &(current->team);
        }
        current = current->next;
    }

    return nullptr;
}

void HashTable::displayAll() const {

    for (int i = 0; i < TABLE_SIZE; i++) {

        Node* current = table[i];

        while (current != nullptr) {
            std::cout << "Team: "
                      << current->team.getName() << "\n";

            current->team.displayRoster();
            std::cout << "\n";

            current = current->next;
        }
    }
}

int HashTable::getCount() const {

    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {

        Node* current = table[i];

        while (current != nullptr) {
            count++;
            current = current->next;
        }
    }

    return count;
}

Teams* HashTable::getByIndex(int index) {

    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {

        Node* current = table[i];

        while (current != nullptr) {

            if (count == index)
                return &(current->team);

            count++;
            current = current->next;
        }
    }

    return nullptr;
}