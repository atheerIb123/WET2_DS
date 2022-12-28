#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
    this->teamsIdTree.n = 0;
    this->teamsStatsTree.n = 0;

    // TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{
	// TODO: Your code goes here
    if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    TeamByStats tempSt(teamId);
    TeamById tempId(teamId);
    
    auto r = this->teamsIdTree.getRoot();
    if(this->teamsIdTree.getRoot() == nullptr)
    {
        this->teamsIdTree.insert(&tempId);
        TeamByStats tempStats(teamId);
        this->teamsStatsTree.insert(&tempStats);
        return StatusType::SUCCESS;
    }
    if(this->teamsIdTree.search(teamsIdTree.getRoot(),&tempId) != nullptr)
    {
        return StatusType::FAILURE;
    }
    this->teamsIdTree.insert(&tempId);
    TeamByStats tempStats(teamId);
    this->teamsStatsTree.insert(&tempStats);
    
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
    if (1 != 1)
        return StatusType::SUCCESS;
    TeamById t(1);
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
