#include <iostream>

// Node class for AVL tree
template <class T>
class treeNode{
public:
    T key_;
    treeNode* left_;
    treeNode* right_;
    int size_;
    treeNode(T key) : key_(key), left_(NULL), right_(NULL),size_(1) {}
    ~treeNode() = default;
};

// AVL tree class
template<class T>
class AvlRankTree {
private:
    treeNode<T>* root_;
    int nodesNum;
public:
    AvlRankTree() : root_(NULL), nodesNum(0){}

    ~AvlRankTree()
    {
        deleteTree(this->root_);
    }

    void deleteTree(treeNode<T>* root)
    {
        if(root == nullptr)
        {
            return;
        }

        deleteTree(root->left_);
        deleteTree(root->right_);

        delete root;
    }
    // Insert a key into the tree
    void Insert(T key) { root_ = Insert(root_, key); }

    // Get the rank (i.e., number of keys less than or equal to a given key) of a key
    int GetRank(T key) { return GetRank(root_, key); }

    treeNode<T>* getRoot() const
    {
        return this->root_;
    }
    treeNode<T>* search(treeNode<T>* root, T x)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (x == root->key_)
            return root;
        else if (x < root->key_)
            return search(root->left_, x);
        else if (x > root->key_)
            return search(root->right_, x);
        return nullptr;
    }
    void Remove(const T& element) {
        root_ = Remove(root_, element);
    }
    treeNode<T>* select(int k)
    {
        return select(root_, k);
    }
    int getNodesNum() const
    {
        return this->nodesNum;
    }
    void updateNodesNum(bool add)
    {
        if(add == true)
            nodesNum++;
        else
            nodesNum--;
    }
private:
    // Recursive function to insert a key into the tree
    treeNode<T>* Insert(treeNode<T>* node, T key) {
        if (node == NULL) return new treeNode<T>(key);

        if (key < node->key_) {
            node->left_ = Insert(node->left_, key);
        } else if (key > node->key_) {
            node->right_ = Insert(node->right_, key);
        } else {
            // Key already exists in the tree, do nothing
            return node;
        }

        // Update the height and size of the node
        node->size_ = GetSize(node->left_) + GetSize(node->right_) + 1;
        // Balance the tree
        int balance = GetBalance(node);
        if (balance > 1 && key < node->left_->key_) {
            // Left-left case
            return RotateRight(node);
        }
        if (balance < -1 && key > node->right_->key_) {
            // Right-right case
            return RotateLeft(node);
        }
        if (balance > 1 && key > node->left_->key_) {
            // Left-right case
            node->left_ = RotateLeft(node->left_);
            return RotateRight(node);
        }
        if (balance < -1 && key < node->right_->key_) {
            // Right-left case
            node->right_ = RotateRight(node->right_);
            return RotateLeft(node);
        }

        return node;
    }

    // Recursive function to get the rank of a key
    int GetRank(treeNode<T>* node, T key) {
        if (node == NULL) return -1;

        if (key < node->key_) {
            return GetRank(node->left_, key);
        } else if (key > node->key_) {
            return 1 + GetSize(node->left_) + GetRank(node->right_, key);
        } else {
            // Key found, return the number of keys less than or equal to it
            return GetSize(node->left_);
        }
    }
    treeNode<T>* select(treeNode<T>* v, int k)
    {
        int Vleft;

        if(v->left_ == nullptr)
        {
            Vleft = 0;
        }
        else
        {
            Vleft = v->left_->size_;
        }

        if(Vleft == k - 1)
        {
            return v;
        }
        else if(Vleft > k - 1)
        {
            return select(v->left_,k);
        }
        else if(Vleft < k - 1)
        {
            return select(v->right_, k - Vleft - 1);
        }

        return nullptr;
    }

    // Get the size (i.e., number of nodes) of a subtree
    int GetSize(treeNode<T>* node) {
        if (node == NULL) return 0;
        return node->size_;
    }

    // Get the balance factor of a node (left subtree height - right subtree height)
    int GetBalance(treeNode<T>* node) {
        if (node == NULL) return 0;
        return GetHeight(node->left_) - GetHeight(node->right_);
    }
    int getBalance(treeNode<T>* root)
    {
        int Hleft;
        int Hright;
        if (root)
        {
            if(root->left_)
                Hleft = GetHeight(root->left_);
            else
                Hleft = 0;
            if(root->right_)
                Hright = GetHeight(root->right_);
            else
                Hright = 0;
            return (Hleft - Hright);
        }

        return 0;
    }


    inline treeNode<T>* Balance(treeNode<T>* root)
    {
        if (root != nullptr)
        {
            if (getBalance(root) == 2)
            {
                if (getBalance(root->left_) >= 0)
                {
                    return RotateRight(root);
                }
                else if (getBalance(root->left_) == -1)
                {
                    root->left_ = RotateLeft(root->left_);
                    return RotateRight(root);
                }
            }
            else if (getBalance(root) == -2)
            {
                if (getBalance(root->right_) <= 0)
                {
                    return RotateLeft(root);
                }
                else if (getBalance(root->right_) == 1)
                {
                    root->right_ = RotateRight(root->right_);
                    return RotateLeft(root);
                }
            }
        }

        return root;
    }




    treeNode<T>* Remove(treeNode<T>* node, const T& element) {
        if (node == nullptr) return nullptr;

        // Find the node to remove
        if (element < node->key_) {
            node->left_ = Remove(node->left_, element);
        } else if (element > node->key_) {
            node->right_ = Remove(node->right_, element);
        } else {  // element == node->element
            // Handle the case where the node has no children or only one child
            if (node->left_ == nullptr || node->right_ == nullptr) {
                treeNode<T>* temp = (node->left_ == nullptr) ? node->right_ : node->left_;
                delete node;
                return temp;
            } else {  // node has two children
                // Find the minimum element in the right subtree
                treeNode<T>* temp = node->right_;
                while(temp->left_ != nullptr)
                    temp = temp->left_;
                // Replace the element of the node to remove with the element of the minimum element
                node->key_ = temp->key_;
                // Remove the minimum element from the right subtree
                node->right_ = Remove(node->right_, temp->key_);
            }
        }

        // Update the size of the node
        node->size_ = 1 + GetSize(node->left_) + GetSize(node->right_);
        // Rebalance the tree if necessary
        return Balance(node);
    }
    // Rotate a subtree to the right
    treeNode<T>* RotateRight(treeNode<T>* node)
    {
        treeNode<T>* left = node->left_;
        treeNode<T>* right = nullptr;
        if(left != nullptr) {
            right = left->right_;

            left->right_ = node;
            node->left_ = right;

            // Update the height and size of the nodes
            node->size_ = GetSize(node->left_) + GetSize(node->right_) + 1;
            left->size_ = GetSize(left->left_) + GetSize(left->right_) + 1;
        }
        return left;
    }

    // Rotate a subtree to the left
    treeNode<T>* RotateLeft(treeNode<T>* node) {
        treeNode<T> *right = node->right_;
        treeNode<T>* left = nullptr;

        if (right != nullptr)
        {
            left = right->left_;

            right->left_ = node;
            node->right_ = left;

            // Update the height and size of the nodes
            node->size_ = GetSize(node->left_) + GetSize(node->right_) + 1;
            right->size_ = GetSize(right->left_) + GetSize(right->right_) + 1;
        }

        return right;
    }
// Get the height of a node
    int GetHeight(treeNode<T>* node) {

        if (node == NULL) return 0;
        int leftH = GetHeight(node->left_);
        int rightH = GetHeight(node->right_);
        int max = leftH;
        if(rightH > leftH)
            max = rightH;

        return max + 1;
    }

};


