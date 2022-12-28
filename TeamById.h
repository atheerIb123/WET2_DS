//
// Created by zaher.amir on 26/12/2022.
//

#include "wet2util.h"
#include <memory>

#ifndef WETTTTT_TEAMBYID_H
#define WETTTTT_TEAMBYID_H


class TeamById {
private:
    int teamId_;
    int allPlayersAbility;
    int teamPoints;
    bool hasGK;
    permutation_t teamSpirit;
    std::shared_ptr<int> gamesPlayed;
public:
    TeamById() = default;
    TeamById(int teamId_);
    TeamById(const TeamById& other) = default;
    TeamById& operator=(const TeamById& other) = delete;
    ~TeamById() = default;
    int getTeamId() const;
    bool isLegalTeam() const;
    void increaseTeamAbility(int value);
    void decreaseTeamAbility(int value);
    void increaseGamesPlayed(int value);
    int getGamesPlayed() const;
    int getTeamPoints() const;
    void increaseTeamPoints(int value);
    bool operator<(const TeamById& other) const;
    bool operator>(const TeamById& other) const;
    bool operator==(const TeamById& other) const;





};


#endif //WETTTTT_TEAMBYID_H
