#include "ForestTree.h"
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

ForestTree::ForestTree() : root(nullptr) {}

ForestTree::~ForestTree() { destroy(root); }

void ForestTree::destroy(FNodePtr &node)
{
  if (node != nullptr)
  {
    destroy(node->left);  // Destroy children
    destroy(node->right); // Destroy siblings
    delete node;
    node = nullptr;
  }
}

Account *ForestTree::getRoot() const { return &(root->data); }

bool ForestTree::isEmpty() const { return root == nullptr; }

bool ForestTree::isAncestor(int ancestorNumber, int accountNumber) const
{
  accountNumber /= 10;
  while (accountNumber > 0)
  {
    // Check if the ancestor number is a prefix of the account number
    if (accountNumber == ancestorNumber)
    {
      return true; // Found an ancestor
    }
    accountNumber /= 10;
  }

  return false; // Not an ancestor
}

bool ForestTree::isChild(int accountNumber, int subAccountNumber) const
{
  string parentString = to_string(accountNumber);
  string subAccountString = to_string(subAccountNumber);
  return subAccountString.find(parentString) == 0 &&
         subAccountString.length() == parentString.length() + 1;
}

bool ForestTree::insert(const Account &account)
{
  if (isEmpty())
  {
    root = new ForestNode(account);
    return true;
  }

  // Check if the account is on the 1st level (no parent exists for level 1)
  if (account.getAccountNumber() < 10)
  {
    if (insert(root, account))
    {
      updateParentBalances(account.getAccountNumber());
      return true;
    }
    return false;
  }

  // Find the parent of the account
  FNodePtr parent = findParent(root, account.getAccountNumber(), 1);
  if (parent == nullptr)
  {
    cerr << "\nParent account not found for account: "
         << account.getAccountNumber()
         << "\nParent account: " << account.getAccountNumber() / 10
         << " should exist first before inserting this account."
         << "\nAborting insertion...\n"
         << endl;
    return false;
  }

  // Insert under the found parent
  if (insert(parent, account))
  {
    updateParentBalances(account.getAccountNumber());
    return true;
  }
  return false;
}

// function to get the root of the tree
bool ForestTree::insert(FNodePtr &current, const Account &account)
{
  // If the current node is nullptr, insert here
  if (current == nullptr)
  {
    current = new ForestNode(account);
    return true;
  }

  // check if it is the same account (either same id or same description)
  if (current->data.getAccountNumber() == account.getAccountNumber() ||
      current->data.getDescription() == account.getDescription())
  {
    cerr << "\nAccount already exists. id and description should be unique!"
         << endl;
    return false;
  }

  // Check if the current node is the parent of the account
  if (isChild(current->data.getAccountNumber(), account.getAccountNumber()))
  {
    // check if the 1st child is bigger than the account
    if (current->right != nullptr &&
        current->right->data.getAccountNumber() > account.getAccountNumber())
    {
      // insert the account as the child of the current node
      FNodePtr temp = current->right;           // Save the child of the current node
      current->right = new ForestNode(account); // Insert the account node
      current->right->left =
          temp; // link the child to the new node created as a sibling
      return true;
    }
    // Recur to the next level (right child)
    return insert(current->right, account);
  }
  else
  {
    // check if next sibling is bigger than the account
    if (current->left != nullptr &&
        current->left->data.getAccountNumber() > account.getAccountNumber())
    {
      // insert the account as the sibling of the current node
      FNodePtr temp = current->left;           // Save the sibling of the current node
      current->left = new ForestNode(account); // Insert the account node
      current->left->left = temp;              // link the sibling to the new node created
      return true;
    }

    // Otherwise, move to the next sibling
    return insert(current->left, account);
  }
}

ForestTree::FNodePtr ForestTree::findParent(FNodePtr current, int accountNumber,
                                            int level) const
{
  if (current == nullptr)
  {
    return nullptr; // Base case: No parent found
  }

  // Check if the current node is the parent of the given account
  if (isChild(current->data.getAccountNumber(), accountNumber))
  {
    return current; // Found the parent node
  }

  // Recursively search for the parent in the children (next level)
  FNodePtr parentInRight = findParent(current->right, accountNumber, level + 1);
  if (parentInRight != nullptr)
  {
    return parentInRight;
  }

  // Recursively search for the parent in the siblings (same level)
  return findParent(current->left, accountNumber, level);
}

Account *ForestTree::findAccount(int accountNumber) const
{
  FNodePtr node = findNode(root, accountNumber);
  if (node != nullptr)
  {
    return &(node->data);
  }
  return nullptr; // Account not found
}

ForestTree::FNodePtr ForestTree::findNode(FNodePtr current,
                                          int accountNumber) const
{
  // Base case
  if (current == nullptr)
  {
    return nullptr; // Account not found
  }

  // Check if the current node is the one we are looking for
  if (current->data.getAccountNumber() == accountNumber)
  {
    return current;
  }

  // check if current node is the parent of the account
  if (isAncestor(current->data.getAccountNumber(), accountNumber))
  {
    // Recur to the next level (right child)
    return findNode(current->right, accountNumber);
  }

  // Otherwise, move to the next sibling
  return findNode(current->left, accountNumber);
}

bool ForestTree::applyTransaction(int accountNumber, Transaction *transaction)
{
  FNodePtr accountNode = findNode(root, accountNumber);
  if (!accountNode)
  {
    cerr << "Account " << accountNumber << " not found." << endl;
    return false;
  }

  // Check for sufficient balance in case of Debit
  if ((transaction->getTransactionType() == 'C' || transaction->getTransactionType() == 'C') &&
      accountNode->data.getBalance() < transaction->getTransactionAmount())
  {
    cerr << "Insufficient balance for account " << accountNumber << endl;
    return false;
  }

  // Add the transaction to the account
  accountNode->data.addTransaction(transaction); // Dereference pointer to pass the object

  // After applying the transaction, update parent balances
  updateParentBalances(accountNumber); // Update parent balances recursively

  return true;
}

void ForestTree::removeTransaction(const int &accountNumber, const int &transactionId)
{
    // Find the account
    Account *account = findAccount(accountNumber);
    
    if (account)
    {
        // Remove the transaction from the account
        account->removeTransaction(transactionId);
        cout << "Transaction with ID " << transactionId << " removed from the account " << accountNumber << endl;

       

        // Now update the parent balances
        cout << "Updating parent balances after transaction removal." << endl;
        updateParentBalances(accountNumber); // Pass the account node itself for parent updates
    }
    else
    {
        cout << "Account with the number " << accountNumber << " is not found" << endl;
    }
}

bool ForestTree::deleteAccount(int accountNumber)
{
    std::cout << "Attempting to delete account: " << accountNumber << std::endl;

    FNodePtr nodeToDelete = nullptr;

    // Check if the account is at the root
    if (root != nullptr && root->data.getAccountNumber() == accountNumber)
    {
        std::cout << "Account is the root. Deleting root account " << accountNumber << std::endl;
        destroy(root);  // Delete the root node
        root = nullptr;  // Set root to nullptr
        return true;     // Root account deleted successfully
    }

    // Call the recursive delete function to search and delete the account in all subtrees
    std::cout << "Searching and deleting account " << accountNumber << " in the tree." << std::endl;
    nodeToDelete = findNode(root, accountNumber);

    if (nodeToDelete != nullptr) {
        // Perform the actual deletion
        root = findNodeAndDelete(root, accountNumber);
        std::cout << "Account " << accountNumber << " deleted successfully, now updating parent balances." << std::endl;
        // Pass the node that was deleted to update parent balances
        updateParentBalances(nodeToDelete);
        return true;
    }

    std::cout << "Account " << accountNumber << " not found, deletion failed." << std::endl;
    return false;  // Account was not found or could not be deleted
}
void ForestTree::printTree() const
{
  if (root == nullptr)
  {
    cout << "\nTree is empty." << endl;
  }
  else
  {
    printTree(root, 0, "|_ ");
    cout << endl
         << "End of Tree" << endl;
  }
}

void ForestTree::printTree(FNodePtr node, int level, string prefix) const
{
  if (node == nullptr)
  {
    return;
  }

  // Indent according to the level
  for (int i = 0; i < level; ++i)
  {
    cout << "|     "; // 5 spaces
  }

  // Print current node
  cout << prefix << node->data.getAccountNumber() << " "
       << node->data.getDescription() << " (" << node->data.getBalance() << ")"
       << endl;

  // Recursively print children (right subtree)
  if (node->right != nullptr)
  {
    printTree(node->right, level + 1, "|_ ");
  }

  // Recursively print siblings (left subtree at the same level)
  if (node->left != nullptr)
  {
    printTree(node->left, level, "|_ ");
  }
}

void ForestTree::saveNodeRecursive(ofstream &outFile, FNodePtr node,
                                   int level) const
{
  if (!node)
    return;

  outFile << string(level * 2, ' ') << node->data.getAccountNumber() << " \""
          << node->data.getDescription() << "\" " << node->data.getBalance()
          << endl;

  saveNodeRecursive(outFile, node->right, level + 1);
  saveNodeRecursive(outFile, node->left, level);
}

void ForestTree::updateParentBalances(FNodePtr node)
{
    std::cout << "Updating parent balances starting from node with account number: " << node->data.getAccountNumber() << std::endl;

    // Recursively update balances for all parents
    while (node != nullptr)
    {
        // Find the parent of the current node
        FNodePtr parent = findParent(root, node->data.getAccountNumber(), 0);

        if (parent == nullptr)
        {
            std::cerr << "No valid parent found for account number " << node->data.getAccountNumber() << std::endl;
            break; // Stop when reaching a node with no parent (root level)
        }

        double updatedBalance = 0;

        // Sum up the balances of all children (subaccounts)
        FNodePtr child = parent->right;
        while (child != nullptr)
        {
            updatedBalance += child->data.getBalance();
            child = child->left; // Traverse siblings
        }

        std::cout << "Updating parent account " << parent->data.getAccountNumber()
                  << " with new balance: " << updatedBalance << std::endl;

        // Update the parent's balance
        parent->data.setBalance(updatedBalance);

        // Move up to the next level (parent of the current node)
        node = parent;
    }
}

void ForestTree::updateParentBalances(const int &accountNumber)
{
  // Find the node corresponding to the current account number
  FNodePtr node = findNode(root, accountNumber);

  if (node == nullptr)
  {
    std::cerr << "Account with number " << accountNumber << " not found!" << std::endl;
    return;
  }

  // Recursively update balances for all parents
  while (node != nullptr)
  {
    // Find the parent of the current node
    FNodePtr parent = findParent(root, node->data.getAccountNumber(), 0);

    if (parent == nullptr)
    {
      std::cerr << "No valid parent found for account number " << node->data.getAccountNumber() << std::endl;
      break; // Stop when reaching a node with no parent (root level)
    }

    double updatedBalance = 0;

    // Sum up the balances of all children (subaccounts)
    FNodePtr child = parent->right;
    while (child != nullptr)
    {
      updatedBalance += child->data.getBalance();
      child = child->left; // Traverse siblings
    }

    cout << "Updating parent account " << parent->data.getAccountNumber()
         << " with new balance: " << updatedBalance << endl;

    // Update the parent's balance
    parent->data.setBalance(updatedBalance);

    // Move up to the next level (parent of the current node)
    node = parent;
  }
}
void ForestTree::updateNodeBalance(FNodePtr current, int accountNumber, int delta)
{
  // Step 1: Find the parent of the current node
  FNodePtr parent = findParent(root, accountNumber, 0); // Assuming root is your tree's root pointer

  if (parent != nullptr)
  {
    // Step 2: Update the parent balances
    updateParentBalances(accountNumber);
  }
  else
  {
    std::cerr << "Parent not found for account number " << accountNumber << std::endl;
  }
}
void ForestTree::saveToFile(const string &fileName) const
{
  ofstream outFile(fileName);
  if (!outFile.is_open())
  {
    cerr << "Error: Could not open file " << fileName << " for writing."
         << endl;
    return;
  }

  try
  {
    // Start saving from the root node
    saveNodeRecursive(outFile, root, 0);
    cout << "Tree saved successfully to file: " << fileName << endl;
  }
  catch (const exception &e)
  {
    cerr << "Error during save operation: " << e.what() << endl;
  }

  outFile.close();
}

void ForestTree::generateReportFile(ForestTree::FNodePtr accountNode) const
{
  if (!accountNode)
  {
    cerr << "Error: Account node is null. Cannot generate report." << endl;
    return;
  }

  string truncatedDescription =
      accountNode->data.getDescription().substr(0, 10);
  replace(truncatedDescription.begin(), truncatedDescription.end(), ' ', '_');
  replace(truncatedDescription.begin(), truncatedDescription.end(), '/', '_');

  // Generate the filename with account number and truncated descri   ption
  string fileName = "accounts/account_" +
                    to_string(accountNode->data.getAccountNumber()) + "_" +
                    truncatedDescription + ".txt";

  // Open the file for writing
  ofstream reportFile(fileName);
  if (!reportFile.is_open())
  {
    cerr << "Error: Could not create file: " << fileName << endl;
    return;
  }

  // Write header with borders
  reportFile << "==========================================" << endl;
  reportFile << "               ACCOUNT REPORT              " << endl;
  reportFile << "==========================================" << endl;
  reportFile << "Account Number : " << accountNode->data.getAccountNumber()
             << endl;
  reportFile << "Description    : " << accountNode->data.getDescription()
             << endl;
  reportFile << "Balance        : $" << fixed << setprecision(2)
             << accountNode->data.getBalance() << endl;
  reportFile << "==========================================" << endl;

  // Subaccounts and transactions section
  if (accountNode->right)
  {
    reportFile << "SUBACCOUNTS" << endl;
    reportFile << "------------------------------------------" << endl;
    saveSubAccounts(reportFile, accountNode->right, 1); // Process subaccounts
  }
  else
  {
    reportFile << "No subaccounts available for this account.\n";
  }
  // Transactions section
  reportFile << "TRANSACTIONS" << endl;
  reportFile << "------------------------------------------" << endl;

  // Assuming accountNode->data has a method to get transactions
  const auto &transactions = accountNode->data.getTransactions(); // Assuming this returns a std::vector<Transaction*>

  if (!transactions.empty())
  {
    for (const auto *transaction : transactions)
    { // Iterate through the vector of Transaction pointers
      reportFile << "Transaction ID: " << transaction->getTransactionId() << endl;
      reportFile << "Type           : " << (transaction->getTransactionType() == 'D' ? "Debit" : "Credit") << endl;
      reportFile << "Amount         : $" << fixed << setprecision(2) << transaction->getTransactionAmount() << endl;
      reportFile << "------------------------------------------" << endl;
    }
  }
  else
  {
    reportFile << "No transactions available for this account.\n";
  }
  // Footer
  reportFile << "==========================================" << endl;
  reportFile << "        END OF ACCOUNT REPORT             " << endl;
  reportFile << "==========================================" << endl;

  reportFile.close();
  cout << "Report generated: " << fileName << endl;
}

void ForestTree::saveSubAccounts(ofstream &reportFile,
                                 ForestTree::FNodePtr node, int level) const
{
  if (!node)
    return;

  // Indentation for hierarchical structure
  string indentation(level * 4, ' ');

  // Write subaccount details
  reportFile << indentation << "- Subaccount: " << node->data.getAccountNumber()
             << endl;
  reportFile << indentation
             << "  Description : " << node->data.getDescription().substr(0, 10)
             << endl;
  reportFile << indentation << "  Balance     : $" << fixed << setprecision(2)
             << node->data.getBalance() << endl;
  reportFile << indentation << endl;

  // Recursively handle children and siblings
  saveSubAccounts(reportFile, node->right,
                  level + 1); // Process children (next level)
  saveSubAccounts(reportFile, node->left,
                  level); // Process siblings (same level)
}

void ForestTree::generateAccountReport(int accountNumber) const
{

  FNodePtr accountNode = findNode(root, accountNumber);
  if (!accountNode)
  {
    cerr << "Error: Account not found. Cannot generate report." << endl;
    return;
  }

  generateReportFile(accountNode);
}

ForestTree::FNodePtr ForestTree::findNodeAndDelete(FNodePtr node,
                                                   int accountNumber)
{
  // Base case: if the node is null, return null
  if (node == nullptr)
  {
    return nullptr;
  }

  // If the current node's account matches, delete it
  if (node->data.getAccountNumber() == accountNumber)
  {
    destroy(node);  // delete the current node and its children
    return nullptr; // return null to indicate this node is deleted
  }

  // Recursively search in the left and right subtrees
  node->left = findNodeAndDelete(node->left, accountNumber);
  node->right = findNodeAndDelete(node->right, accountNumber);

  // Return the potentially updated node (after recursion)
  return node;
}