#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include <iostream>
#include "LinkedList.h"

typedef enum {
    HASH_TABLE_SUCCESS = 0,
    HASH_TABLE_PLAYER_NOT_FOUND = -1,
    HASH_TABLE_ALLOCATION_ERROR = -2,
    HASH_TABLE_PLAYER_ALREADY_EXISTS = -4,
} HashTableStatus;

class HashTable {
private:
    int size;
    int counter;
    LinkedList* players;
    static const int init_size = 8;

public:
    HashTable();
    HashTable (const HashTable& hash_table);
    HashTable& operator=(const HashTable& node) = default;
    ~HashTable();

    void resize(int new_size, LinkedList* old_players_array, int old_size);
    int HashFunction(int playerId);
    InvertedTree* find(int playerId);

    HashTableStatus insert(InvertedTree* player);
    HashTableStatus remove(InvertedTree& player);
    int getCounter() { return counter; }
    int getSize() { return size; }
    void deletePlayers();
};

#endif //WET2_HASHTABLE_H
