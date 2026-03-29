#ifndef RANKINGS_H
#define RANKINGS_H

#include "TeamTrees.h"

class Rankings {

private:
    struct PlayerEntry
    {
        std::string name;
        int regularPoints;
        int playoffPoints;
    };

    void sortTeamsByWins(Teams* arr[], int count);
    void sortPlayersByRegularPoints(PlayerEntry arr[], int count);
    void sortPlayersByPlayoffPoints(PlayerEntry arr[], int count);

public:
    void display(TeamTrees& teams);
};

#endif