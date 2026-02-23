#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    int pointsScored;

public:
    Player();
    Player(std::string n);

    std::string getName() const;

    void addPoints(int pts);
    int getPoints() const;
};

#endif