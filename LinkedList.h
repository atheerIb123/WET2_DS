//
// Created by USER on 12/26/2022.
//

#ifndef WET2_LINKEDLIST_H
#define WET2_LINKEDLIST_H

#include <iostream>
#include "Player.h"

class Node {
public:
    Node(const Player& employee);
    Node(const Node& node);
    Node& operator=(const Node& node);
    ~Node();

    Player* data;
    Node* next;
};

class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList();
    LinkedList(const LinkedList& linked_list);
    LinkedList& operator=(const LinkedList& linked_list);
    ~LinkedList();

    void insert(const Player& employee);
    void remove(const int id);
    Node* find(const int id);
    Player* getPlayerData(Node* node);
    void setHead(Node* newHead);
    Node* getHead() { return head; }
    int getSize() { return size; }

    void updateEmployeesCompanyID(int acquirerID);
};


#endif //WET2_LINKEDLIST_H
