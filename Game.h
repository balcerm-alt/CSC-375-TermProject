#ifndef GAME_H
#define GAME_H

#include "Teams.h"

class Game {

private:
    Teams* home;
    Teams* away;

    int homeScore;
    int awayScore;

    bool played;
    bool isBye;

public:
    Game(Teams* h, Teams* a, bool bye = false);

    Teams* getHomeTeam();
    Teams* getAwayTeam();

    void setScore(int h, int a);

    int getHomeScore() const;
    int getAwayScore() const;

    bool isPlayed() const;
    bool isByeGame() const;
};

#endif