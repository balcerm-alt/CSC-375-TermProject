#include "Teams.h"
#include <iostream>

//constructor
Teams::Teams()
        : name(""), //sets name to empty
          playerCount(0), //sets player count empty
          wins(0), //sets wins empty
          pointsFor(0), //sets points for empty
          pointsAgainst(0) {} //sets points against empty

//main constructor can be edited with inputs
Teams::Teams(const std::string& teamName)
        : name(teamName),
          playerCount(0),
          wins(0),
          pointsFor(0),
          pointsAgainst(0) {}

std::string Teams::getName() const //returns team name
{
    return name;
}

void Teams::addPlayer(const Player& p) //adds player to team
{

    if (playerCount < MAX_PLAYERS) //prevents overflow of array
    {
        players[playerCount] = p; //stores player in next available slots
        playerCount++;
    }
}

Player* Teams::getPlayer(int index) //returns pointer to a player
{

    if (index < 0 || index >= playerCount) //safety check
        return nullptr;

    return &players[index];
}

int Teams::getPlayerCount() const //returns number of players on team
{
    return playerCount;
}

void Teams::displayRoster() const //displays roster using 1. 2. 3.
{

    for (int i = 0; i < playerCount; i++)
    {
        std::cout << i + 1 << ". "
                  << players[i].getName()
                  << "\n";
    }
}

void Teams::displayRosterWithPoints() const //displays team roster with points assigned
{

    for (int i = 0; i < playerCount; i++)
    {
        std::cout << i + 1 << ". "
                  << players[i].getName()
                  << " - "
                  << players[i].getPoints()
                  << "\n";
    }
}

void Teams::addPoints(int scored, int allowed) //updates team totals
{

    pointsFor += scored;
    pointsAgainst += allowed;
}

void Teams::addWin() //adds wins to teams USED FOR RANKINGS NOT DONE YET
{
    wins++;
}

int Teams::getWins() const //returns wins USED FOR RANKINGS
{
    return wins;
}

int Teams::getPointsFor() const //returns points scored
{
    return pointsFor;
}

int Teams::getPointsAgainst() const //returns points against
{
    return pointsAgainst;
}

void Teams::resetStats() //resets stats
{

    wins = 0;
    pointsFor = 0;
    pointsAgainst = 0;

    for (int i = 0; i < playerCount; i++)
    {
        players[i] = Player(players[i].getName());
    }
}