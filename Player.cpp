#include "Player.h"

//constructor
Player::Player()
        : name(""), regularPoints(0), playoffPoints(0) {}

//main constructor
Player::Player(const std::string& n)
        : name(n), regularPoints(0), playoffPoints(0) {}

std::string Player::getName() const //returns player name
{
    return name;
}

void Player::addRegularPoints(int pts) //adds regular season points to player
{
    regularPoints += pts;
}

void Player::addPlayoffPoints(int pts) //adds playoff points to player
{
    playoffPoints += pts;
}

int Player::getRegularPoints() const //returns regular season points
{
    return regularPoints;
}

int Player::getPlayoffPoints() const //returns playoff points
{
    return playoffPoints;
}

int Player::getTotalPoints() const //returns total points
{
    return regularPoints + playoffPoints;
}

void Player::setName(const std::string& newName) //allows player to be renamed
{
    name = newName;
}