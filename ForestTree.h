/******************************************************************
  Implementation of a Forest Tree data structure class:
  * Public methods:
   - ForestTree: constructor to initialize the tree
    - ~ForestTree: destructor to to delete the tree
    - getRoot: function to get the root of the tree
    - isEmpty: function to check if the tree is empty
    - insert: function to insert an account into the tree
    - findAccount: function to find an account in the tree
    - applyTransaction: function to apply a transaction to an account
    - deleteAccount: function to delete an account from the tree
    - printTree: function to print the tree
    - saveToFile: function to save the tree to a file
    - generateAccountReport: function to generate an account report
    - removeTransaction: function to remove a transaction from an account

  * Private methods:
    - destroy: function to delete the tree
    - insert: function to insert an account into the tree
    - isChild: function to check if an account is a child of another
    - isAncestor: function to check if an account is an ancestor of another
    - findParent: function to find the parent of an account
    - findNode: function to find a node in the tree
    - findNodeAndDelete: function to find and delete a node in the tree
    - printTree: function to print the tree
    - saveNodeRecursive: function to save the tree to a file
    - saveSubAccounts: function to save subaccounts to a file
    - generateReportFile: function to generate an account report
    - updateNodeBalance: function to update the balance of a node
    - updateParentBalances: function to update the balances of parents
    - updateParentBalances: function to update the balances of parents
*****************************************************************
 */

#ifndef FORESTTREE_H
#define FORESTTREE_H

#include "Account.h"
#include <iostream>

using namespace std;

class ForestTree {
private:
  // class Node for the ForestTree
  class ForestNode {
  public:
    Account data;      // Node data
    ForestNode *left;  // Sibling (same level)
    ForestNode *right; // First child (next level)

    /***** ForestNode constructor *****/
    /*Precondition: a valid Account object
      Postcondition: a ForestNode object is created with the given Account
      object and left and right pointers are set to nullptr
    */
    ForestNode(const Account &data)
        : data(data), left(nullptr), right(nullptr) {}
  };

  typedef ForestNode *FNodePtr; // Pointer to a ForestNode
  FNodePtr root;                // Pointer to the root of the tree

public:
  /******* ForestTree constructor *****/
  /*Precondition: None
    Postcondition: A new ForestTree object is created with the root set to
    nullptr
  */
  ForestTree();

  /******* ForestTree destructor *****/
  /*Precondition: None
    Postcondition: The ForestTree object is destroyed and memory is deallocated
  */
  ~ForestTree();

  /******* getRoot function *****/
  /*Precondition: None
    Postcondition: Returns the root account of the tree
  */
  Account *getRoot() const;

  /******* isEmpty function *****/
  /*Precondition: None
    Postcondition: Returns true if the tree is empty, false otherwise
  */
  bool isEmpty() const;

  /******* insert function *****/
  /*Precondition: A valid Account object
    Postcondition: Inserts the given account into the tree
  */
  bool insert(const Account &account);

  /******* findAccount function *****/
  /*Precondition: An account number
    Postcondition: Returns a pointer to the account with the given account
    number, or nullptr if not found
  */
  Account *findAccount(int accountNumber) const;

  /******* applyTransaction function *****/
  /*Precondition: An account number and a Transaction object
    Postcondition: Applies the given transaction to the account with the given
    account number
  */
  bool applyTransaction(int accountNumber, Transaction *transaction);

  /******* deleteAccount function *****/
  /*Precondition: An account number
    Postcondition: Deletes the account with the given account number from the
    tree
  */
  bool deleteAccount(int accountNumber);

  /******* printTree function *****/
  /*Precondition: None
    Postcondition: Prints the tree in a readable format
  */
  void printTree() const;

  /******* saveToFile function *****/
  /*Precondition: A file name
    Postcondition: Saves the tree to a file with the given name
  */
  void saveToFile(const string &fileName) const;

  /******* generateAccountReport function *****/
  /*Precondition: An account number
    Postcondition: Generates a report for the account with the given account
    number
  */
  void generateAccountReport(int accountNumber) const;

  /******* removeTransaction function *****/
  /*Precondition: An account number and a transaction ID
    Postcondition: Removes the transaction with the given ID from the account
    with the given account number
  */
  void removeTransaction(const int &accountNumber, const int &transactionId);

private:
  // Helper methods

  /******* destroy function *****/
  /*Precondition: A ForestNode pointer
    Postcondition: Deletes the tree starting from the given node
  */
  void destroy(FNodePtr &node);

  /******* insert function *****/
  /*Precondition: A ForestNode pointer and a valid Account object
    Postcondition: Inserts the given account into the tree starting from the
    given node
  */
  bool insert(FNodePtr &current, const Account &account);

  /******* isChild function *****/
  /*Precondition: An account number and a subaccount number
    Postcondition: Returns true if the subaccount is a child of the account,
    false otherwise
  */
  bool isChild(int accountNumber, int subAccountNumber) const;

  /******* isAncestor function *****/
  /*Precondition: An ancestor account number and an account number
    Postcondition: Returns true if the ancestor is an ancestor of the account,
    false otherwise
  */
  bool isAncestor(int ancestorNumber, int accountNumber) const;

  /******* findParent function *****/
  /*Precondition: A ForestNode pointer, an account number, and a level
    Postcondition: Returns the parent of the account with the given account
    number at the given level
  */
  FNodePtr findParent(FNodePtr current, int accountNumber, int level) const;

  /******* findNode function *****/
  /*Precondition: A ForestNode pointer and an account number
    Postcondition: Returns the node with the given account number in the tree
  */
  FNodePtr findNode(FNodePtr current, int accountNumber) const;

  /******* findNodeAndDelete function *****/
  /*Precondition: A ForestNode pointer and an account number
    Postcondition: Finds and deletes the node with the given account number in
    the tree
  */
  FNodePtr findNodeAndDelete(FNodePtr node, int accountNumber);

  /******* printTree function *****/
  /*Precondition: A ForestNode pointer, a level, and a prefix
    Postcondition: Prints the tree starting from the given node in a readable
    format
  */
  void printTree(FNodePtr node, int level, string prefix) const;

  /******* saveNodeRecursive function *****/
  /*Precondition: An output file stream, a ForestNode pointer, and a level
    Postcondition: Saves the tree starting from the given node to the output
    file
  */
  void saveNodeRecursive(ofstream &outFile, FNodePtr node, int level) const;

  /******* saveSubAccounts function *****/
  /*Precondition: An output file stream, a ForestNode pointer, and a level
    Postcondition: Saves the subaccounts of the given node to the output file
  */
  void saveSubAccounts(ofstream &reportFile, ForestTree::FNodePtr node,
                       int level) const;

  /******* generateReportFile function *****/
  /*Precondition: A ForestNode pointer
    Postcondition: Generates a report file for the account with the given node
  */
  void generateReportFile(ForestTree::FNodePtr accountNode) const;

  /******* updateNodeBalance function *****/
  /*Precondition: A ForestNode pointer, an account number, and a delta
    Postcondition: Updates the balance of the node with the given account number
    by the given delta
  */
  void updateNodeBalance(FNodePtr current, int accountNumber, int delta);

  /******* updateParentBalances function *****/
  /*Precondition: A ForestNode pointer
    Postcondition: Updates the balances of the parents of the given node
  */
  void updateParentBalances(const int &accountNumber);

  /******* updateParentBalances function *****/
  /*Precondition: A ForestNode pointer
    Postcondition: Updates the balances of the parents of the given node
  */
  void updateParentBalances(FNodePtr node);
};

#endif

// End of header file
/*-------------------------------------------------------------------------*/