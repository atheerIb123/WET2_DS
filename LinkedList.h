//
// Created by USER on 12/26/2022.
//

#ifndef WET2_LINKEDLIST_H
#define WET2_LINKEDLIST_H

#include <iostream>
#include "UF.h"

class Node {
public:
    Node(const InvertedTree& player);
    Node(InvertedTree* player);
    Node(const Node& node);
    Node& operator=(const Node& node);
    ~Node();

    InvertedTree* data;
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

    void insert(const InvertedTree& player);
    void insertWithPtr(InvertedTree* player);
    void remove(const int id);
    Node* find(const int id);
    Player& getPlayerData(Node* node);
    void setHead(Node* newHead);
    Node* getHead() { return head; }
    int getSize() { return size; }

};


#endif //WET2_LINKEDLIST_H
