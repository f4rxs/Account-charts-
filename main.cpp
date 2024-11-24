#include <iostream>
#include <fstream>
#include <sstream>
#include "Account.h"
#include "Transaction.h"
#include "ForestTree.h"

using namespace std;

void loadAccountsFromFile(const string &fileName, ForestTree &forestTree);
void createEmptyForest(ForestTree &forestTree);
void addAccount(ForestTree &forestTree);
void addTransaction(ForestTree &forestTree);
void printTree(ForestTree &forestTree);
void generateAccountFileForDetails(ForestTree &forestTree);
void findAccount(ForestTree &forestTree);
void displayMenu();

int main()
{
    ForestTree forestTree; // Instantiate the tree here for usage across menu options
    int choice;

    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        while (!(cin >> choice)) // Handle non-numeric input
        {
            cout << "Invalid input! Please enter a number: ";
            cin.clear();               // Clear error flags
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
        }

        switch (choice)
        {
        case 1:
            createEmptyForest(forestTree);
            cout << "Empty forest has been created." << endl;
            break;
        case 2:
            addAccount(forestTree);
            break;
        case 3:
            // You can implement deleteAccount here
            cout << "Delete account functionality not yet implemented." << endl;
            break;
        case 4:
            addTransaction(forestTree);
            break;
        case 5:
            // You can implement deleteTransaction here
            cout << "Delete transaction functionality not yet implemented." << endl;
            break;
        case 6:
            findAccount(forestTree);
            break;
        case 7:
            generateAccountFileForDetails(forestTree);
            break;
        case 8:
            printTree(forestTree);
            break;
        case 9:
            // Save tree to file logic
            cout << "Save account charts functionality not yet implemented." << endl;
            break;
        case 10:
            // Load predefined chart logic
            loadAccountsFromFile("resources/accounts.txt", forestTree);
            cout << "Load predefined account charts functionality not yet implemented." << endl;
            break;
        case 11:
            // Load from saved file logic
            cout << "Load from saved file functionality not yet implemented." << endl;
            break;
        case 12:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please select a number between 1 and 12." << endl;
        }

        cout << endl;

    } while (choice != 12);

    return 0;
}

void displayMenu()
{
    cout << "\n==============================\n";
    cout << "       Chart of Accounts\n";
    cout << "==============================\n";
    cout << "1.  Create Empty Forest\n";
    cout << "2.  Add an Account\n";
    cout << "3.  Delete an Account\n";
    cout << "4.  Add a Transaction for an Account\n";
    cout << "5.  Delete a Transaction for an Account\n";
    cout << "6.  Find an Account\n";
    cout << "7.  Generate Detailed Account File\n";
    cout << "8.  Print Account Charts\n";
    cout << "9.  Save Account Charts\n";
    cout << "10. Load Predefined Account Charts Data\n";
    cout << "11. Load from Saved File\n";
    cout << "12. Exit\n";
    cout << "==============================\n";
}

void loadAccountsFromFile(const string &fileName, ForestTree &forestTree)
{
    string filePath = fileName;
    cout << "Attempting to open file: " << filePath << endl;
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

void createEmptyForest(ForestTree &forestTree)
{
    // forestTree.clear(); // Assuming a clear method exists in ForestTree to reset it
    cout << "Forest tree cleared." << endl;
}

void addAccount(ForestTree &forestTree)
{
    int accountNumber;
    string description;
    double balance;

    cout << "Enter an account number: ";
    while (!(cin >> accountNumber)) // Handle invalid numeric input
    {
        cout << "Invalid input! Please enter a valid account number: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    cout << "Enter a description for the account: ";
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, description);

    cout << "Enter the balance for the account: ";
    while (!(cin >> balance)) // Handle invalid numeric input
    {
        cout << "Invalid input! Please enter a valid balance: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    Account newAccount(accountNumber, description, balance);
    forestTree.insert(newAccount);
    cout << "Account added successfully!" << endl;
}

void addTransaction(ForestTree &forestTree)
{
    int accountNumber;
    double amount;
    char type;

    cout << "Enter the account number for the transaction: ";
    while (!(cin >> accountNumber))
    {
        cout << "Invalid input! Please enter a valid account number: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    cout << "Enter the transaction amount: ";
    while (!(cin >> amount))
    {
        cout << "Invalid input! Please enter a valid amount: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    cout << "Enter the transaction type (e.g., Deposit or Withdrawal): ";
    cin >> type;

    Transaction transaction(amount, type);
    forestTree.applyTransaction(accountNumber, &transaction);
    cout << "Transaction added successfully!" << endl;
}

void findAccount(ForestTree &forestTree)
{
    int accountNumber;
    cout << "Enter the account number to find: ";
    while (!(cin >> accountNumber))
    {
        cout << "Invalid input! Please enter a valid account number: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    Account *account = forestTree.findAccount(accountNumber); // Assuming findAccount method exists
    if (account)
    {
        cout << "Account found: " << *account << endl; // Assuming Account has an overloaded << operator
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void printTree(ForestTree &forestTree)
{
    cout << "Printing tree (stub function, implement as needed):" << endl;
    forestTree.printTree(); // Assuming ForestTree has a print method
}

void generateAccountFileForDetails(ForestTree &forestTree)
{
    cout << "Generating account file (stub function, implement as needed)." << endl;
    // Implement file generation logic here
}
