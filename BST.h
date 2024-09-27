#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;

/* ----------------------------------------------------------------------------
---- Below is declaration of BST class, referring to textbook, Figure 4.16 ----
---------------------------------------------------------------------------- */

template <typename Comparable>
class BST
{
public:
    BST();
    ~BST();
    void makeEmpty();

    const Comparable& findMin() const;
    const Comparable& findMax() const;

    bool contains(const Comparable& x) const;
    void insert(const Comparable& x);
    void remove(const Comparable& x);
    int treeSize() const;
    int treeHeight() const;
    void printInOrder() const;
    void printLevels() const;
    void printMaxPath() const;

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt) : element(theElement), left(lt), right(rt) {}
        BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt) : element(move(theElement)), left(lt), right(rt) {}
    };

    BinaryNode* root;

    BinaryNode* findMin(BinaryNode* t) const;
    BinaryNode* findMax(BinaryNode* t) const;
    void makeEmpty(BinaryNode*& t);
    bool contains(const Comparable& x, BinaryNode* t) const;
    void insert(const Comparable& x, BinaryNode*& t);
    void remove(const Comparable& x, BinaryNode*& t);
    int treeSize(BinaryNode* t) const;
    int treeHeight(BinaryNode* t) const;
    void printInOrder(BinaryNode* t) const;
    void printLevels(BinaryNode* t) const;
    void printMaxPath(BinaryNode* t) const;
};

/* --------------------------------------------------------------
---- Below is implementation of public and private functions ----
-------------------------------------------------------------- */

// constructor
template<typename Comparable>
BST<Comparable>::BST() : root(NULL) {}

// destructor, refer to textbook, Figure 4.27
template<typename Comparable>
BST<Comparable>::~BST() {
    makeEmpty();
}

// public makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty() {
    makeEmpty(root);
}

// private recursive makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty(BinaryNode*& t) {
    if (t != NULL) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

// // public findMin
template <typename Comparable>
const Comparable& BST<Comparable>::findMin() const {
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMin(root)->element;
}

// private findMin: refer to textbook, Figure 4.20
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMin(BinaryNode* t) const {
    if (t == NULL) {
        return NULL;
    }
    else if (t->left == NULL) {
        return t;
    }
    else {
        return findMin(t->left);
    }
}

// public findMax
template <typename Comparable>
const Comparable& BST<Comparable>::findMax() const {
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMax(root)->element;
}

// private findMax: refer to textbook, Figure 4.21
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMax(BinaryNode* t) const {
    if (t == NULL) {
        return NULL;
    }
    else if (t->right == NULL) {
        return t;
    }
    else {
        return findMin(t->right);
    }
}

// public contains: refer to textbook, Figure 4.17, Line 4 - 7
template<typename Comparable>
bool BST<Comparable>::contains(const Comparable& x) const {
    return contains(x, root);
}

template<typename Comparable>
bool BST<Comparable>::contains(const Comparable& x, BinaryNode* t) const {
    if (t == NULL) {
        return false;
    }
    else if (x < t->element) {
        return contains(x, t->left);
    }
    else if (x > t->element) {
        return contains(x, t->right);
    }
    else {
        return true; // Match
    }
}

// public insert: refer to textbook, Figure 4.17, Line 12 - 15
template<typename Comparable>
void BST<Comparable>::insert(const Comparable& x) {
    insert(x, root);
}

template<typename Comparable>
void BST<Comparable>::insert(const Comparable& x, BinaryNode*& t) {
    if (t == NULL) {
        t = new BinaryNode(x, NULL, NULL); // Create new node
    }
    else if (x < t->element) {
        insert(x, t->left); // Insert in left subtree
    }
    else if (x > t->element) {
        insert(x, t->right); // Insert in right subtree
    }
}

// public remove: refer to textbook, Figure 4.17, Line 20 - 23
template<typename Comparable>
void BST<Comparable>::remove(const Comparable& x) {
    remove(x, root);
}

template<typename Comparable>
void BST<Comparable>::remove(const Comparable& x, BinaryNode*& t) {
    if (t == NULL) return; // Item not found
    if (x < t->element) {
        remove(x, t->left);
    }
    else if (x > t->element) {
        remove(x, t->right);
    }
    else if (t->left != NULL && t->right != NULL) { // Two children
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else { // One or no child
        BinaryNode* oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
}

// public treeSize
template <typename Comparable>
int BST<Comparable>::treeSize() const {
    return treeSize(root);
}

template <typename Comparable>
int BST<Comparable>::treeSize(BinaryNode* t) const {
    if (t == NULL) {
        return 0;
    }
    else {
        return 1 + treeSize(t->left) + treeSize(t->right);
    }
}

// public treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight() const {
    return treeHeight(root);
}

template <typename Comparable>
int BST<Comparable>::treeHeight(BinaryNode* t) const {
    if (t == NULL) {
        return -1; // Height of empty tree is -1
    }
    else {
        return 1 + max(treeHeight(t->left), treeHeight(t->right));
    }
}

// public printInOrder: refer to textbook, Figure 4.60
template<typename Comparable>
void BST<Comparable>::printInOrder() const {
    printInOrder(root);
}

template<typename Comparable>
void BST<Comparable>::printInOrder(BinaryNode* t) const {
    if (t != NULL) {
        printInOrder(t->left);
        cout << t->element << " ";
        printInOrder(t->right);
    }
}

// public printLevels
template <typename Comparable>
void BST<Comparable>::printLevels() const {
    if (root == NULL) return;

    queue<BinaryNode*> q;
    q.push(root);

    while (!q.empty()) {
        BinaryNode* current = q.front();
        q.pop();
        cout << current->element << " ";

        if (current->left != NULL) q.push(current->left);
        if (current->right != NULL) q.push(current->right);
    }
    cout << endl;
}

// public printMaxPath
template <typename Comparable>
void BST<Comparable>::printMaxPath() const {
    printMaxPath(root);
}

template <typename Comparable>
void BST<Comparable>::printMaxPath(BinaryNode* t) const {
    if (t == NULL) return;

    cout << t->element << " ";

    if (treeHeight(t->left) > treeHeight(t->right)) {
        printMaxPath(t->left);
    }
    else {
        printMaxPath(t->right);
    }
}

#endif
