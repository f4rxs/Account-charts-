#include <iostream>
#include "Account.h"
#include "Transaction.h"

using namespace std;

int main() {
    // Create a few transactions
    Transaction t1(1, "Deposit", 200.0, 'C');
    Transaction t2(2, "Withdrawal", 150.0, 'D');
    Transaction t3(3, "Deposit", 50.0, 'C');

    // Create an account and set it up
    Account account(1, "Main Account", 1000.0);
    
    // Add transactions to the account by using their pointers
   account.addTransaction(&t1);  // Store pointer to Transaction
    account.addTransaction(&t2);  // Store pointer to Transaction
    account.addTransaction(&t3);  // Store pointer to Transaction

    // Create subaccounts and add them to the main account
    Account subAccount1(11, "Subaccount 1", 500.0);
    Account subAccount2(12, "Subaccount 2", 200.0);
    

    // Output account details
    cout << "Account Details: " << endl;
    cout << account << endl;

    
   
    cout << endl;

    

    // Test input and output using overloaded operators
    Account inputAccount;
    cout << "Enter account details (Account Number, Description, Balance): ";
    cin >> inputAccount;
    cout << "You entered: " << endl;
    cout << inputAccount << endl;

    return 0;
}