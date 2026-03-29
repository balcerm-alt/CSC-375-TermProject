#include "Scoring.h"
#include <iostream>
#include <string>

static int getSafeInt() //used for a safe integer
{
    while (true)
    {
        std::string input;
        std::getline(std::cin, input);
        try
        {
            return std::stoi(input); //tries to convert user input to integer
        }
        catch (...) //if conversion failed validation
        {
            std::cout << "Invalid number. Try again: ";
        }
    }
}

void Scoring::updateGame(Game* game, bool isPlayoff) //updates score for team, team total, team wins/losses and player points
{
    if (game == nullptr || game->isByeGame()) //safety check for bye weeks
    {
        std::cout << "Cannot score a BYE game.\n";
        return;
    }

    if (game->isPlayed()) //prevents rescoring games
    {
        std::cout << "This game has already been scored... (Press Enter)";
        std::string pause;
        std::getline(std::cin, pause);
        return;
    }

    Teams* home = game->getHomeTeam(); //pointer to home team
    Teams* away = game->getAwayTeam(); //pointer to away team

    int homeScore;
    int awayScore;

    while (true)
    {
        std::cout << "\n" << home->getName() << " Score: "; //home team score
        homeScore = getSafeInt();

        std::cout << away->getName() << " Score: "; //away team score
        awayScore = getSafeInt();

        if (isPlayoff && homeScore == awayScore)
        {
            std::cout << "Playoff games cannot end in a tie. Re-enter scores.\n";
            continue;
        }

        break;
    }

    game->setScore(homeScore, awayScore); //updates so score will be seen on schedule

    home->addPoints(homeScore, awayScore); //updates points scored and allowed for home
    away->addPoints(awayScore, homeScore); //updates points scored and allowed for away

    if (homeScore > awayScore) //updates wins/losses
    {
        home->addWin();
        away->addLoss();
    }
    else if (awayScore > homeScore)
    {
        away->addWin();
        home->addLoss();
    }
    else
    {
        home->addTie();
        away->addTie();
    }

    std::cout << "\nUpdating individual scoring for "
              << home->getName() << "\n";

    home->displayRosterWithPoints();

    int homeRemaining = homeScore;

    while (homeRemaining > 0)
    {
        std::cout << "Remaining team points to assign: " << homeRemaining << "\n";
        std::cout << "Select player: ";
        int selection = getSafeInt();

        Player* player = home->getPlayer(selection - 1);

        if (player == nullptr)
        {
            std::cout << "Invalid selection.\n";
            continue;
        }

        while (true)
        {
            std::cout << player->getName() << "'s Score: ";
            int pts = getSafeInt();

            if (pts < 0)
            {
                std::cout << "Score cannot be negative.\n";
                continue;
            }

            if (pts > homeRemaining)
            {
                std::cout << "You only have " << homeRemaining << " team points left to assign.\n";
                continue;
            }

            if (isPlayoff)
                player->addPlayoffPoints(pts);
            else
                player->addRegularPoints(pts);

            homeRemaining -= pts;
            break;
        }

        std::cout << "Updated.\n";
    }

    std::cout << "\nUpdating individual scoring for "
              << away->getName() << "\n";

    away->displayRosterWithPoints();

    int awayRemaining = awayScore;

    while (awayRemaining > 0)
    {
        std::cout << "Remaining team points to assign: " << awayRemaining << "\n";
        std::cout << "Select player: ";
        int selection = getSafeInt();

        Player* player = away->getPlayer(selection - 1);

        if (player == nullptr)
        {
            std::cout << "Invalid selection.\n";
            continue;
        }

        while (true)
        {
            std::cout << player->getName() << "'s Score: ";
            int pts = getSafeInt();

            if (pts < 0)
            {
                std::cout << "Score cannot be negative.\n";
                continue;
            }

            if (pts > awayRemaining)
            {
                std::cout << "You only have " << awayRemaining << " team points left to assign.\n";
                continue;
            }

            if (isPlayoff)
                player->addPlayoffPoints(pts);
            else
                player->addRegularPoints(pts);

            awayRemaining -= pts;
            break;
        }

        std::cout << "Updated.\n";
    }

    std::cout << "\nGame Updated Successfully.\n"; //completion verification
}