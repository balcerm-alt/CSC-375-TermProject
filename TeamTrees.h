#ifndef TEAMTREES_H
#define TEAMTREES_H

#include "Teams.h"
#include <string>

class TeamTrees {

private:
    struct Node {
        Teams team;
        Node* left;
        Node* right;

        Node(const Teams& t)
            : team(t), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insertHelper(Node*& node, const Teams& team);
    Teams* searchHelper(Node* node, const std::string& name);

    void displayHelper(Node* node) const;
    void clearHelper(Node*& node);

    void fillArrayHelper(Node* node, Teams* arr[], int& count);

public:
    TeamTrees();
    ~TeamTrees();

    void insert(const Teams& team);
    Teams* search(const std::string& name);

    void displayAll() const;

    void fillArray(Teams* arr[], int& count);

    void clear();
};

#endif