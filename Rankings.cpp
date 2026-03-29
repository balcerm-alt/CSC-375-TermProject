#include "Rankings.h"
#include <iostream>

void Rankings::sortTeamsByWins(Teams* arr[], int count) //sorts the teams based on wins of games played
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            bool shouldSwap = false;

            if (arr[j]->getWins() < arr[j + 1]->getWins())
                shouldSwap = true;
            else if (arr[j]->getWins() == arr[j + 1]->getWins() &&
                     arr[j]->getPointsFor() < arr[j + 1]->getPointsFor())
                shouldSwap = true;
            else if (arr[j]->getWins() == arr[j + 1]->getWins() &&
                     arr[j]->getPointsFor() == arr[j + 1]->getPointsFor() &&
                     arr[j]->getPointDifferential() < arr[j + 1]->getPointDifferential())
                shouldSwap = true;

            if (shouldSwap)
            {
                Teams* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void Rankings::sortPlayersByRegularPoints(PlayerEntry arr[], int count) //sorts the players based off regular season points
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].regularPoints < arr[j + 1].regularPoints)
            {
                PlayerEntry temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void Rankings::sortPlayersByPlayoffPoints(PlayerEntry arr[], int count) //sorts the players based off playoff points
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (arr[j].playoffPoints < arr[j + 1].playoffPoints)
            {
                PlayerEntry temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void Rankings::display(TeamTrees& teams)
{
    Teams* teamRankings[100];
    int teamCount = 0;

    teams.fillArray(teamRankings, teamCount);
    sortTeamsByWins(teamRankings, teamCount);

    std::cout << "\n=== Team Rankings By Wins ===\n";

    for (int i = 0; i < teamCount; i++)
    {
        std::cout << i + 1 << ". "
                  << teamRankings[i]->getName()
                  << " | Wins: " << teamRankings[i]->getWins()
                  << " | Losses: " << teamRankings[i]->getLosses()
                  << " | Ties: " << teamRankings[i]->getTies()
                  << " | Points For: " << teamRankings[i]->getPointsFor()
                  << "\n";
    }

    PlayerEntry players[500];
    int playerCount = 0;

    for (int i = 0; i < teamCount; i++)
    {
        for (int j = 0; j < teamRankings[i]->getPlayerCount(); j++)
        {
            Player* p = teamRankings[i]->getPlayer(j);

            if (p != nullptr)
            {
                players[playerCount].name = p->getName();
                players[playerCount].regularPoints = p->getRegularPoints();
                players[playerCount].playoffPoints = p->getPlayoffPoints();
                playerCount++;
            }
        }
    }

    sortPlayersByRegularPoints(players, playerCount);

    std::cout << "\n=== Top 5 Players By Regular Season Points ===\n";

    int regularLimit = (playerCount < 5) ? playerCount : 5;
    for (int i = 0; i < regularLimit; i++)
    {
        std::cout << i + 1 << ". "
                  << players[i].name
                  << " | Regular Points: " << players[i].regularPoints
                  << "\n";
    }

    sortPlayersByPlayoffPoints(players, playerCount);

    std::cout << "\n=== Top 5 Players By Playoff Points ===\n";

    int playoffLimit = (playerCount < 5) ? playerCount : 5;
    for (int i = 0; i < playoffLimit; i++)
    {
        std::cout << i + 1 << ". "
                  << players[i].name
                  << " | Playoff Points: " << players[i].playoffPoints
                  << "\n";
    }
}