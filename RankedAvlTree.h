#include<iostream>
using namespace std;

template<class T>
class node
{
public:
    T key;
    int nleft;
    node * left;
    node * right;
    node * parent;
    node(T k, node * p){
        parent = p;
        nleft = 0;
        key = k;
        left = NULL;
        right = NULL;
    }
};


template <class T>
class AVLRankTree{
private:
    node<T>* root = NULL;
    node<T>* root_ = NULL;

public:
    int n;
    void insert(T x){
        root=insertUtil(root, x, NULL);
    }
    void remove(T x){
        root=removeUtil(root, x, NULL);
    }
    node<T>* getRoot()
    {
        return this->root;
    }
    node<T> * search(node<T>* root,T x)
    {
        if(x == nullptr)
        {
            return nullptr;
        }
        if(x == root->key)
            return root;
        else if(x < root->key)
            return search(root->right,x);
        else if(x > root->key)
            return search(root->left,x);
        return nullptr;
    }
    void inorder(){
        inorderUtil(root);
        cout<<endl;
    }
    T ksmallest(int k){
        return ksmallestUtil(root, k);
    }
    int rank(T x){
        return rankUtil(root, x, 0);
    }
    node<T>* select(int k)
    {
         k += 1;
        if(k > this->n)
        {
            return nullptr;
        }
        return selectUtil(root,k);
    }
private:
    void inorderUtil(node<T> * head){
        if(head==NULL) return ;
        inorderUtil(head->left);
        cout<<head->key<<" ";
        inorderUtil(head->right);
    }
    node<T> * insertUtil(node<T> * head, T x, node<T> * p){
        if(head == NULL){
            n++;
            node<T> * temp = new node<T>(x,p);
            while(p!=NULL){
                if(x<p->key) p->nleft += 1;
                p=p->parent;
            }
            if(n==1)
                root_ = temp;
            return temp;
        }
        if(*x > *head->key)
            head->right = insertUtil(head->right, x, head);
        else if(*x < *head->key) head->left = insertUtil(head->left, x, head);
        return head;
    }
    node<T> * searchUtil(node<T> * head, T x){
        if(head == NULL) return NULL;
        T k = head->key;
        if(k == x) return head;
        if(k > x) return searchUtil(head->left, x);
        if(k < x) return searchUtil(head->right, x);
    }
    int rankUtil(node<T> * head, T x, int r){
        if(head == NULL) return 0;
        T k = head->key;
        if(*k == *x) return r+1+head->nleft;
        if(*k > *x) return rankUtil(head->left, x, r);
        if(*k < *x) return rankUtil(head->right, x, r+head->nleft+1);
    }
    node<T>* selectUtil(node<T>* head,int k)
    {
        if(head->nleft  == k-1)
        {
            return head;
        }
        else if(head->nleft > k-1)
        {
            return selectUtil(head->left,k);
        }
        else if(head->nleft < k-1)
        {
            return selectUtil(head->right, k - head->nleft - 1);
        }
        return nullptr;
    }
    node<T> * removeUtil(node<T> * head, T x, node<T> * p){
        if(head == NULL) return NULL;
        if(x == head->key){
            node<T> * l = head->left;
            node<T>* r = head->right;
            while(p!=NULL){
                if(x<p->key) p->nleft -= 1;
                p=p->parent;
            }
            if(l == NULL){
                delete(head);
                return r;
            }
            if(r == NULL){
                delete(head);
                return l;
            }
            while(r->left != NULL) r = r->left;
            head->key = r->key;
            head->right = removeUtil(head->right, r->key, NULL);
            return head;
        }
        if(x < head->key) head->left = removeUtil(head->left, x, head);
        else head->right = removeUtil(head->right, x, head);
        return head;
    }

    T& ksmallestUtil(node<T> * head, int k){
        if(k<1 || k>n) return NULL;
        if(head->nleft == k-1) return head->key;
        if(head->nleft > k-1) return ksmallestUtil(head->left, k);
        return ksmallestUtil(head->right, k-1-head->nleft);
    }
};