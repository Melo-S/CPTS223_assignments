#pragma once

#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename Comparable>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void makeEmpty();
    const Comparable& findMin() const;
    const Comparable& findMax() const;

    bool contains(const Comparable& x) const;
    void insert(const Comparable& x);
    void remove(const Comparable& x);
    int treeSize() const;
    int computeHeight() const;
    int readRootHeight() const;
    bool isBalanced() const;
    bool isBST() const;

    double averageDepth() const;
    void removeByRank(int rank);

private:
    static const int ALLOWED_IMBALANCE = 1;

    struct AVLNode {
        Comparable element;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(const Comparable& theElement, AVLNode* lt = nullptr, AVLNode* rt = nullptr)
            : element(theElement), left(lt), right(rt), height(0) {}
    };

    AVLNode* root;

    AVLNode* findMin(AVLNode* t) const;
    AVLNode* findMax(AVLNode* t) const;
    void makeEmpty(AVLNode*& t);
    bool contains(const Comparable& x, AVLNode* t) const;
    void insert(const Comparable& x, AVLNode*& t);
    void remove(const Comparable& x, AVLNode*& t);
    void balance(AVLNode*& t);
    int height(AVLNode* t) const;
    int treeSize(AVLNode* t) const;
    int computeHeight(AVLNode* t) const;
    void rotateWithLeftChild(AVLNode*& k2);
    void rotateWithRightChild(AVLNode*& k2);
    void doubleWithLeftChild(AVLNode*& k3);
    void doubleWithRightChild(AVLNode*& k3);
    void removeByRank(AVLNode*& t, int rank, int& currentRank);
    bool isBST(AVLNode* t, AVLNode* minNode, AVLNode* maxNode) const;
    bool isBalanced(AVLNode* t) const;

    void computeAverageDepth(AVLNode* node, int depth, int& totalDepth, int& totalNodes) const;
};

// Constructor & Destructor
template <typename Comparable>
AVLTree<Comparable>::AVLTree() : root(nullptr) {}

template <typename Comparable>
AVLTree<Comparable>::~AVLTree() {
    makeEmpty();
}

// Function for Making the tree empty
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

template <typename Comparable>
void AVLTree<Comparable>::makeEmpty(AVLNode*& t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

//Add  Contains function
template <typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable& x) const {
    return contains(x, root);
}

template <typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable& x, AVLNode* t) const {
    if (t == nullptr) return false;
    if (x < t->element) return contains(x, t->left);
    if (x > t->element) return contains(x, t->right);
    return true;
}

// Add Insert function
template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& x) {
    insert(x, root);
}

template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& x, AVLNode*& t) {
    if (t == nullptr) {
        t = new AVLNode(x);
    } else if (x < t->element) {
        insert(x, t->left);
    } else if (x > t->element) {
        insert(x, t->right);
    }
    balance(t);
}

// Add Remove function
template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable& x) {
    remove(x, root);
}

template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable& x, AVLNode*& t) {
    if (t == nullptr) return;

    if (x < t->element) {
        remove(x, t->left);
    } else if (x > t->element) {
        remove(x, t->right);
    } else if (t->left != nullptr && t->right != nullptr) {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    } else {
        AVLNode* oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
    balance(t);
}

// Add Balance function
template <typename Comparable>
void AVLTree<Comparable>::balance(AVLNode*& t) {
    if (t == nullptr) return;

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);
    }
    t->height = max(height(t->left), height(t->right)) + 1;
}

// Add Height function
template <typename Comparable>
int AVLTree<Comparable>::height(AVLNode* t) const {
    return t == nullptr ? -1 : t->height;
}

// Add Rotate functions
template <typename Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode*& k2) {
    AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template <typename Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode*& k2) {
    AVLNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;
    k2 = k1;
}

template <typename Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <typename Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode*& k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

// Implement isBalanced function
template <typename Comparable>
bool AVLTree<Comparable>::isBalanced() const {
    return isBalanced(root);
}

template <typename Comparable>
bool AVLTree<Comparable>::isBalanced(AVLNode* t) const {
    if (t == nullptr) return true;

    int leftHeight = height(t->left);
    int rightHeight = height(t->right);

    if (abs(leftHeight - rightHeight) > ALLOWED_IMBALANCE)
        return false;
    else
        return isBalanced(t->left) && isBalanced(t->right);
}

// List root height
template <typename Comparable>
int AVLTree<Comparable>::readRootHeight() const {
    return root != nullptr ? root->height : -1;
}

// Find the treeSize function
template <typename Comparable>
int AVLTree<Comparable>::treeSize() const {
    return treeSize(root);
}

template <typename Comparable>
int AVLTree<Comparable>::treeSize(AVLNode* t) const {
    if (t == nullptr) return 0;
    return 1 + treeSize(t->left) + treeSize(t->right);
}

//Find the height of the tree
template <typename Comparable>
int AVLTree<Comparable>::computeHeight() const {
    return computeHeight(root);
}

template <typename Comparable>
int AVLTree<Comparable>::computeHeight(AVLNode* t) const {
    if (t == nullptr) return -1;
    return max(computeHeight(t->left), computeHeight(t->right)) + 1;
}

// RemoveByRank function
template <typename Comparable>
void AVLTree<Comparable>::removeByRank(int rank) {
    int currentRank = 0;
    removeByRank(root, rank, currentRank);
}

template <typename Comparable>
void AVLTree<Comparable>::removeByRank(AVLNode*& t, int rank, int& currentRank) {
    if (t == nullptr) return;

    removeByRank(t->left, rank, currentRank);
    currentRank++;
    if (currentRank == rank) {
        remove(t->element, root);
        return;
    }
    removeByRank(t->right, rank, currentRank);
}

// Find out if the tree is a BST
template <typename Comparable>
bool AVLTree<Comparable>::isBST() const {
    return isBST(root, nullptr, nullptr);
}

template <typename Comparable>
bool AVLTree<Comparable>::isBST(AVLNode* t, AVLNode* minNode, AVLNode* maxNode) const {
    if (t == nullptr) return true;
    if ((minNode != nullptr && t->element <= minNode->element) ||
        (maxNode != nullptr && t->element >= maxNode->element)) {
        return false;
    }
    return isBST(t->left, minNode, t) && isBST(t->right, t, maxNode);
}

// Find min & max
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMin(AVLNode* t) const {
    if (t == nullptr) return nullptr;
    if (t->left == nullptr) return t;
    return findMin(t->left);
}

template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMax(AVLNode* t) const {
    if (t == nullptr) return nullptr;
    if (t->right == nullptr) return t;
    return findMax(t->right);
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::findMin() const {
    AVLNode* minNode = findMin(root);
    if (minNode == nullptr) throw underflow_error("Tree is empty");
    return minNode->element;
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::findMax() const {
    AVLNode* maxNode = findMax(root);
    if (maxNode == nullptr) throw underflow_error("Tree is empty");
    return maxNode->element;
}

// Find the average depth computation
template <typename Comparable>
double AVLTree<Comparable>::averageDepth() const {
    int totalDepth = 0, totalNodes = 0;
    computeAverageDepth(root, 0, totalDepth, totalNodes);
    return totalNodes == 0 ? 0.0 : static_cast<double>(totalDepth) / totalNodes;
}

template <typename Comparable>
void AVLTree<Comparable>::computeAverageDepth(AVLNode* node, int depth, int& totalDepth, int& totalNodes) const {
    if (node == nullptr) return;
    totalDepth += depth;
    totalNodes++;
    computeAverageDepth(node->left, depth + 1, totalDepth, totalNodes);
    computeAverageDepth(node->right, depth + 1, totalDepth, totalNodes);
}
