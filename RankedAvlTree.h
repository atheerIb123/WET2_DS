#include<iostream>
using namespace std;

template<class T>
class node
{
public:
    T* key;
    int nleft;
    int height;
    node* left;
    node* right;
    node* parent;
    node(T k, node* p) {
        parent = p;
        nleft = 0;
        key = new T(k);
        left = NULL;
        right = NULL;
    }
};


template <class T>
class AVLRankTree {
private:
    node<T>* root = NULL;
    node<T>* root_ = NULL;

public:
    int n;
    void insert(T x) {
        root = insertUtil(root, x, NULL);
    }
    void remove(T x) {
        root = removeUtil(root, x, NULL);
    }
    node<T>* getRoot()
    {
        return this->root;
    }
    node<T>* search(node<T>* root, T x)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (x == *root->key)
            return root;
        else if (x < *root->key)
            return search(root->right, x);
        else if (x > *root->key)
            return search(root->left, x);
        return nullptr;
    }
    void inorder() {
        inorderUtil(root);
        cout << endl;
    }
    T ksmallest(int k) {
        return ksmallestUtil(root, k);
    }
    int rank(T x) {
        return rankUtil(root, x, 0);
    }
    node<T>* select(int k)
    {
        k += 1;
        if (k > this->n)
        {
            return nullptr;
        }
        return selectUtil(root, k);
    }
private:
    void inorderUtil(node<T>* head) {
        if (head == NULL) return;
        inorderUtil(head->left);
        cout << head->key << " ";
        inorderUtil(head->right);
    }
    node<T>* insertUtil(node<T>* head, T x, node<T>* p) {
        if (head == NULL) {
            n++;
            node<T>* temp = new node<T>(x, p);
            while (p != NULL) {
                if (x < *p->key) p->nleft += 1;
                p = p->parent;
            }
            if (n == 1)
                root_ = temp;
            head = balanceTree(head);
            return temp;
        }
        if (x > *head->key)
            head->right = insertUtil(head->right, x, head);
        else if (x < *head->key) head->left = insertUtil(head->left, x, head);
        head = balanceTree(head);
        return head;
    }
    node<T>* searchUtil(node<T>* head, T x) {
        if (head == NULL) return NULL;
        T k = head->key;
        if (k == x) return head;
        if (k > x) return searchUtil(head->left, x);
        if (k < x) return searchUtil(head->right, x);
    }
    int rankUtil(node<T>* head, T x, int r) {
        if (head == NULL) return 0;
        T k = head->key;
        if (*k == *x) return r + 1 + head->nleft;
        if (*k > *x) return rankUtil(head->left, x, r);
        if (*k < *x) return rankUtil(head->right, x, r + head->nleft + 1);
    }
    node<T>* selectUtil(node<T>* head, int k)
    {
        if (head->nleft == k - 1)
        {
            return head;
        }
        else if (head->nleft > k - 1)
        {
            return selectUtil(head->left, k);
        }
        else if (head->nleft < k - 1)
        {
            return selectUtil(head->right, k - head->nleft - 1);
        }
        return nullptr;
    }
    node<T>* removeUtil(node<T>* head, T x, node<T>* p) {
        if (head == NULL) return NULL;
        if (x == *head->key) {
            node<T>* l = head->left;
            node<T>* r = head->right;
            while (p != NULL) {
                if (x < *p->key) p->nleft -= 1;
                p = p->parent;
            }
            if (l == NULL) {
                delete(head);
                head = balanceTree(head);
                return r;
            }
            if (r == NULL) {
                delete(head);
                return l;
            }
            while (r->left != NULL) r = r->left;
            head->key = r->key;
            head->right = removeUtil(head->right, *r->key, NULL);
            head = balanceTree(head);
            return head;
        }
        if (x < *head->key) head->left = removeUtil(head->left, x, head);
        else head->right = removeUtil(head->right, x, head);
        head = balanceTree(head);
        return head;
    }

    T& ksmallestUtil(node<T>* head, int k) {
        if (k<1 || k>n) return NULL;
        if (head->nleft == k - 1) return head->key;
        if (head->nleft > k - 1) return ksmallestUtil(head->left, k);
        return ksmallestUtil(head->right, k - 1 - head->nleft);
    }
    node<T>* leftRotate(node<T>* parent) {
        node<T>* toRotate = parent->right;
        node<T>* leftSon = toRotate->left;
        /*parent->nleft = parent->left->right->nleft + parent->right->nleft + 1;
        parent->left->nleft = parent->left->left->nleft + parent->nleft + 1;*/
        /// if node has left subtree make the node parent its parent
        if (leftSon != nullptr) {
            leftSon->parent = parent;
        }
        parent->right = leftSon;
        /// if node parent is root make node root, if not root make son of grandparent
        toRotate->parent = parent->parent;
        if (parent->parent == nullptr) {
            root = toRotate;
        }
        else if (parent->parent->left == parent) {
            parent->parent->left = toRotate;
        }
        else {
            parent->parent->right = toRotate;
        }
        /// make node parent of parent
        toRotate->left = parent;
        parent->parent = toRotate;
        parent->height = 1 + max(getBalance(parent->right), getBalance(parent->left));
        toRotate->height = 1 + max(getBalance(toRotate->right), getBalance(toRotate->left));
        return toRotate;
    }
    
node<T>* rightRotate(node<T>* parent) {
    node<T>* toRotate = parent->left;
    node<T>* rightSon = toRotate->right;
        /// if node has right subtree make the node parent its parent
    if (rightSon != nullptr) {
        rightSon->parent = parent;
    }
        parent->left = rightSon;
        /// if node parent is root make node root, if not root make son of grandparent
        toRotate->parent = parent->parent;
        if (parent->parent == nullptr) {
            root = toRotate;
        }
        else if (parent->parent->right == parent) {
            parent->parent->right = toRotate;
        }
        else {
            parent->parent->left = toRotate;
        }
        /// make node parent of parent
        toRotate->right = parent;
        parent->parent = toRotate;
        parent->height = 1 + max(getBalance(parent->right), getBalance(parent->left));
        toRotate->height = 1 + max(getBalance(toRotate->right), getBalance(toRotate->left));
        return toRotate;
}
int calcHeight(node<T>* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int leftHeight = calcHeight(root->left);
    int rightHeight = calcHeight(root->right);

    return 1 + max(leftHeight, rightHeight);
}
int getBalance(node<T>* root)
{
    if (root)
    {
        return (calcHeight(root->left) - calcHeight(root->right));
    }
}

inline node<T>* balanceTree(node<T>* root)
{
    if (root != nullptr)
    {
            if (getBalance(root) == 2)
            {
                if (getBalance(root->left) >= 0)
                {
                    return rightRotate(root);
                }
                else if (getBalance(root->left) == -1)
                {
                    root->left = leftRotate(root->left);
                    return rightRotate(root);
                }
            }
            else if (getBalance(root) == -2)
            {
                if (getBalance(root->right) <= 0)
                {
                    return leftRotate(root);
                }
                else if (getBalance(root->right) == 1)
                {
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
            }
        }

        return root;
}


};
