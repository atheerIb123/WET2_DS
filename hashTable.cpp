//
// Created by USER on 12/26/2022.
//

#include "hashTable.h"

HashTable::HashTable() : size(init_size), counter(0)
{
    players = new LinkedList[size];
}

HashTable::HashTable(const HashTable& hash_table) : size(hash_table.size), counter(hash_table.counter)
{
    this->players = new LinkedList[size];

    for (int i = 0; i < size; i++) {
        Node* currentNode = (hash_table.players)[i].getHead();
        while (currentNode) {
            this->insert((currentNode->data));
            currentNode = currentNode->next;
        }
    }
}

HashTable::~HashTable()
{
    delete[] players;
}

void HashTable::resize(int new_size, LinkedList* old_players_array, int old_size)
{
    size = new_size;
    LinkedList* allPlayers = new LinkedList();
    int counter = 0;

    for (int i = 0; i < old_size; i++)
    {
        if (old_players_array[i].getHead()) {
            Node* currentNode = old_players_array[i].getHead();
            while (currentNode)
            {
                allPlayers->insertWithPtr((currentNode->data));
                counter++;
                currentNode->data = nullptr;
                currentNode = currentNode->next;
            }
        }
    }

    delete[] old_players_array;

    players = new LinkedList[size];

    Node* currentNode = allPlayers->getHead();
    for (int i = 0; i < counter; i++)
    {
        InvertedTree* currentPlayer = currentNode->data;
        currentNode->data = nullptr;
        int index = HashFunction(currentPlayer->getData().getPlayerId());

        players[index].insertWithPtr(currentPlayer);
        currentNode = currentNode->next;
    }
    delete allPlayers;
}

int HashTable::HashFunction(int playerId)
{
    return (playerId % size);
}

InvertedTree* HashTable::find(int player)
{
    int index = HashFunction(player);
    if (players[index].find(player)) {
        return ((players[index].find(player))->data); // find in linkedlist
    }
    return nullptr;
}

HashTableStatus HashTable::insert(InvertedTree* player)
{
    if (counter == size / 2) {
        resize(2 * size, players, size);
    }

    int index = HashFunction(player->getData().getPlayerId());

    if (players[index].getHead() && find(player->getData().getPlayerId())) {
        return HASH_TABLE_PLAYER_ALREADY_EXISTS;
    }
    players[index].insert(*player);
    counter++;
    return HASH_TABLE_SUCCESS;
}

HashTableStatus HashTable::remove(InvertedTree& player)
{
    if (counter == size / 4) {
        resize((int)(0.5 * size), players, size);
    }

    int index = HashFunction(player.getData().getPlayerId());
    if (!players[index].getHead() || !players[index].find(player.getData().getPlayerId())) {
        return HASH_TABLE_PLAYER_NOT_FOUND;
    }

    players[index].remove(player.getData().getPlayerId());
    counter--;
    return HASH_TABLE_SUCCESS;
}

void HashTable::deletePlayers() {
    delete players;
}