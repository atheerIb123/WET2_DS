//
// Created by USER on 12/26/2022.
//

#include "hashTable.h"

HashTable::HashTable() : size(init_size), counter(0)
{
    players = new LinkedList * [size];
    for (int i = 0; i < size; i++) {
        players[i] = new LinkedList();
    }
}

HashTable::HashTable(const HashTable& hash_table) : size(hash_table.size), counter(hash_table.counter)
{
    this->players = new LinkedList * [size];
    for (int i = 0; i < size; i++) {
        this->players[i] = new LinkedList();
    }
    for (int i = 0; i < size; i++) {
        Node* currentNode = (hash_table.players)[i]->getHead();
        while (currentNode) {
            this->insert((currentNode->data));
            currentNode = currentNode->next;
        }
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < size; i++) {
        if (players[i]) {
            delete players[i];
            size--;
        }
    }
    delete[] players;
}

void HashTable::resize(int new_size, LinkedList* old_players_array[], int old_size)
{
    /*
    size = new_size;
    LinkedList** new_employees_arr = new LinkedList * [new_size];
    for (int i = 0; i < size; i++)
    {
        new_employees_arr[i] = new LinkedList();
    }
    int index = 0;
    for (int i = 0; i < old_size; i++) {
        if (old_employees_array[i]) {
            Node* currentNode = old_employees_array[i]->getHead();
            while (currentNode) {
                index = HashFunction(currentNode->data->getID());
                new_employees_arr[index]->insert(*(currentNode->data));
                currentNode = currentNode->next;
            }
        }
    }
    employees = new_employees_arr;*/


    size = new_size;
    LinkedList* allPlayers = new LinkedList();
    int counter = 0;

    for (int i = 0; i < old_size; i++)
    {
        if (old_players_array[i]) {
            Node* currentNode = old_players_array[i]->getHead();
            while (currentNode)
            {
                allPlayers->insert(*(currentNode->data));
                counter++;
                currentNode->data = nullptr;
                currentNode = currentNode->next;
            }
            delete old_players_array[i];
        }
    }

    delete[] old_players_array;

    LinkedList** new_players_arr = new LinkedList * [size];
    for (int i = 0; i < size; i++)
    {
        new_players_arr[i] = new LinkedList();
    }

    Node* currentNode = allPlayers->getHead();
    for (int i = 0; i < counter; i++)
    {
        InvertedTree* currentPlayer = currentNode->data;
        currentNode->data = nullptr;
        int index = HashFunction(currentPlayer->getData().getPlayerId());
        if (!new_players_arr[index])
        {
            new_players_arr[index] = new LinkedList();
        }
        new_players_arr[index]->insert(*currentPlayer);
        currentNode = currentNode->next;
    }
    delete allPlayers;
    players = new_players_arr;
}

int HashTable::HashFunction(int playerId)
{
    return (playerId % size);
}

InvertedTree* HashTable::find(int player)
{
    int index = HashFunction(player);
    if (players[index]->find(player)) {
        return ((players[index]->find(player))->data); // find in linkedlist
    }
    return nullptr;
}

HashTableStatus HashTable::insert(InvertedTree* player)
{
    if (counter == size / 2) {
        resize(2 * size, players, size);
    }

    int index = HashFunction(player->getData().getPlayerId());

    if (players[index] && find(player->getData().getPlayerId())) {
        return HASH_TABLE_PLAYER_ALREADY_EXISTS;
    }
    players[index]->insert(*player);
    counter++;
    return HASH_TABLE_SUCCESS;
}

HashTableStatus HashTable::remove(InvertedTree& player)
{
    if (counter == size / 4) {
        resize((int)(0.5 * size), players, size);
    }

    int index = HashFunction(player.getData().getPlayerId());
    if (!players[index] || !players[index]->find(player.getData().getPlayerId())) {
        return HASH_TABLE_PLAYER_NOT_FOUND;
    }

    players[index]->remove(player.getData().getPlayerId());
    if (!players[index]->getHead()) {
        delete players[index]; //delete linkedlist
        players[index] = new LinkedList();
    }
    counter--;
    return HASH_TABLE_SUCCESS;
}

/*void HashTable::updateEmployeesCompanyID(int acquirerID)
{
    for (int hashIndex = 0; hashIndex < size; hashIndex++) {
        employees[hashIndex]->updateEmployeesCompanyID(acquirerID);
    }
}*/

/*void HashTable::mergeTwoHashies(HashTable* acquirer, HashTable* target)
{
    int target_size = target->getSize();
    LinkedList* target_employees = new LinkedList();

    for (int i = 0; i < target_size; i++) {
        Node* currentNode = (target->employees)[i]->getHead();
        while(currentNode) {
            target_employees->insert(*(currentNode->data));
            currentNode = currentNode->next;
        }
        delete (target->employees[i]);
    }

    delete[] target->employees;

    for (int i = 0; i < target_size; i++) {
        Node* currentNode = target_employees->getHead();
        while(currentNode) {
            acquirer->insert(*(currentNode->data));
            currentNode = currentNode->next;
        }
    }

    delete target_employees;
}*/

void HashTable::deletePlayers() {
    for (int i = 0; i < size; i++) {
        if (players[i]) {
            delete players[i];
        }
        size--;
    }
    delete[] players;

}