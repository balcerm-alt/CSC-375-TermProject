#include "Scoring.h"
#include <iostream>

void Scoring::updateGameScore(Game& game) {

    if (game.isByeGame()) {
        std::cout << "Cannot score a BYE game.\n";
        return;
    }

    Teams& home = *(game.getHomeTeam());
    Teams& away = *(game.getAwayTeam());

    int homeScore, awayScore;

    std::cout << home.getName() << " Score: ";
    std::cin >> homeScore;

    std::cout << away.getName() << " Score: ";
    std::cin >> awayScore;

    game.setScore(homeScore, awayScore);

    home.addPoints(homeScore, awayScore);
    away.addPoints(awayScore, homeScore);

    if (homeScore > awayScore)
        home.addWin();
    else
        away.addWin();

    std::cout << "\nUpdating individual scoring for "
              << home.getName() << "\n";

    updatePlayerScores(home);

    std::cout << "\nUpdating individual scoring for "
              << away.getName() << "\n";

    updatePlayerScores(away);

    std::cout << "Game Updated Successfully.\n";
}

void Scoring::updatePlayerScores(Teams& team) {

    char choice = 'Y';

    while (choice == 'Y' || choice == 'y') {

        team.displayRoster();

        int selection;
        std::cout << "Select player: ";
        std::cin >> selection;

        Player* player = team.getPlayer(selection - 1);

        if (player != nullptr) {
            int pts;
            std::cout << player->getName()
                      << "'s Score: ";
            std::cin >> pts;

            player->addPoints(pts);
            std::cout << "Updated.\n";
        }

        std::cout << "Add Another? (Y/N): ";
        std::cin >> choice;
    }
}