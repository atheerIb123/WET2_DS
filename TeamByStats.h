//
// Created by zaher.amir on 26/12/2022.
//

#include "wet2util.h"
#include <memory>
#ifndef WETTTTT_TEAMBYSTATS_H
#define WETTTTT_TEAMBYSTATS_H


class TeamByStats {
private:
    int allPlayersAbility;
    int teamId;
public:
    TeamByStats() = default;
    TeamByStats(int teamId);
    TeamByStats(const TeamByStats& other) = default;
    TeamByStats& operator=(const TeamByStats& other) = default;
    ~TeamByStats() = default;
    int getTeamId() const;
    bool isLegalTeam() const;
    void increaseTeamAbility(int value);
    void decreaseTeamAbility(int value);
    void increseGamesPlayed(int value);
    int getGamesPlayed(int value) const;
    bool operator<(const TeamByStats& other) const;
    bool operator>(const TeamByStats& other) const;
    bool operator==(const TeamByStats& other) const;

};


#endif //WETTTTT_TEAMBYSTATS_H
