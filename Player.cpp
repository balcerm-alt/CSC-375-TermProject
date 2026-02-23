#include "Player.h"

Player::Player() : name(""), pointsScored(0) {}

Player::Player(std::string n) : name(n), pointsScored(0) {}

std::string Player::getName() const {
    return name;
}

void Player::addPoints(int pts) {
    pointsScored += pts;
}

int Player::getPoints() const {
    return pointsScored;
}