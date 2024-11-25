#include "Account.h"
#include "ForestTree.h"
#include "Transaction.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void loadAccountsFromFile(const string &fileName, ForestTree *forestTree);
ForestTree *createEmptyForest(ForestTree *&forestTree);
void addAccount(ForestTree *forestTree);
void addTransaction(ForestTree *forestTree);
void deleteTransaction(ForestTree *forestTree);
void deleteAccount(ForestTree *forestTree);
void printTree(ForestTree *forestTree);
void generateAccountFileForDetails(ForestTree *forestTree);
void findAccount(ForestTree *forestTree);
void saveChartsToFile(ForestTree forestTree, const string &fileName);
void displayMenu();

int main()
{
  ForestTree *forestTree = new ForestTree();
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
      forestTree = createEmptyForest(forestTree);
      cout << "Empty forest has been created." << endl;
      break;
    case 2:
      addAccount(forestTree);
      break;
    case 3:
      deleteAccount(forestTree);
      break;
    case 4:
      addTransaction(forestTree);
      break;
    case 5:
      deleteTransaction(forestTree);
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
      saveChartsToFile(*forestTree, "resources/savedAccounts.txt");
      break;
    case 10:
      // Load predefined chart logic
      loadAccountsFromFile("resources/accounts.txt", forestTree);
      cout
          << "Load predefined account charts functionality not yet implemented."
          << endl;
      break;
    case 11:
      // Load from saved file logic
      loadAccountsFromFile("resources/savedAccounts.txt", forestTree);
      break;
    case 12:
      cout << "Exiting the program. Goodbye!" << endl;
      break;
    default:
      cout << "Invalid choice! Please select a number between 1 and 12."
           << endl;
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

void loadAccountsFromFile(const string &fileName, ForestTree *forestTree)
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

      forestTree->insert(account);
    }
  }

  file.close();
  cout << "Accounts loaded successfully from file." << endl;
}

ForestTree *createEmptyForest(ForestTree *&forestTree)
{
  delete forestTree;
  ForestTree *newTree = new ForestTree();
  cout << "Forest tree cleared." << endl;
  return newTree;
}

void addAccount(ForestTree *forestTree)
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
  bool response = forestTree->insert(newAccount);
  if (response)
  {
    cout << "Account added successfully!" << endl;
  }
  else
  {
    cout << "Failed to add account." << endl;
  }
}

void addTransaction(ForestTree *forestTree)
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

  cout << "Enter the transaction type (D d for Debit , C c for credit): ";
  cin >> type;

  Transaction *transaction = new Transaction(amount, type);
  bool response = forestTree->applyTransaction(accountNumber, transaction);
  if (response)
  {
    cout << "Transaction applied successfully!" << endl;
  }
  else
  {
    cout << "Failed to apply transaction." << endl;
  }
}

// delete transaction function
void deleteTransaction(ForestTree *forestTree)
{
  int accountNumber;
  int transactionId;
  cout << "Enter the account number to delete transaction: ";
  while (!(cin >> accountNumber))
  {
    cout << "Invalid input! Please enter a valid account number: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }

  Account account = *forestTree->findAccount(accountNumber);

  if (account.getTransactions().empty())
  {
    cout << "No transactions found for account number " << accountNumber
         << endl;
    return;
  }

  cout << "Transactions for account number " << accountNumber << ":" << endl
       << "--------------------------------" << endl
       << endl;
  for (const auto *transaction : account.getTransactions())
  {
    cout << "- Transaction ID: " << transaction->getTransactionId() << endl;
    cout << "- Transaction Ammount: " << transaction->getTransactionAmount() << endl;
    cout << "- Transaction Type: " << transaction->getTransactionType() << endl;
  }

  cout << "Enter the transaction ID to delete: ";
  while (!(cin >> transactionId))
  {
    cout << "Invalid input! Please enter a valid transaction ID: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }

  forestTree->removeTransaction(accountNumber, transactionId);
}

// delete account function
void deleteAccount(ForestTree *forestTree)
{
  int accountNumber;
  cout << "Enter the account number to delete: ";
  while (!(cin >> accountNumber))
  {
    cout << "Invalid input! Please enter a valid account number: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }

  bool response = forestTree->deleteAccount(accountNumber);
  if (response)
  {
    cout << "Account deleted successfully!" << endl;
  }
  else
  {
    cout << "Failed to delete account." << endl;
  }
}

void findAccount(ForestTree *forestTree)
{
  int accountNumber;
  cout << "Enter the account number to find: ";
  while (!(cin >> accountNumber))
  {
    cout << "Invalid input! Please enter a valid account number: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }

  Account *account = forestTree->findAccount(
      accountNumber); // Assuming findAccount method exists
  if (account)
  {
    cout << "Account found: " << *account
         << endl; // Assuming Account has an overloaded << operator
  }
  else
  {
    cout << "Account not found." << endl;
  }
}

void printTree(ForestTree *forestTree)
{
  cout << "Printing tree:" << endl;
  forestTree->printTree(); // Assuming ForestTree has a print method
}

void saveChartsToFile(ForestTree forestTree, const string &fileName)
{
  string savePath = fileName;
  forestTree.saveToFile(fileName);
}

void generateAccountFileForDetails(ForestTree *forestTree)
{
  int accountNumber;
  cout << "Enter the account number to find: ";
  while (!(cin >> accountNumber))
  {
    cout << "Invalid input! Please enter a valid account number: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }
  forestTree->generateAccountReport(accountNumber);
}
