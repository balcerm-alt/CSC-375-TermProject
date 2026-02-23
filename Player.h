#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {

private:
    std::string name;
    int points;

public:
    Player();
    Player(const std::string& n);

    std::string getName() const;

    void addPoints(int pts);
    int getPoints() const;

    void setName(const std::string& newName);
};

#endif