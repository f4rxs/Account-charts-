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


   readAccountsFromFile(fileName, forestTree);

forestTree.printTree();


    // // Create a few transactions
    // Transaction t1(1, "Deposit", 200.0, 'C');
    // Transaction t2(2, "Withdrawal", 150.0, 'D');
    // Transaction t3(3, "Deposit", 50.0, 'C');

    // // Create an account and set it up
    // Account account(1, "Main Account", 1000.0);

    // // Add transactions to the account by using their pointers
    // account.addTransaction(&t1); // Store pointer to Transaction
    // account.addTransaction(&t2); // Store pointer to Transaction
    // account.addTransaction(&t3); // Store pointer to Transaction

    // // Create subaccounts and add them to the main account
    // Account subAccount1(11, "Subaccount 1", 500.0);
    // Account subAccount2(12, "Subaccount 2", 200.0);

    // // Output account details
    // cout << "Account Details: " << endl;
    // cout << account << endl;

    // cout << endl;

    // // Test input and output using overloaded operators
    // Account inputAccount;
    // cout << "Enter account details (Account Number, Description, Balance): ";
    // cin >> inputAccount;
    // cout << "You entered: " << endl;
    // cout << inputAccount << endl;

    return 0;
}

void readAccountsFromFile(const string &fileName, ForestTree &forestTree)
{
    string filePath = fileName;
    cout << "Attempting to open file: DS-Lebanese-Accounts/accounts.txt" << endl;
    // Open the file
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Ignore empty lines or comments

        stringstream ss(line);
        int accountNumber;
        string description;
        double balance;

        if (ss >> accountNumber) {
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

