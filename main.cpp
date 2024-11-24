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
    // string fileNameToSaved = "resources/savedAccounts.txt";
    readAccountsFromFile(fileName, forestTree);
     forestTree.applyTransaction(68725,(new Transaction(500,'D')));
    forestTree.generateAccountReport(68);
    forestTree.printTree();




  

  

  

    return 0;
}

void readAccountsFromFile(const string &fileName, ForestTree &forestTree)
{
    string filePath = fileName;
    cout << "Attempting to open file: "<<filePath << endl;
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
