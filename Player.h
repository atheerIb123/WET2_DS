//
// Created by USER on 12/26/2022.
//

#ifndef WET2_PLAYER_H
#define WET2_PLAYER_H
#include "wet2util.h"
#include <memory>

using std::shared_ptr;

class Player {
private:
    int playerId;
    shared_ptr<int> teamId;
    permutation_t spirit;
    int gamesPlayed;
    shared_ptr<int> gamesPlayedWithTeam;
    int ability;
    shared_ptr<int> cards;
    bool goalKeeper;

public:
    Player();
    Player(int playerId, shared_ptr<int> teamId, const permutation_t& sp, int gamesPlayed, shared_ptr<int> cards, int ability, bool goalKeeper);
    Player(const Player& other) = default;
    Player& operator=(const Player& other) = default;
    ~Player() = default;

    void setGamesPlayedWithTeam(std::shared_ptr<int> games);
    int getGamesPlayed() const;
    void addCards(int amount);
    int getCardsAmount() const;
    int getPlayerId() const;
    permutation_t& getPermutation();
};


#endif //WET2_PLAYER_H
