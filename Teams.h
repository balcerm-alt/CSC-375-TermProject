#ifndef TEAMS_H
#define TEAMS_H

#include "Player.h"
#include <string>

class Teams {
private:
    std::string teamName;

    Player players[50];
    int playerCount;

    int wins;
    int pointsFor;
    int pointsAgainst;

public:
    Teams();
    Teams(std::string name);

    void addPlayer(const Player& p);
    void displayRoster() const;

    Player* getPlayer(int index);
    int getPlayerCount() const;

    std::string getName() const;

    void addWin();
    void addPoints(int scored, int allowed);

    int getWins() const;
    int getPointDiff() const;
};

#endif