#ifndef FORESTTREE_H
#define FORESTTREE_H

#include "Account.h"
#include <iostream>

using namespace std;

class ForestTree
{
private:
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
  typedef ForestNode *FNodePtr;
  FNodePtr root;

public:
  ForestTree();
  ~ForestTree();

  Account *getRoot() const;

  bool isEmpty() const;

  bool insert(const Account &account);

  Account *findAccount(int accountNumber) const;

  bool applyTransaction(int accountNumber, Transaction *transaction);

  bool deleteAccount(int accountNumber);

  void printTree() const;

  void saveToFile(const string &fileName) const;

  void generateAccountReport(int accountNumber) const;

  void removeTransaction(const int &accountNumber, const int &transactionId);

private:
  // Helper methods
  void destroy(FNodePtr &node);

  bool insert(FNodePtr &current, const Account &account);

  bool isChild(int accountNumber, int subAccountNumber) const;

  bool isAncestor(int ancestorNumber, int accountNumber) const;

  FNodePtr findParent(FNodePtr current, int accountNumber, int level) const;

  FNodePtr findNode(FNodePtr current, int accountNumber) const;

  FNodePtr findNodeAndDelete(FNodePtr node, int accountNumber);

  void printTree(FNodePtr node, int level, string prefix) const;

  void saveNodeRecursive(ofstream &outFile, FNodePtr node, int level) const;

  void saveSubAccounts(ofstream &reportFile, ForestTree::FNodePtr node,
                       int level) const;

  void generateReportFile(ForestTree::FNodePtr accountNode) const;

  void updateNodeBalance(FNodePtr current, int accountNumber, int delta);

  void updateParentBalances(const int &accountNumber);
  void updateParentBalances(FNodePtr node);
};

#endif
