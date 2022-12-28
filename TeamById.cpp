//
// Created by zaher.amir on 26/12/2022.
//

#include "TeamById.h"


TeamById::TeamById(int teamId)
{
    this->teamPoints = 0;
    teamId_ = teamId;
    this->gamesPlayed = std::make_shared<int>(0);
}
void TeamById::increaseTeamAbility(int value)
{
    this->allPlayersAbility += value;
}
void TeamById::decreaseTeamAbility(int value)
{
    this->allPlayersAbility -= value;
}
int TeamById::getGamesPlayed() const
{
    return *this->gamesPlayed;
}
void TeamById::increaseGamesPlayed(int value)
{
    *this->gamesPlayed += value;
};



bool TeamById::operator<(const TeamById &other) const
{
    if(this->teamId_ < other.teamId_)
    {
        return true;
    }
    return false;
}

bool TeamById::operator>(const TeamById &other) const
{
    if(this ->teamId_ > other.teamId_)
    {
        return true;
    }
    return false;
}

bool TeamById::operator==(const TeamById &other) const
{
    if(this->teamId_ == other.teamId_)
        return true;
    return false;
}

int TeamById::getTeamId() const
{
    return this->teamId_;
}

int TeamById::getTeamPoints() const
{
    return this->teamPoints;
}

void TeamById::increaseTeamPoints(int value)
{
    this->teamPoints += value;
}
