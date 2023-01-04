#include "Player.h"

Player::Player()
{
    this->playerId = 0;
    this->gamesPlayed = -1;
    this->goalKeeper = false;
    this->cards = nullptr;
    this->teamId = nullptr;
    this->ability = 0;
    this->spirit = permutation_t::neutral();
}
Player::Player(int id)
{
    this->playerId = id;
    this->gamesPlayed = -1;
    this->goalKeeper = false;
    this->cards = nullptr;
    this->teamId = nullptr;
    this->ability = 0;
    this->spirit = permutation_t::invalid();

}

Player::Player(int playerId, shared_ptr<int> teamId, const permutation_t& sp, int gamesPlayed, shared_ptr<int> cards, int ability, bool goalKeeper)
{
    this->playerId = playerId;
    this->teamId = teamId;
    this->spirit = sp;
    this->gamesPlayed = gamesPlayed;
    this->cards = cards;
    this->ability = ability;
    this->goalKeeper = goalKeeper;
    this->eliminated = false;
    this->spirit = permutation_t::neutral();
}


void Player::setGamesPlayedWithTeam(std::shared_ptr<int> games)
{
    this->gamesPlayedWithTeam = games;
}

int Player::getCardsAmount() const
{
    return this->cards.operator*();
}

int Player::getGamesPlayed() const
{
    return this->gamesPlayed;
}

void Player::addCards(int amount)
{
    *this->cards += amount;
}

int Player::getPlayerId() const
{
    return this->playerId;
}
permutation_t& Player::getPermutation()
{
    return this->spirit;
}

void Player::eliminatePlayer()
{
    this->eliminated = true;
}
bool Player::isEliminated() const
{
    return this->eliminated;
}

std::shared_ptr<int>& Player::getGamesPlayedWithTeam()
{
    return this->gamesPlayedWithTeam;
}

void Player::setTeamId(shared_ptr<int>& newTeamIdPtr)
{
    this->teamId = newTeamIdPtr;
}
