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

static char getSafeChar() //used for safe character for (Y/N)
{
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty())
        return input[0];
    return '\0';
}

void Scoring::updateGame(Game* game) //updates score for team, team total, team wins(When rankings are done) and player points
{

    if (game == nullptr || game->isByeGame()) //safety check for bye weeks
    {
        std::cout << "Cannot score a BYE game.\n";
        return;
    }

    Teams* home = game->getHomeTeam(); //pointer to home team
    Teams* away = game->getAwayTeam(); //pointer to away team

    std::cout << "\n" << home->getName() << " Score: "; //home team score
    int homeScore = getSafeInt();

    std::cout << away->getName() << " Score: "; //away team score
    int awayScore = getSafeInt();

    game->setScore(homeScore, awayScore); //updates so score will be seen on schedule

    home->addPoints(homeScore, awayScore); //updates points scored and allowed for rankings for home
    away->addPoints(awayScore, homeScore); //updates points scored and allowed for rankings for away

    if (homeScore > awayScore) //updates wins for home
        home->addWin();
    else if (awayScore > homeScore) //updates wins for away
        away->addWin();


    std::cout << "\nUpdating individual scoring for " //player scoring section
              << home->getName() << "\n";

    home->displayRosterWithPoints(); //displays roster with current scored points

    while (true) //allows adding mulitple player scores
    {

        std::cout << "Select player: ";
        int selection = getSafeInt(); //user sees player number starting at 1

        Player* player = home->getPlayer(selection - 1); //code sees user input and subtracts 1 to start at 0

        if (player == nullptr) //invalid number = loop conitnues
        {
            std::cout << "Invalid selection.\n";
            continue;
        }

        std::cout << player->getName() << "'s Score: ";
        int pts = getSafeInt(); //allows user input players points

        player->addPoints(pts); //adds player points

        std::cout << "Updated.\n";
        std::cout << "Add Another? (Y/N): "; //asks for any other point input

        char choice = getSafeChar();
        if (choice == 'N' || choice == 'n') //n breaks loop
            break;
    }


    std::cout << "\nUpdating individual scoring for " //repeats for away team
              << away->getName() << "\n";

    away->displayRosterWithPoints();

    while (true)
    {

        std::cout << "Select player: ";
        int selection = getSafeInt();

        Player* player = away->getPlayer(selection - 1);

        if (player == nullptr)
        {
            std::cout << "Invalid selection.\n";
            continue;
        }

        std::cout << player->getName() << "'s Score: ";
        int pts = getSafeInt();

        player->addPoints(pts);

        std::cout << "Updated.\n";
        std::cout << "Add Another? (Y/N): ";

        char choice = getSafeChar();
        if (choice == 'N' || choice == 'n')
            break;
    }

    std::cout << "\nGame Updated Successfully.\n"; //completion verification
}