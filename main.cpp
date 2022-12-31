#include <iostream>
/*#include "worldcup23a2.h"
#include "Player.h"*/
#include "worldcup23a2.h"
int main()
{




  /*  HashTable playersTable;
    permutation_t per;
    Player tempPlayer(10,std::make_shared<int>(1),per,0,std::make_shared<int>(0),0,false);
    InvertedTree newNode(10,&tempPlayer);
    playersTable.insert(newNode);
    Player tempPlayer2(11,std::make_shared<int>(1),per,0,std::make_shared<int>(0),0,false);
    InvertedTree newNode2(11,&tempPlayer2);
    playersTable.insert(newNode2);
*/






    permutation_t per;
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);

    worldCup.add_player(10,1,per,0,3,0,false);
    worldCup.add_player(11,1,per,1,4,1,false);
    worldCup.add_player(12,1,per,0,3,0,true);

    worldCup.add_player(20,2,per,0,4,0,false);
    worldCup.add_player(21,2,per,0,0,0,false);
    worldCup.add_player(22,2,per,0,7,0,true);
    auto res = worldCup.play_match(1,2);

    worldCup.playersTable.find(20)->Union(worldCup.playersTable.find(12)->find());

    auto y = worldCup.playersTable.find(20);












    return 0;
}
