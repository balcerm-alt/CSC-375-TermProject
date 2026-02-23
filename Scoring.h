#ifndef SCORING_H
#define SCORING_H

#include "Game.h"

class Scoring {

private:
    void updatePlayerScores(Teams& team);

public:
    void updateGameScore(Game& game);
};

#endif