//
// Created by zaher.amir on 26/12/2022.
//

#include "TeamByStats.h"

TeamByStats::TeamByStats(int teamId)
{
    this->teamId = teamId;
    this->allPlayersAbility = 0;

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

void TeamByStats::increaseTeamAbility(int value)
{
    this->allPlayersAbility += value;
}
void TeamByStats::decreaseTeamAbility(int value)
{
    this->allPlayersAbility -= value;
}
int TeamByStats::getTeamAbility() const
{
    return this->allPlayersAbility;
}
void TeamByStats::setId(int id)
{
    this->teamId = id;
}


