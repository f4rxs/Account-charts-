#include <iostream>
#include <fstream>
#include <sstream>
#include "Account.h"
#include "Transaction.h"
#include "ForestTree.h"

using namespace std;

void readAccountsFromFile(const string &fileName, ForestTree &forestTree);
int main()
{
    ForestTree forestTree;

    string fileName = "resources/accounts.txt";
    string fileNameToSaved = "resources/savedAccounts.txt";
    readAccountsFromFile(fileName, forestTree);

    forestTree.printTree();

    forestTree.saveToFile(fileNameToSaved);

        forestTree = ForestTree();
    cout<<"Reading from the saved file"<<endl;
    readAccountsFromFile(fileNameToSaved,forestTree);

   forestTree.generateAccountReport(forestTree);



    // ForestTree tree;

    // // Insert accounts to build a sample tree
    // tree.insert(Account(1,"Super Account",1000));
    // tree.insert(Account(101, "ParentAccount", 5000.0));
    // tree.insert(Account(1011, "ChildAccount1", 3000.0));
    // tree.insert(Account(1012, "ChildAccount2", 2000.0));
    // tree.insert(Account(10111, "GrandChildAccount", 1000.0));
    // tree.insert(Account(102, "SiblingAccount", 4000.0));

    // // Test the findParent function
    // int accountNumberToFind = 102; // Replace with an account number to test
    // ForestTree::FNodePtr parent = tree.findParent(tree.getRoot(), accountNumberToFind, 3);

    // if (parent != nullptr) {
    //     cout << "Parent found: " << endl;
    //     cout << "Account Number: " << parent->data.getAccountNumber() << endl;
    //     cout << "Description: " << parent->data.getDescription() << endl;
    //     cout << "Balance: " << parent->data.getBalance() << endl;
    // } else {
    //     cout << "No parent found for account number " << accountNumberToFind << endl;
    // }

    // tree.printTree();

    return 0;
}

void readAccountsFromFile(const string &fileName, ForestTree &forestTree)
{
    string filePath = fileName;
    cout << "Attempting to open file: DS-Lebanese-Accounts/accounts.txt" << endl;
    // Open the file
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue; // Ignore empty lines or comments

        stringstream ss(line);
        int accountNumber;
        string description;
        double balance;

        if (ss >> accountNumber)
        {
            getline(ss, description, '"');
            getline(ss, description, '"');
            ss >> balance;

            Account account(accountNumber, description, balance);

            forestTree.insert(account);
        }
    }

    file.close();
    cout << "Accounts loaded successfully from file." << endl;
}
