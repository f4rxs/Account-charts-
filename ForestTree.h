#ifndef FORESTTREE_H
#define FORESTTREE_H

#include <iostream>
#include "Account.h"
using namespace std;

class ForestTree {
private:
    // Inner class for a node in the tree
    class ForestNode {
    public:
        Account data;      // Node data
        ForestNode* left;  // First child (next level)
        ForestNode* right; // Next sibling (same level)

        // Constructor
        ForestNode(const Account& data) : data(data), left(nullptr), right(nullptr) {}
    };

    typedef ForestNode* FNodePtr;
    FNodePtr root; // Root of the tree

public:
    ForestTree();
    ~ForestTree();

    FNodePtr getRoot() const;
    bool isEmpty() const;
    bool insert(const Account& account);
    void printTree() const;

private:
    void destroy(FNodePtr node); // Helper to clean up memory
    bool insert(FNodePtr& current, const Account& account);
    bool isChild(const Account& parent, const Account& potentialChild) const;
    void printTree(FNodePtr node, int level, string prefix) const;
};

#endif // end of FORESTTREE_H
