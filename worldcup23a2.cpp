#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{


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
    TeamById t(teamId);

    if(this->teamsIdTree.getRoot())
    {
        this->teamsIdTree.Insert(t);
        TeamByStats tempStats(teamId);
        this->teamsStatsTree.Insert(tempStats);
        return StatusType::SUCCESS;
    }
    if(this->teamsIdTree.search(teamsIdTree.getRoot(),t) != nullptr)
    {
        return StatusType::FAILURE;
    }
    this->teamsIdTree.Insert(t);
    TeamByStats tempStats(teamId);
    this->teamsStatsTree.Insert(tempStats);

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    TeamById x(teamId);
    treeNode<TeamById>* team = teamsIdTree.search(teamsIdTree.getRoot(), x);

    if(team == nullptr)
    {
        return StatusType::FAILURE;
    }

    TeamByStats teamStats(teamId);
    teamStats.increaseTeamAbility(team->key_.getTeamAbility());
    treeNode<TeamByStats>* teamSt = teamsStatsTree.search(teamsStatsTree.getRoot(), teamStats);

    teamsStatsTree.Remove(teamSt->key_);
    teamsIdTree.Remove(x);

    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
    if(playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || cards < 0 /*|| spirit.isvalid() == false*/)
        return StatusType::INVALID_INPUT;

    TeamById tempId(teamId);
    treeNode<TeamById>* team = teamsIdTree.search(teamsIdTree.getRoot(),tempId);
    if(team == nullptr || (this->playersTable.find(playerId) != nullptr && this->playersTable.find(playerId)->getData().getPlayerId() == playerId))
        return StatusType::FAILURE;



    Player tempPlayer(playerId,std::make_shared<int>(teamId),spirit,gamesPlayed,std::make_shared<int>(cards),ability,goalKeeper);
    tempPlayer.setGamesPlayedWithTeam(std::make_shared<int>(team->key_.getGamesPlayed()));
    InvertedTree newNode(playerId, tempPlayer);
    this->playersTable.insert(&newNode);
    TeamByStats teamStats(teamId);
    teamStats.increaseTeamAbility(team->key_.getTeamAbility());
    team->key_.increaseTeamAbility(ability);
    team->key_.mulPer(spirit);

    this->teamsStatsTree.Remove(teamStats);
    teamStats.increaseTeamAbility(team->key_.getTeamAbility());
    this->teamsStatsTree.Insert(teamStats);

    if(team->key_.getPlayersNum() == 0)
    {
        team->key_.captain = tempPlayer;
    }
    team->key_.addPlayerToCount();
    if(goalKeeper == true)
    {
        team->key_.setTeamIsLegal();
    }
    if(team->key_.captain.getPlayerId() != playerId)
        this->playersTable.find(playerId)->find()->Union(new InvertedTree(team->key_.captain.getPlayerId(), team->key_.captain));
    
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
