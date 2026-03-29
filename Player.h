#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {

private:
    std::string name;
    int regularPoints;
    int playoffPoints;

public:
    Player();
    Player(const std::string& n);

    std::string getName() const;

    void addRegularPoints(int pts);
    void addPlayoffPoints(int pts);

    int getRegularPoints() const;
    int getPlayoffPoints() const;
    int getTotalPoints() const;

    void setName(const std::string& newName);
};

#endif