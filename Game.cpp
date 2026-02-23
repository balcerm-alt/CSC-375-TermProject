#include "Game.h"

//conrtuctor
Game::Game(Teams* h, Teams* a, bool bye)
        : home(h), away(a),
          homeScore(0), awayScore(0),
          played(false), isBye(bye) {}//bye week

Teams* Game::getHomeTeam() { return home; }//returns pointer to home team
Teams* Game::getAwayTeam() { return away; }//returns pointer to away team

void Game::setScore(int h, int a)//sets scores when user sets score
{
    homeScore = h;
    awayScore = a;
    played = true;//marks game as played
}

int Game::getHomeScore() const { return homeScore; }//returns score of home team
int Game::getAwayScore() const { return awayScore; }//returns score of away team

bool Game::isPlayed() const { return played; }//returns whether game is played
bool Game::isByeGame() const { return isBye; }//or is bye week