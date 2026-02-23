#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Game.h"
#include "TeamTrees.h"

class Schedule {

private:
  static const int MAX_WEEKS = 50;
  static const int MAX_GAMES_PER_WEEK = 25;

  Game* weeks[MAX_WEEKS][MAX_GAMES_PER_WEEK];
  int gamesPerWeek[MAX_WEEKS];
  int totalWeeks;

public:
  Schedule();

  void generate(TeamTrees& teams, int seasonWeeks);
  void display();
  Game* getGame(int weekIndex, int gameIndex);

  void clear();
};

#endif