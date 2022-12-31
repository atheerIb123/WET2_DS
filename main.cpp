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
    worldCup.add_team(100);
    worldCup.add_team(200);
    worldCup.add_team(99);
    worldCup.add_team(500);
    worldCup.add_team(98);

    worldCup.add_player(30,99,per,0,100,0,false);
    worldCup.add_player(60,98,per,0,100,0,false);

    worldCup.add_player(31,500,per,1,0,1,false);


    worldCup.add_player(10,100,per,0,3,0,false);
    worldCup.add_player(11,100,per,1,4,1,false);
    worldCup.add_player(12,100,per,0,3,0,true);

    worldCup.add_player(20,200,per,0,4,0,false);
    worldCup.add_player(21,200,per,0,0,0,false);
    worldCup.add_player(22,200,per,0,10,0,true);


    int a = worldCup.get_ith_pointless_ability(0).ans();
    int b = worldCup.get_ith_pointless_ability(1).ans();
    int c = worldCup.get_ith_pointless_ability(2).ans();
    int d = worldCup.get_ith_pointless_ability(-3).ans();
    int e = worldCup.get_ith_pointless_ability(5).ans();









    return 0;
}
