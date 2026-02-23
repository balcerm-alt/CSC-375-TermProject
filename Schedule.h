#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Game.h"
#include "HashTable.h"

class Schedule {

private:
    static const int MAX_WEEKS = 50;
    static const int MAX_GAMES_PER_WEEK = 20;

    Game* weeks[MAX_WEEKS][MAX_GAMES_PER_WEEK];
    int weekGameCount[MAX_WEEKS];
    int totalWeeks;

public:
    Schedule();

    void generate(HashTable& teams, int numberOfWeeks);
    void displayGames() const;

    Game* getGame(int weekIndex, int gameIndex);

    void clear();
};

#endif