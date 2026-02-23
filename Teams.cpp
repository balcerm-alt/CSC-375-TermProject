#include "Teams.h"
#include <iostream>

Teams::Teams() : teamName(""), playerCount(0), wins(0), pointsFor(0), pointsAgainst(0) {}

Teams::Teams(std::string name) {
    teamName = name;
    playerCount = 0;
    wins = 0;
    pointsFor = 0;
    pointsAgainst = 0;
}

Player* Teams::getPlayer(int index) {
    if (index >= 0 && index < playerCount)
        return &players[index];
    return nullptr;
}

int Teams::getPlayerCount() const {
    return playerCount;
}

void Teams::addPlayer(const Player& p) {
    if (playerCount < 50) {
        players[playerCount++] = p;
    }
}

void Teams::displayRoster() const {

    std::cout << "Team: " << teamName
              << " | Wins: " << wins
              << " | Points For: " << pointsFor
              << " | Points Against: " << pointsAgainst
              << "\n";

    for (int i = 0; i < playerCount; i++) {

        std::cout << "  "
                  << i + 1 << ". "
                  << players[i].getName()
                  << " - "
                  << players[i].getPoints()
                  << "\n";
    }

    std::cout << "\n";
}

std::string Teams::getName() const {
    return teamName;
}

void Teams::addWin() {
    wins++;
}

void Teams::addPoints(int scored, int allowed) {
    pointsFor += scored;
    pointsAgainst += allowed;
}

int Teams::getWins() const {
    return wins;
}

int Teams::getPointDiff() const {
    return pointsFor - pointsAgainst;
}