#ifndef WET2_UF_H
#define WET2_UF_H

#include <iostream>
#include "Player.h"

class InvertedTree {
private:
    int key;
    Player data;
    int gamesRemainder;
    permutation_t spiritRemainder;
    InvertedTree* next;

    void updatePath(InvertedTree *head, InvertedTree *node);
    void updateGamesPlayed(InvertedTree* node);

public:
    permutation_t partialSpirit;
    permutation_t teamSpirit;
    InvertedTree(int key, Player data) : key(key), data(data), gamesRemainder(0), spiritRemainder(permutation_t::neutral()), next(nullptr){}
    InvertedTree(const InvertedTree& invertedTree) = default;
    InvertedTree& operator=(const InvertedTree& invertedTree) = default;
    ~InvertedTree() = default;
    void updatePartialSpirit(InvertedTree *node);
    Player& getData() { return data; }
    int getKey() const {return key;}
    int getTotalGamesPlayed();
    permutation_t findPartialSpirit();
    InvertedTree* find();
    void setSpiritRemainder(permutation_t sp);
    void Union(InvertedTree* root);
    int findValue();
    void incGamesPlayed();
    void multSpirit(permutation_t sp);
};

inline void InvertedTree::updatePath(InvertedTree* head, InvertedTree* node)
{
    if (head == node) {
        return;
    }

    InvertedTree* temp;
    while (node->next) {
        temp = node->next;
        node->next = head;
        node = temp;
    }
}

inline void InvertedTree::updatePartialSpirit(InvertedTree* node)
{
    if (node->next == nullptr) {
        return;
    }

    updatePartialSpirit(node->next);

    if (node->next->next == nullptr) {
        return;
    }
    else {
        node->spiritRemainder = node->next->spiritRemainder * node->spiritRemainder;
    }
}

inline InvertedTree* InvertedTree::find()
{
    InvertedTree* head = this;
    while (head->next) {
        head = head->next;
    }

    updatePartialSpirit(this);
    updateGamesPlayed(this);
    updatePath(head, this);

    return head;
}
inline void InvertedTree::Union(InvertedTree *root)
{
    this->next = root;
    this->gamesRemainder -= root->gamesRemainder;
    this->spiritRemainder = this->spiritRemainder * root->spiritRemainder.inv();
}

inline void InvertedTree::updateGamesPlayed(InvertedTree* node)
{
    if (node->next == nullptr) {
        return;
    }

    updateGamesPlayed(node->next);

    if (node->next->next == nullptr) {
        return;
    }
    else {
        node->gamesRemainder += node->next->gamesRemainder;
    }
}

inline int InvertedTree::findValue()
{
    InvertedTree* parent = find();
    int res =  this->data.getGamesPlayed() + this->gamesRemainder;

    if(this != parent)
    {
        res += parent->getTotalGamesPlayed();
    }

    return res;
}

inline int InvertedTree::getTotalGamesPlayed() {
    return this->gamesRemainder;
}

inline void InvertedTree::incGamesPlayed()
{
    this->gamesRemainder++;
}

inline permutation_t InvertedTree::findPartialSpirit()
{
    InvertedTree* parent = find();
    permutation_t res = permutation_t::neutral();

    if(this != parent)
    {
        res = res * parent->spiritRemainder;
    }

    res = res * this->spiritRemainder;
    res = res * this->partialSpirit;

    return res;
}

inline void InvertedTree::setSpiritRemainder(permutation_t sp)
{
    this->spiritRemainder = sp;
}

inline void InvertedTree::multSpirit(permutation_t sp)
{
    this->spiritRemainder = sp * this->spiritRemainder;
}

#endif