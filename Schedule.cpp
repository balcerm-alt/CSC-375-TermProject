#include "Schedule.h"
#include <iostream>

Schedule::Schedule() {
    clear();
}

void Schedule::clear() {

    totalWeeks = 0;

    for (int i = 0; i < MAX_WEEKS; i++) {
        weekGameCount[i] = 0;

        for (int j = 0; j < MAX_GAMES_PER_WEEK; j++) {
            weeks[i][j] = nullptr;
        }
    }
}

void Schedule::generate(HashTable& teams, int numberOfWeeks) {

    clear();

    int teamCount = teams.getCount();
    if (teamCount < 2) return;

    Teams* teamList[50];

    for (int i = 0; i < teamCount; i++)
        teamList[i] = teams.getByIndex(i);

    if (teamCount % 2 != 0) {
        teamList[teamCount] = nullptr; // BYE placeholder
        teamCount++;
    }

    totalWeeks = numberOfWeeks;

    for (int week = 0; week < numberOfWeeks; week++) {

        weekGameCount[week] = 0;

        for (int i = 0; i < teamCount / 2; i++) {

            Teams* home = teamList[i];
            Teams* away = teamList[teamCount - 1 - i];

            if (home == nullptr || away == nullptr) {

                Teams* realTeam = home ? home : away;

                weeks[week][weekGameCount[week]++] =
                        new Game(realTeam, nullptr, true);
            }
            else {
                weeks[week][weekGameCount[week]++] =
                        new Game(home, away);
            }
        }

        // rotation
        Teams* last = teamList[teamCount - 1];

        for (int i = teamCount - 1; i > 1; i--)
            teamList[i] = teamList[i - 1];

        teamList[1] = last;
    }
}

void Schedule::displayGames() const {

    if (totalWeeks == 0) {
        std::cout << "No schedule generated.\n";
        return;
    }

    for (int week = 0; week < totalWeeks; week++) {

        std::cout << "\nWeek " << week + 1 << ":\n";

        int displayNumber = 1;

        // Print real games first
        for (int game = 0; game < weekGameCount[week]; game++) {

            Game* g = weeks[week][game];

            if (!g->isByeGame()) {

                std::cout << "  "
                          << displayNumber << ". "
                          << g->getHomeTeam()->getName()
                          << " vs "
                          << g->getAwayTeam()->getName();

                if (g->isPlayed()) {
                    std::cout << ": "
                              << g->getHomeScore()
                              << " - "
                              << g->getAwayScore();
                }

                std::cout << "\n";

                displayNumber++;
            }
        }

        // Then print BYE last (no numbering)
        for (int game = 0; game < weekGameCount[week]; game++) {

            Game* g = weeks[week][game];

            if (g->isByeGame()) {

                std::cout << "  "
                          << g->getHomeTeam()->getName()
                          << " - BYE\n";
            }
        }
    }
}

Game* Schedule::getGame(int weekIndex, int gameIndex) {

    if (weekIndex >= 0 &&
        weekIndex < totalWeeks &&
        gameIndex >= 0 &&
        gameIndex < weekGameCount[weekIndex])
        return weeks[weekIndex][gameIndex];

    return nullptr;
}