#include "Player.h"

//constructor
Player::Player()
        : name(""), points(0) {}

//main constructor
Player::Player(const std::string& n)
        : name(n), points(0) {}

std::string Player::getName() const //returns player name
{
    return name;
}

void Player::addPoints(int pts) //adds point to player
{
    points += pts;
}

int Player::getPoints() const //returns player points
{
    return points;
}

void Player::setName(const std::string& newName) //allows player to be renamed
{
    name = newName;
}