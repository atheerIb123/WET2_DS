#include <iostream>
#include "Player.h"

class InvertedTree {
private:
    int key;
    Player data;
    int size;
    long double acquired_value;
    InvertedTree* next;

    void updatePath(InvertedTree *head, InvertedTree *node);


public:
    permutation_t partialSpirit;
    permutation_t teamSpirit;
    InvertedTree(int key, Player data) : key(key), data(data), size(1), next(nullptr) {}
    InvertedTree(const InvertedTree& invertedTree) = default;
    InvertedTree& operator=(const InvertedTree& invertedTree) = default;
    ~InvertedTree() = default;
    void updatePartialSpirit(InvertedTree *node);
    Player& getData() { return data; }
    int getKey() const {return key;}
    long double getAcquiredValue() { return acquired_value; }
    InvertedTree* find();
    void Union(InvertedTree* root);
    void findValue(InvertedTree* node, long double* value);
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
    if (node->next->next == nullptr)
    {
        return;
    }
    else
    {
        node->partialSpirit = node->next->next->teamSpirit * node->partialSpirit;
    }
}
inline InvertedTree* InvertedTree::find()
{
    InvertedTree* head = this;
    while (head->next) {
        head = head->next;
    }

    updatePartialSpirit(this);
    updatePath(head, this);

    return head;
}
inline void InvertedTree::Union(InvertedTree *root)
{
    this->next = root;
}
