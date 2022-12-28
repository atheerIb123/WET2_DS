#include <iostream>
#include "Player.h"
#include "hashTable.h"

class InvertedTree {
private:
    int key;
    Player *data;
    int size;
    long double acquired_value;
    InvertedTree* next;

    void updatePath(InvertedTree *head, InvertedTree *node);

    void updateAcquiredValue(InvertedTree *node);

public:
    InvertedTree(int key, Player* data) : key(key), data(data), size(1), acquired_value(0), next(nullptr) {}
    InvertedTree(const InvertedTree& invertedTree) = default;
    InvertedTree& operator=(const InvertedTree& invertedTree) = default;
    ~InvertedTree() = default;

    Player* getData() { return data; }
    long double getAcquiredValue() { return acquired_value; }
    InvertedTree* find();
    void Union(InvertedTree* root);
    void findValue(InvertedTree* node, long double* value);
    void Union(InvertedTree* group1, InvertedTree* group2, double factor, InvertedTree* owner);
    void mergeTeamsTrees(Player* rootAcquirer, Player* targetCompany);
    void mergeTeamsHashies(Player* rootAcquirer, Player* targetCompany);
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
inline void InvertedTree::updateAcquiredValue(InvertedTree* node)
{
    if (node->next == nullptr) {
        return;
    }
    updateAcquiredValue(node->next);
    if (node->next->next == nullptr) {
        return;
    }
    else {
        node->acquired_value += node->next->acquired_value;
    }
}
inline InvertedTree* InvertedTree::find()
{
    InvertedTree* head = this;
    while (head->next) {
        head = head->next;
    }

    updateAcquiredValue(this);
    updatePath(head, this);

    return head;
}
inline void InvertedTree::Union(InvertedTree *root)
{
    this->next = root;
}
