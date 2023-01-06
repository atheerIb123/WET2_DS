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

    if(this->teamsIdTree.search(teamsIdTree.getRoot(),t) != nullptr)
    {
        return StatusType::FAILURE;
    }


    if(this->teamsIdTree.getRoot())
    {
        this->teamsIdTree.Insert(t);
        TeamByStats tempStats(teamId);
        this->teamsStatsTree.Insert(tempStats);
        this->teamsIdTree.updateNodesNum(true);
        this->teamsStatsTree.updateNodesNum(true);
        return StatusType::SUCCESS;
    }


    this->teamsIdTree.Insert(t);
    TeamByStats tempStats(teamId);
    this->teamsStatsTree.Insert(tempStats);
    this->teamsIdTree.updateNodesNum(true);
    this->teamsStatsTree.updateNodesNum(true);
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

    if(team->key_.getPlayersNum() != 0)
        this->playersTable.find(team->key_.captain.getPlayerId())->getData().eliminatePlayer();

    teamsStatsTree.Remove(teamSt->key_);
    teamsIdTree.Remove(x);
    this->teamsIdTree.updateNodesNum(false);
    this->teamsStatsTree.updateNodesNum(false);
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper) {
    // TODO: Your code goes here
    if (playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || cards < 0 || spirit.isvalid() == false)
        return StatusType::INVALID_INPUT;

    TeamById tempId(teamId);
    treeNode<TeamById>* team = teamsIdTree.search(teamsIdTree.getRoot(),tempId);

    if(team == nullptr || (this->playersTable.find(playerId) != nullptr && this->playersTable.find(playerId)->getData().getPlayerId() == playerId))
        return StatusType::FAILURE;




    Player tempPlayer(playerId,std::make_shared<int>(teamId),spirit,gamesPlayed,std::make_shared<int>(cards),ability,goalKeeper);
    tempPlayer.setGamesPlayedWithTeam(team->key_.getGamesPlayedPointer());
    InvertedTree newNode(playerId, tempPlayer);
    this->playersTable.insert(&newNode);
    TeamByStats teamStats(teamId);
    teamStats.increaseTeamAbility(team->key_.getTeamAbility());
    team->key_.increaseTeamAbility(ability);
    team->key_.mulPer(spirit);

    this->teamsStatsTree.Remove(teamStats);
    teamStats.increaseTeamAbility(ability);
    this->teamsStatsTree.Insert(teamStats);

    if(team->key_.getPlayersNum() == 0)
    {
        team->key_.captain = tempPlayer;
        playersTable.find(playerId)->partialSpirit = team->key_.getTeamSpirit();
    }
    team->key_.addPlayerToCount();
    if(goalKeeper == true)
    {
        team->key_.setTeamIsLegal();
    }
    if(team->key_.captain.getPlayerId() != playerId)
    {
        playersTable.find(playerId)->Union(playersTable.find(team->key_.captain.getPlayerId()));
        playersTable.find(playerId)->partialSpirit = team->key_.getTeamSpirit();
    }

    playersTable.find(team->key_.captain.getPlayerId())->teamSpirit = team->key_.getTeamSpirit();

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    TeamById temp1(teamId1);
    TeamById temp2(teamId2);
    treeNode<TeamById>* team1 = this->teamsIdTree.search(teamsIdTree.getRoot(),temp1);
    treeNode<TeamById>* team2 = this->teamsIdTree.search(teamsIdTree.getRoot(),temp2);
    if(team1 == nullptr || team2 == nullptr)
        return StatusType::FAILURE;

    if(!team1->key_.isLegalTeam() || !team2->key_.isLegalTeam())
        return StatusType::FAILURE;


    InvertedTree* captain1 = playersTable.find(team1->key_.captain.getPlayerId());
    InvertedTree* captain2 = playersTable.find(team2->key_.captain.getPlayerId());

    captain1->incGamesPlayed();
    captain2->incGamesPlayed();

    if(team1->key_.getTeamAbility() + team1->key_.getTeamPoints() > team2->key_.getTeamAbility() + team2->key_.getTeamPoints())
    {//team1 wins
        team1->key_.increaseTeamPoints(3);
        team1->key_.increaseGamesPlayed(1);
        team2->key_.increaseGamesPlayed(1);
        return 1;
        return StatusType::SUCCESS;
    }
    else if(team1->key_.getTeamAbility() + team1->key_.getTeamPoints() < team2->key_.getTeamAbility() + team2->key_.getTeamPoints())
    {//team2 wins
        team2->key_.increaseTeamPoints(3);
        team1->key_.increaseGamesPlayed(1);
        team2->key_.increaseGamesPlayed(1);
        return 3;
        return StatusType::SUCCESS;

    }
    else
    {//same abilities
        if(team1->key_.getTeamSpirit().strength() > team2->key_.getTeamSpirit().strength())
        {
            team1->key_.increaseTeamPoints(3);
            team1->key_.increaseGamesPlayed(1);
            team2->key_.increaseGamesPlayed(1);
            return 2;
            return StatusType::SUCCESS;

        }
        else if(team1->key_.getTeamSpirit().strength() < team2->key_.getTeamSpirit().strength())
        {
            team2->key_.increaseTeamPoints(3);
            team1->key_.increaseGamesPlayed(1);
            team2->key_.increaseGamesPlayed(1);
            return 4;
            return StatusType::SUCCESS;

        }
        else
        {//tie
            team1->key_.increaseTeamPoints(1);
            team2->key_.increaseTeamPoints(1);
            team1->key_.increaseGamesPlayed(1);
            team2->key_.increaseGamesPlayed(1);
            return 0;
            return StatusType::SUCCESS;

        }
    }
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	if(playerId <= 0)
        return StatusType::INVALID_INPUT;
    if(this->playersTable.find(playerId) == nullptr)
    {
        return StatusType::FAILURE;
    }


    InvertedTree* playerNode = this->playersTable.find(playerId);

    return playerNode->findValue();
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
    if(playerId <= 0 || cards < 0)
        return StatusType::INVALID_INPUT;


    auto player = this->playersTable.find(playerId);
    if(this->playersTable.find(playerId) == nullptr || player->find()->getData().isEliminated())
    {
        return StatusType::FAILURE;
    }

    player->getData().addCards(cards);

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
    if(playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(this->playersTable.find(playerId) == nullptr)
    {
        return StatusType::FAILURE;
    }

    return playersTable.find(playerId)->getData().getCardsAmount();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;


    TeamById temp(teamId);
    treeNode<TeamById>* team = teamsIdTree.search(teamsIdTree.getRoot(),temp);
    if(team == nullptr)
        return  StatusType::FAILURE;

    return team->key_.getTeamPoints();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{


    if(i < 0 || teamsIdTree.getNodesNum() == 0 || i >= this->teamsIdTree.getNodesNum() )
    {
        return StatusType::FAILURE;
    }

    int res = teamsStatsTree.select(i + 1)->key_.getTeamId();
	return (res);
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
    if(playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }


    if(playersTable.find(playerId) == nullptr || playersTable.find(playerId)->find()->getData().isEliminated())
    {
        return StatusType::FAILURE;
    }

    return playersTable.find(playerId)->findPartialSpirit();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) {
    // TODO: Your code goes here
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
        return StatusType::INVALID_INPUT;
    }


    TeamById tId1(teamId1);
    TeamById tId2(teamId2);
    TeamByStats St1(teamId1);
    TeamByStats St2(teamId2);

    treeNode<TeamById>* firstTeam = this->teamsIdTree.search(teamsIdTree.getRoot(),tId1);
    treeNode<TeamById>* secondTeam = this->teamsIdTree.search(teamsIdTree.getRoot(),tId2);

    if(firstTeam == nullptr || secondTeam == nullptr)
    {
        return StatusType::FAILURE;
    }
  
    St1.increaseTeamAbility(firstTeam->key_.getTeamAbility());
    St2.increaseTeamAbility(secondTeam->key_.getTeamAbility());
    treeNode<TeamByStats>* firstStats = this->teamsStatsTree.search(teamsStatsTree.getRoot(),St1);
    treeNode<TeamByStats>* secondStats = this->teamsStatsTree.search(teamsStatsTree.getRoot(),St2);


    if(secondTeam->key_.getPlayersNum() == 0)
    {
        remove_team(teamId2);
        //return StatusType::SUCCESS;
    }
    else if(firstTeam->key_.getPlayersNum() == 0)
    {
        remove_team(teamId1);
        secondTeam = teamsIdTree.search(teamsIdTree.getRoot(), tId2);
        secondStats = teamsStatsTree.search(teamsStatsTree.getRoot(), St2);
        TeamById temp = secondTeam->key_;
        TeamByStats tempSt = secondStats->key_;
        temp.setPlayersCount(secondTeam->key_.getPlayersNum());
        if(secondTeam->key_.isLegalTeam())
            temp.setTeamIsLegal();
        teamsIdTree.Remove(temp);
        teamsStatsTree.Remove(tempSt);
        temp.setId(teamId1);
        tempSt.setId(teamId1);

        teamsIdTree.Insert(temp);
        teamsStatsTree.Insert(tempSt);

    }
    else
    {
        if(secondTeam->key_.isLegalTeam())
            firstTeam->key_.setTeamIsLegal();
        firstTeam->key_.setPlayersCount(firstTeam->key_.getPlayersNum() + secondTeam->key_.getPlayersNum());
        if(firstTeam->key_.getPlayersNum() >= secondTeam->key_.getPlayersNum())
        {
            firstTeam->key_.increaseTeamPoints(secondTeam->key_.getTeamPoints());
            TeamByStats st = firstStats->key_;
            this->teamsStatsTree.Remove(st);
            st.increaseTeamAbility(secondTeam->key_.getTeamAbility());
            firstTeam->key_.increaseTeamAbility(secondTeam->key_.getTeamAbility());
            this->teamsStatsTree.Insert(st);
            InvertedTree* firstCaptain = playersTable.find(firstTeam->key_.captain.getPlayerId());
            InvertedTree* secondCaptain = playersTable.find(secondTeam->key_.captain.getPlayerId());
            secondCaptain->Union(firstCaptain);
            secondCaptain->multSpirit(firstTeam->key_.getTeamSpirit());
        }
        else
        {
            firstTeam->key_.increaseTeamPoints(secondTeam->key_.getTeamPoints());

            TeamByStats st = firstStats->key_;
            this->teamsStatsTree.Remove(st);
            st.increaseTeamAbility(secondTeam->key_.getTeamAbility());
            this->teamsStatsTree.Insert(st);

            InvertedTree* firstCaptain = playersTable.find(firstTeam->key_.captain.getPlayerId());
            InvertedTree* secondCaptain = playersTable.find(secondTeam->key_.captain.getPlayerId());

            secondCaptain->getData().setGamesPlayedWithTeam(firstTeam->key_.captain.getGamesPlayedWithTeam());
            firstCaptain->Union(secondCaptain);
            firstTeam->key_.captain = secondTeam->key_.captain;

            std::shared_ptr<int> newTeamId = std::make_shared<int>(teamId1);

            firstTeam->key_.captain.setTeamId(newTeamId);
            firstTeam->key_.increaseTeamAbility(secondTeam->key_.getTeamAbility());
            playersTable.find(firstTeam->key_.captain.getPlayerId())->getData().setTeamId(newTeamId);
            secondTeam->key_.captain = firstCaptain->getData();

            firstCaptain->multSpirit(firstTeam->key_.getTeamSpirit().inv());
            secondCaptain->multSpirit(firstTeam->key_.getTeamSpirit());
        }
        firstTeam->key_.mulPer(secondTeam->key_.getTeamSpirit());
        remove_team(teamId2);
    }

    return StatusType::SUCCESS;
}
