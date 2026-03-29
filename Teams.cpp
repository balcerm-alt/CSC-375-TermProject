#include "Teams.h"
#include <iostream>

//constructor
Teams::Teams()
        : name(""), //sets name to empty
          playerCount(0), //sets player count empty
          wins(0), //sets wins empty
          losses(0), //sets losses empty
          ties(0), //sets ties empty
          pointsFor(0), //sets points for empty
          pointsAgainst(0) {} //sets points against empty

//main constructor can be edited with inputs
Teams::Teams(const std::string& teamName)
        : name(teamName),
          playerCount(0),
          wins(0),
          losses(0),
          ties(0),
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

void Teams::displayRosterWithPoints() const //displays team roster with point totals
{
    for (int i = 0; i < playerCount; i++)
    {
        std::cout << i + 1 << ". "
                  << players[i].getName()
                  << " - Regular: " << players[i].getRegularPoints()
                  << " | Playoff: " << players[i].getPlayoffPoints()
                  << " | Total: " << players[i].getTotalPoints()
                  << "\n";
    }
}

void Teams::displayTeamStats() const
{
    std::cout << "Team: " << name << "\n";
    std::cout << "Wins: " << wins
              << " | Losses: " << losses
              << " | Ties: " << ties
              << " | Points For: " << pointsFor
              << " | Points Against: " << pointsAgainst
              << " | Player Total Points: " << getTotalPlayerPoints()
              << "\n";

    for (int i = 0; i < playerCount; i++)
    {
        std::cout << i + 1 << ". "
                  << players[i].getName()
                  << " - Total: " << players[i].getTotalPoints()
                  << " (Regular: " << players[i].getRegularPoints()
                  << ", Playoff: " << players[i].getPlayoffPoints()
                  << ")\n";
    }

    std::cout << "\n";
}

void Teams::addPoints(int scored, int allowed) //updates team totals
{
    pointsFor += scored;
    pointsAgainst += allowed;
}

void Teams::addWin() //adds wins to teams
{
    wins++;
}

void Teams::addLoss() //adds losses to teams
{
    losses++;
}

void Teams::addTie() //adds ties to teams
{
    ties++;
}

int Teams::getWins() const //returns wins
{
    return wins;
}

int Teams::getLosses() const //returns losses
{
    return losses;
}

int Teams::getTies() const //returns ties
{
    return ties;
}

int Teams::getPointsFor() const //returns points scored
{
    return pointsFor;
}

int Teams::getPointsAgainst() const //returns points against
{
    return pointsAgainst;
}

int Teams::getTotalRegularPlayerPoints() const //returns total regular player points
{
    int total = 0;

    for (int i = 0; i < playerCount; i++)
        total += players[i].getRegularPoints();

    return total;
}

int Teams::getTotalPlayoffPlayerPoints() const //returns total playoff player points
{
    int total = 0;

    for (int i = 0; i < playerCount; i++)
        total += players[i].getPlayoffPoints();

    return total;
}

int Teams::getTotalPlayerPoints() const //returns total player scored points
{
    int total = 0;

    for (int i = 0; i < playerCount; i++)
        total += players[i].getTotalPoints();

    return total;
}

int Teams::getPointDifferential() const //returns scoring margin
{
    return pointsFor - pointsAgainst;
}

Player* Teams::getHighestTotalPointPlayer()
{
    if (playerCount == 0)
        return nullptr;

    int bestIndex = 0;

    for (int i = 1; i < playerCount; i++)
    {
        if (players[i].getTotalPoints() > players[bestIndex].getTotalPoints())
            bestIndex = i;
    }

    return &players[bestIndex];
}

void Teams::resetStats() //resets stats
{
    wins = 0;
    losses = 0;
    ties = 0;
    pointsFor = 0;
    pointsAgainst = 0;

    for (int i = 0; i < playerCount; i++)
    {
        players[i] = Player(players[i].getName());
    }
}