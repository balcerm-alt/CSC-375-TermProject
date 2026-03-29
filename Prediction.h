#ifndef PREDICTION_H
#define PREDICTION_H

#include "TeamTrees.h"
#include "Schedule.h"

class Prediction {

private:
    static const int MAX_TEAMS = 100;

    Teams* teamArray[MAX_TEAMS];
    int teamCount;

    int directWins[MAX_TEAMS][MAX_TEAMS];
    int directGames[MAX_TEAMS][MAX_TEAMS];
    int pointsScoredAgainst[MAX_TEAMS][MAX_TEAMS];
    double finalPower[MAX_TEAMS];

    void clearTables();
    void buildTeamArray(TeamTrees& teams);
    int findTeamIndex(Teams* team);
    double clamp(double value);
    void computePowerRatings();

public:
    Prediction();

    void buildModel(TeamTrees& teams, Schedule& schedule, int regularSeasonWeeks);
    double predictChance(Teams* teamA, Teams* teamB);
    double getTeamPower(Teams* team);
    void displayPrediction(TeamTrees& teams, Schedule& schedule, int regularSeasonWeeks);
};

#endif