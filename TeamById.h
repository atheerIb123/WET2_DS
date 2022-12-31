//
// Created by zaher.amir on 26/12/2022.
//

#include "wet2util.h"
#include <memory>
#include "Player.h"
#ifndef WETTTTT_TEAMBYID_H
#define WETTTTT_TEAMBYID_H


class TeamById {
private:
    int playersNum;
    int teamId_;
    int allPlayersAbility;
    int teamPoints;
    bool hasGK;
    permutation_t teamSpirit;
    std::shared_ptr<int> gamesPlayed;
public:
    Player captain;
    TeamById() = default;
    TeamById(int teamId_);
    TeamById(const TeamById& other) = default;
    TeamById& operator=(const TeamById& other) = default;
    ~TeamById() = default;
    int getTeamId() const;
    int getPlayersNum() const;
    bool isLegalTeam() const;
    void setTeamIsLegal();
    void increaseTeamAbility(int value);
    void addPlayerToCount();
    void decreaseTeamAbility(int value);
    void increaseGamesPlayed(int value);
    int getGamesPlayed() const;
    int getTeamPoints() const;
    int getTeamAbility() const;
    void increaseTeamPoints(int value);
    void mulPer(const permutation_t& other);
    bool operator<(const TeamById& other) const;
    bool operator>(const TeamById& other) const;
    bool operator==(const TeamById& other) const;





};


#endif //WETTTTT_TEAMBYID_H
