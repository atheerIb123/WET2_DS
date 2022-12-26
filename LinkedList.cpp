#include "LinkedList.h"

Node::Node(const Player& player) : data(new Player(player)), next(nullptr) {}

Node::Node(const Node& node)
{
    data = new Player(*(node.data));
    if (node.next) {
        next = new Node(*(node.next));
    }
    else {
        next = nullptr;
    }
}

Node& Node::operator=(const Node& node)
{
    if (this == &node) {
        return *this;
    }
    data = new Player(*(node.data));
    if (node.next != nullptr) {
        delete this->next;
        next = new Node(*(node.next));
    }
    else {
        next = nullptr;
    }
    return *this;
}

Node::~Node()
{
    delete data;
}

LinkedList::LinkedList() : head(nullptr), size(0) {}

LinkedList::LinkedList(const LinkedList& linked_list)
{
    head = nullptr;
    Node* current_node = linked_list.head;

    while (current_node != nullptr) {
        this->insert(*(current_node->data));
        current_node = current_node->next;
    }
    size = linked_list.size;
}

LinkedList& LinkedList::operator=(const LinkedList& linked_list)
{
    if (this != &linked_list) {
        this->~LinkedList();
        Node* currentNode = linked_list.head;
        while (currentNode) {
            this->insert(*(linked_list.head->data));
            currentNode = currentNode->next;
        }
        size = linked_list.size;
    }
    return *this;
}

LinkedList::~LinkedList()
{
    Node* current_node = head;
    while (current_node != nullptr) {
        Node* next = current_node->next;
        delete current_node;
        current_node = next;

        size--;
    }
}

void LinkedList::insert(const Player& player)
{
    Node* node_to_add = new Node(player);
    if (head == nullptr) {
        head = node_to_add;
    }
    else {
        Node* currentNode = head;
        while (currentNode->next) {
            currentNode = currentNode->next;
        }
        currentNode->next = node_to_add;
    }
    size++;
}

void LinkedList::remove(const int id)
{
    if (!head) {
        return;
    }
    Node* currentNode = head;
    if (currentNode->data->getPlayerId() == id) {
        head = head->next;
        delete currentNode;
        size--;
        return;
    }
    while (currentNode->next) {
        if (currentNode->next->data->getPlayerId() == id) {
            Node* toDelete = currentNode->next;
            Node* tempNode = toDelete->next;
            currentNode->next = tempNode;
            delete toDelete;
            size--;
            return;
        }
        currentNode = currentNode->next;
    }
}

Node* LinkedList::find(const int id)
{
    if (head) {
        Node* currentNode = head;
        while (currentNode) {
            if (currentNode->data->getPlayerId() == id) {
                return currentNode;
            }
            currentNode = currentNode->next;
        }
    }
    return nullptr;
}

Player* LinkedList::getPlayerData(Node* node)
{
    if (node) {
        return node->data;
    }
    return nullptr;
}

void LinkedList::setHead(Node* newHead)
{
    if (newHead) {
        head = newHead;
    }
}

void LinkedList::updateEmployeesCompanyID(int acquirerID)
{
    /*Node* currentNode = head;
    while (currentNode) {
        currentNode->data->setEmployerID(acquirerID);
        currentNode = currentNode->next;
    }*/
}