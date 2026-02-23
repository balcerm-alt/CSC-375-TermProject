#ifndef TEAMS_H
#define TEAMS_H

#include "Player.h"
#include <string>

class Teams {

private:
    std::string name;

    static const int MAX_PLAYERS = 50;
    Player players[MAX_PLAYERS];
    int playerCount;

    int wins;
    int pointsFor;
    int pointsAgainst;

public:
    Teams();
    Teams(const std::string& teamName);

    std::string getName() const;

    // Player management
    void addPlayer(const Player& p);
    Player* getPlayer(int index);
    int getPlayerCount() const;

    void displayRoster() const;
    void displayRosterWithPoints() const;

    // Team scoring
    void addPoints(int scored, int allowed);
    void addWin();

    int getWins() const;
    int getPointsFor() const;
    int getPointsAgainst() const;

    void resetStats();
};

#endif