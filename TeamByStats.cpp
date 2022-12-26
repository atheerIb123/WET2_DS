//
// Created by zaher.amir on 26/12/2022.
//

#include "TeamByStats.h"

TeamByStats::TeamByStats(int teamId, int a)
{
    this->teamId = teamId;
    this->allPlayersAbility = a;
    this->gamesPlayed = std::make_shared<int>(0);
    this->teamSpirit;
}

bool TeamByStats::operator<(const TeamByStats &other) const
{
    if(this->allPlayersAbility < other.allPlayersAbility)
    {
        return true;
    }
    else if(this->allPlayersAbility == other.allPlayersAbility && (this->teamId < other.teamId))
    {
        return true;
    }
    return false;
}

bool TeamByStats::operator>(const TeamByStats &other) const
{
    if(this ->allPlayersAbility > other.allPlayersAbility)
    {
        return true;
    }
    else if(this->allPlayersAbility == other.allPlayersAbility && (this->teamId > other.teamId))
    {
        return true;
    }
    return false;
}

bool TeamByStats::operator==(const TeamByStats &other) const
{
    if(this->teamId == other.teamId)
        return true;
    return false;
}

int TeamByStats::getTeamId() const
{
    return this->teamId;
}
int TeamByStats::getGamesPlayed(int value) const
{
    return *this->gamesPlayed;
}
void TeamByStats::increaseTeamAbility(int value)
{
    this->allPlayersAbility += value;
}
void TeamByStats::decreaseTeamAbility(int value)
{
    this->allPlayersAbility -= value;
}
void TeamByStats::increseGamesPlayed(int value)
{
    *this->gamesPlayed += value;
};

