//
// Created by zaher.amir on 26/12/2022.
//

#include "TeamById.h"


TeamById::TeamById(int teamId)
{
    this->playersNum = 0;
    this->teamPoints = 0;
    this->allPlayersAbility = 0;
    teamId_ = teamId;
    hasGK = false;
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

int TeamById::getTeamAbility() const
{
    return this->allPlayersAbility;
}

int TeamById::getPlayersNum() const
{
    return this->playersNum;
}

void TeamById::addPlayerToCount()
{
    this->playersNum++;
}

void TeamById::setTeamIsLegal()
{
    this->hasGK = true;
}

bool TeamById::isLegalTeam() const
{
    return hasGK;
}

void TeamById::mulPer(const permutation_t &other)
{
    this->teamSpirit = this->teamSpirit * other;
}

permutation_t TeamById::getTeamSpirit() const
{
    return this->teamSpirit;
}

std::shared_ptr<int> TeamById::getGamesPlayedPointer() const
{
    return this->gamesPlayed;
}
