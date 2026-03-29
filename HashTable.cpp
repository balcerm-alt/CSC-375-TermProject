#include "HashTable.h"

HashTable::HashTable()
{
    clear();
}

int HashTable::hash(const std::string& key)
{
    int sum = 0;

    for (int i = 0; i < key.length(); i++)
        sum += key[i];

    return sum % SIZE;
}

void HashTable::insert(const std::string& key, Teams* value)
{
    int index = hash(key);

    while (table[index].occupied)
    {
        if (table[index].key == key)
        {
            table[index].value = value;
            return;
        }

        index = (index + 1) % SIZE;
    }

    table[index].key = key;
    table[index].value = value;
    table[index].occupied = true;
}

Teams* HashTable::get(const std::string& key)
{
    int index = hash(key);
    int start = index;

    while (table[index].occupied)
    {
        if (table[index].key == key)
            return table[index].value;

        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    return nullptr;
}

void HashTable::clear()
{
    for (int i = 0; i < SIZE; i++)
        table[i] = Entry();
}