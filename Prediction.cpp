#include "Prediction.h"
#include <iostream>
#include <string>

//constructor
Prediction::Prediction()
        : teamCount(0)
{
    clearTables();
}

void Prediction::clearTables()
{
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        teamArray[i] = nullptr;
        finalPower[i] = 0.0;

        for (int j = 0; j < MAX_TEAMS; j++)
        {
            directWins[i][j] = 0;
            directGames[i][j] = 0;
            pointsScoredAgainst[i][j] = 0;
        }
    }

    teamCount = 0;
}

void Prediction::buildTeamArray(TeamTrees& teams)
{
    teams.fillArray(teamArray, teamCount);
}

int Prediction::findTeamIndex(Teams* team)
{
    for (int i = 0; i < teamCount; i++)
    {
        if (teamArray[i] == team)
            return i;
    }

    return -1;
}

double Prediction::clamp(double value)
{
    if (value < 1.0)
        return 1.0;
    if (value > 99.0)
        return 99.0;
    return value;
}

void Prediction::computePowerRatings() //how the prediction is calculated
{
    double basePower[MAX_TEAMS];

    for (int i = 0; i < teamCount; i++)
    {
        double winsPart = teamArray[i]->getWins() * 100.0;
        double tiesPart = teamArray[i]->getTies() * 25.0;
        double diffPart = teamArray[i]->getPointDifferential() * 10.0;
        double pointsPart = teamArray[i]->getPointsFor() * 1.0;

        basePower[i] = winsPart + tiesPart + diffPart + pointsPart;
    }

    for (int i = 0; i < teamCount; i++)
    {
        double opponentBonus = 0.0;

        for (int j = 0; j < teamCount; j++)
        {
            if (i == j)
                continue;

            opponentBonus += directWins[i][j] * (basePower[j] * 0.10);
        }

        finalPower[i] = basePower[i] + opponentBonus;
    }
}

void Prediction::buildModel(TeamTrees& teams, Schedule& schedule, int regularSeasonWeeks) //builds matchup data from played games
{
    clearTables();
    buildTeamArray(teams);

    for (int week = 0; week < regularSeasonWeeks; week++)
    {
        for (int gameIndex = 0; gameIndex < 50; gameIndex++)
        {
            Game* game = schedule.getGame(week, gameIndex);

            if (game == nullptr)
                break;

            if (game->isByeGame() || !game->isPlayed())
                continue;

            Teams* home = game->getHomeTeam();
            Teams* away = game->getAwayTeam();

            int homeIndex = findTeamIndex(home);
            int awayIndex = findTeamIndex(away);

            if (homeIndex == -1 || awayIndex == -1)
                continue;

            directGames[homeIndex][awayIndex]++;
            directGames[awayIndex][homeIndex]++;

            pointsScoredAgainst[homeIndex][awayIndex] += game->getHomeScore();
            pointsScoredAgainst[awayIndex][homeIndex] += game->getAwayScore();

            if (game->getHomeScore() > game->getAwayScore())
                directWins[homeIndex][awayIndex]++;
            else if (game->getAwayScore() > game->getHomeScore())
                directWins[awayIndex][homeIndex]++;
        }
    }

    computePowerRatings();
}

double Prediction::getTeamPower(Teams* team)
{
    int i = findTeamIndex(team);

    if (i == -1)
        return 0.0;

    return finalPower[i];
}

double Prediction::predictChance(Teams* teamA, Teams* teamB) //the actual prediction based on power and matchups
{
    int a = findTeamIndex(teamA);
    int b = findTeamIndex(teamB);

    if (a == -1 || b == -1)
        return 50.0;

    double powerA = finalPower[a];
    double powerB = finalPower[b];

    double powerEdge = (powerA - powerB) / 8.0;

    double headToHeadEdge = 0.0;
    int h2hWinsA = directWins[a][b];
    int h2hWinsB = directWins[b][a];

    if (h2hWinsA != h2hWinsB)
        headToHeadEdge += (h2hWinsA - h2hWinsB) * 8.0;

    double scoringEdge = 0.0;
    int scoredA = pointsScoredAgainst[a][b];
    int scoredB = pointsScoredAgainst[b][a];

    if (scoredA != scoredB)
        scoringEdge += (scoredA - scoredB) * 0.75;

    double result = 50.0 + powerEdge + headToHeadEdge + scoringEdge;
    return clamp(result);
}

void Prediction::displayPrediction(TeamTrees& teams, Schedule& schedule, int regularSeasonWeeks) //displays the prediction
{
    buildModel(teams, schedule, regularSeasonWeeks);

    Teams* arr[100];
    int count = 0;
    teams.fillArray(arr, count);

    std::cout << "\n=== Team Stats ===\n";
    for (int i = 0; i < count; i++)
    {
        std::cout << arr[i]->getName()
                  << " | Wins: " << arr[i]->getWins()
                  << " | Losses: " << arr[i]->getLosses()
                  << " | Ties: " << arr[i]->getTies()
                  << " | Points For: " << arr[i]->getPointsFor()
                  << " | Points Against: " << arr[i]->getPointsAgainst()
                  << " | Power: " << getTeamPower(arr[i])
                  << "\n";
    }

    std::cout << "\nEnter First Team Name: ";
    std::string nameA;
    std::getline(std::cin, nameA);

    std::cout << "Enter Second Team Name: ";
    std::string nameB;
    std::getline(std::cin, nameB);

    Teams* teamA = teams.search(nameA);
    Teams* teamB = teams.search(nameB);

    if (teamA == nullptr || teamB == nullptr)
    {
        std::cout << "One or both teams were not found.\n";
        return;
    }

    if (teamA == teamB)
    {
        std::cout << "Please choose two different teams.\n";
        return;
    }

    double chanceA = predictChance(teamA, teamB);
    double chanceB = 100.0 - chanceA;

    std::cout << "\n=== Match Prediction ===\n";
    std::cout << teamA->getName() << ": " << chanceA << "% chance to win\n";
    std::cout << teamB->getName() << ": " << chanceB << "% chance to win\n";
}