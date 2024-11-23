#ifndef FORESTTREE_H
#define FORESTTREE_H

#include "Account.h"
#include <iostream>

using namespace std;

class ForestTree
{
private:
  // Inner class for a node in the tree
  class ForestNode
  {
  public:
    Account data;      // Node data
    ForestNode *left;  // Sibling (same level)
    ForestNode *right; // First child (next level)

    // Constructor
    ForestNode(const Account &data)
        : data(data), left(nullptr), right(nullptr) {}
  };
  typedef ForestNode *FNodePtr; // Pointer to a node
  FNodePtr root;

public:
  // Root of the tree

  // Constructor
  ForestTree();
  // Destructor
  ~ForestTree();

  // function to get the root of the tree
  Account *getRoot() const;
  // check if the tree is empty
  bool isEmpty() const;
  // function to check if an account is a child of another account
  bool insert(const Account &account);
  // function to find an account in the tree
  Account *findAccount(int accountNumber) const;
  // function to delete an account from the tree
  bool deleteAccount(int accountNumber);
  // function to print the tree
  void printTree() const;
<<<<<<< Updated upstream
  // finction to save into a file
  void saveToFile(const string &fileName) const;
 void generateAccountReport(ForestTree &forestTree) const;
=======

>>>>>>> Stashed changes
private:
  // Helper function to delete from a specific node
  void destroy(FNodePtr &node);
  // Helper function to insert an account
  bool insert(FNodePtr &current, const Account &account);
  // Helper function to check if an account is a child (subAccount) of another
  // account
  bool isChild(int accountNumber, int subAccountNumber) const;
<<<<<<< Updated upstream
=======

  // Helper function to check if an account is an ancestor of another account
  bool isAncestor(int ancestorNumber, int accountNumber) const;
  // Helper function to find the parent node of a given account
  FNodePtr findParent(FNodePtr current, int accountNumber, int level) const;
>>>>>>> Stashed changes
  // Helper function to find a node with a given account number
  FNodePtr findNode(FNodePtr current, int accountNumber) const;
  // Helper function to print the tree
  void printTree(FNodePtr node, int level, string prefix) const;
  //Helper function to find the parent node
  FNodePtr findParent(FNodePtr current, int accountNumber, int level) const;
  //Helper function to save the nodes to genrate accounts
  void saveNodeRecursive(ofstream &outFile, FNodePtr node, int level) const;
  //Helper function to save subaccounts to genrate accounts
  void saveSubAccounts(ofstream &reportFile, ForestTree::FNodePtr node, int level) const;
  //Helper function function for the generate Account Report
  void generateReportFile(ForestTree::FNodePtr accountNode) const;
};

#endif
