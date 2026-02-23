#include "Game.h"

Game::Game(Teams* h, Teams* a, bool bye)
        : home(h),
          away(a),
          homeScore(0),
          awayScore(0),
          played(false),
          isBye(bye) {}

Teams* Game::getHomeTeam() { return home; }
Teams* Game::getAwayTeam() { return away; }

void Game::setScore(int h, int a) {
    homeScore = h;
    awayScore = a;
    played = true;
}

int Game::getHomeScore() const { return homeScore; }
int Game::getAwayScore() const { return awayScore; }

bool Game::isPlayed() const { return played; }
bool Game::isByeGame() const { return isBye; }