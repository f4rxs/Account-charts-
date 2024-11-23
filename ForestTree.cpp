#include "ForestTree.h"
#include <cstddef>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm> 
#include <sstream>   

// constructor to initialize the tree
ForestTree::ForestTree() : root(nullptr) {}

// destructor to delete the tree
ForestTree::~ForestTree() { destroy(root); }

// helper function to destroy and delete from a specific node
void ForestTree::destroy(FNodePtr node)
{
    if (node != nullptr)
    {
        destroy(node->left);  // Destroy children
        destroy(node->right); // Destroy siblings
        delete node;
    }
}

// function to get the root of the tree
ForestTree::FNodePtr ForestTree::getRoot() const { return root; }

// check if the tree is empty
bool ForestTree::isEmpty() const { return root == nullptr; }

// function to check if an account is a child of another account
bool ForestTree::isChild(int accountNumber, int subAccountNumber) const
{
    string parentString = to_string(accountNumber);
    string subAccountString = to_string(subAccountNumber);
    return subAccountString.find(parentString) == 0 &&
           subAccountString.length() == parentString.length() + 1;
}

// function to insert an account (node) in the tree
bool ForestTree::insert(const Account &account)
{
    if (isEmpty())
    {
        root = new ForestNode(account);
        return true;
    }
    // check if the account is on the 1st level so technically no parent
    if (account.getAccountNumber() < 10)
    {
        return insert(root, account);
    }

    // if the account is not on the 1st level
    // find the parent of the account
    FNodePtr parent = findParent(root, account.getAccountNumber(), 1);
    if (parent == nullptr)
    {
        cout << "\nParent account not found for account: "
             << account.getAccountNumber()
             << "\nParent account: " << account.getAccountNumber() / 10
             << " should exist first before inserting this account."
             << "\nAborting insertion...\n"
             << endl;
        return false;
    }
    return insert(parent, account);
}

// helper function to insert an account in the tree
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
        cout << "\nAccount already exists. id and description should be unique!"
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

// Helper function to find the parent node of a given account
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

// function to find an account in the tree
ForestTree::FNodePtr ForestTree::findAccount(int accountNumber) const
{
    return findNode(root, accountNumber);
}

// Helper function to find a node with a given account number
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
    if (isChild(current->data.getAccountNumber(), accountNumber))
    {
        // Recur to the next level (right child)
        return findNode(current->right, accountNumber);
    }

    // Otherwise, move to the next sibling
    return findNode(current->left, accountNumber);
}

// Public function to print the tree
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

// Private helper function
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

void ForestTree::saveNodeRecursive(ofstream &outFile, FNodePtr node, int level) const {
    if (!node) return;

    outFile << string(level * 2, ' ') 
            << node->data.getAccountNumber() << " \"" 
            << node->data.getDescription() << "\" " 
            << node->data.getBalance() << endl;

    saveNodeRecursive(outFile, node->right, level + 1);
    saveNodeRecursive(outFile, node->left, level);    
}

void ForestTree::saveToFile(const string &fileName) const {
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << " for writing." << endl;
        return;
    }

    try {
        // Start saving from the root node
        saveNodeRecursive(outFile, root, 0);
        cout << "Tree saved successfully to file: " << fileName << endl;
    } catch (const exception &e) {
        cerr << "Error during save operation: " << e.what() << endl;
    }

    outFile.close();
}


void ForestTree:: generateReportFile(ForestTree::FNodePtr accountNode) const {
  if (!accountNode) {
        cerr << "Error: Account node is null. Cannot generate report." << endl;
        return;
    }

    string truncatedDescription = accountNode->data.getDescription().substr(0, 10);
    replace(truncatedDescription.begin(), truncatedDescription.end(), ' ', '_'); 
    replace(truncatedDescription.begin(), truncatedDescription.end(), '/', '_'); 

    // Generate the filename with account number and truncated descri   ption
    string fileName = "accounts/account_" + to_string(accountNode->data.getAccountNumber()) + "_" + truncatedDescription + ".txt";

    // Open the file for writing
    ofstream reportFile(fileName);
    if (!reportFile.is_open()) {
        cerr << "Error: Could not create file: " << fileName << endl;
        return;
    }

    // Write header with borders
    reportFile << "==========================================" << endl;
    reportFile << "               ACCOUNT REPORT              " << endl;
    reportFile << "==========================================" << endl;
    reportFile << "Account Number : " << accountNode->data.getAccountNumber() << endl;
    reportFile << "Description    : " << accountNode->data.getDescription() << endl;
    reportFile << "Balance        : $" << fixed << setprecision(2) << accountNode->data.getBalance() << endl;
    reportFile << "==========================================" << endl;

    // Subaccounts and transactions section
    if (accountNode->right) {
        reportFile << "SUBACCOUNTS AND TRANSACTIONS" << endl;
        reportFile << "------------------------------------------" << endl;
        saveSubAccounts(reportFile, accountNode->right, 1); // Process subaccounts
    } else {
        reportFile << "No subaccounts available for this account.\n";
    }

    // Footer
    reportFile << "==========================================" << endl;
    reportFile << "        END OF ACCOUNT REPORT             " << endl;
    reportFile << "==========================================" << endl;

    reportFile.close();
    cout << "Report generated: " << fileName << endl;
}


void ForestTree:: saveSubAccounts(ofstream &reportFile, ForestTree::FNodePtr node, int level) const {
if (!node) return;

    // Indentation for hierarchical structure
    string indentation(level * 4, ' ');

    // Write subaccount details
    reportFile << indentation << "- Subaccount: " << node->data.getAccountNumber() << endl;
    reportFile << indentation << "  Description : " << node->data.getDescription().substr(0, 10) << endl;
    reportFile << indentation << "  Balance     : $" << fixed << setprecision(2) << node->data.getBalance() << endl;
    reportFile << indentation << "  (Same breakdown as account " << node->data.getAccountNumber() << ")" << endl;

    // Recursively handle children and siblings
    saveSubAccounts(reportFile, node->right, level + 1); // Process children (next level)
    saveSubAccounts(reportFile, node->left, level);      // Process siblings (same level)
}

void ForestTree::generateAccountReport(ForestTree &forestTree) const{
     int accountNumber;
    cout << "Enter the account number for which you want to generate a report: ";
    cin >> accountNumber;

    ForestTree::FNodePtr accountNode = forestTree.findAccount(accountNumber);
    if (!accountNode) {
        cout << "Error: Account not found!" << endl;
        return;
    }

     generateReportFile(accountNode);
}