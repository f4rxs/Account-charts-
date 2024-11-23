#ifndef FORESTTREE_H
#define FORESTTREE_H

#include "Account.h"
#include <iostream>

using namespace std;

class ForestTree {
private:
  // Inner class for a node in the tree
  class ForestNode {
  public:
    Account data;      // Node data
    ForestNode *left;  // Sibling (same level)
    ForestNode *right; // First child (next level)

    // Constructor
    ForestNode(const Account &data)
        : data(data), left(nullptr), right(nullptr) {}
  };

  typedef ForestNode *FNodePtr; // Pointer to a node
  FNodePtr root;                // Root of the tree

public:
  // Constructor
  ForestTree();
  // Destructor
  ~ForestTree();

  // function to get the root of the tree
  FNodePtr getRoot() const;
  // check if the tree is empty
  bool isEmpty() const;
  // function to check if an account is a child of another account
  bool insert(const Account &account);
  // function to find an account in the tree
  FNodePtr findAccount(int accountNumber) const;
  // function to delete an account from the tree
  FNodePtr deleteAccount(int accountNumber);
  // function to print the tree
  void printTree() const;

private:
  // Helper function to delete from a specific node
  void destroy(FNodePtr node);
  // Helper function to insert an account
  bool insert(FNodePtr &current, const Account &account);
  // Helper function to check if an account is a child (subAccount) of another
  // account
  bool isChild(int accountNumber, int subAccountNumber) const;
  // Helper function to find the parent node of a given account
  FNodePtr findParent(FNodePtr current, int accountNumber) const;
  // Helper function to find a node with a given account number
  FNodePtr findNode(FNodePtr current, int accountNumber) const;
  // Helper function to print the tree
  void printTree(FNodePtr node, int level, string prefix) const;
};

#endif // end of FORESTTREE_H
