/******************************************************************
  Implementation of an Account class:
  * Public methods:
    - Account: constructors to initialize the account
    - getAccountNumber: function to retrieve the account number
    - getDescription: function to retrieve the account description
    - getBalance: function to retrieve the account balance
    - getTransactions: function to retrieve the account's transactions
    - setAccountNumber: function to set the account number
    - setDescription: function to set the account description
    - setBalance: function to set the account balance
    - addTransaction: function to add a transaction to the account
    - removeTransaction: function to remove a transaction from the account
    - operator<<: function to output account details to a stream
    - operator>>: function to input account details from a stream
    - operator==: function to compare equality of two accounts
    - operator>: function to compare if one account is greater than another
    - operator<: function to compare if one account is less than another

  * Private attributes:
    - accountNumber: stores the unique identifier of the account
    - description: stores the description of the account
    - balance: stores the current balance of the account
    - transactions: stores a list of associated transactions
*****************************************************************
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Transaction.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {
public:
  /******* Account default constructor *****/
  /*Precondition: None
    Postcondition: An Account object is created with default values
  */
  Account();

  /******* Account parameterized constructor *****/
  /*Precondition: Valid accountNumber, description, and balance
    Postcondition: An Account object is created with the specified values
  */
  Account(int accountNumber, const string &description, double balance);

  /******* getAccountNumber function *****/
  /*Precondition: None
    Postcondition: Returns the account number of the account
  */
  int getAccountNumber() const;

  /******* getDescription function *****/
  /*Precondition: None
    Postcondition: Returns the description of the account
  */
  string getDescription() const;

  /******* getBalance function *****/
  /*Precondition: None
    Postcondition: Returns the current balance of the account
  */
  double getBalance() const;

  /******* getTransactions function *****/
  /*Precondition: None
    Postcondition: Returns a reference to the list of transactions associated
    with the account
  */
  vector<Transaction *> &getTransactions();

  /******* setAccountNumber function *****/
  /*Precondition: A valid account number
    Postcondition: Updates the account number of the account
  */
  void setAccountNumber(int accountNumber);

  /******* setDescription function *****/
  /*Precondition: A valid description string
    Postcondition: Updates the description of the account
  */
  void setDescription(const string &description);

  /******* setBalance function *****/
  /*Precondition: A valid balance value
    Postcondition: Updates the balance of the account
  */
  void setBalance(double balance);

  /******* addTransaction function *****/
  /*Precondition: A valid Transaction pointer
    Postcondition: Adds the specified transaction to the account
  */
  void addTransaction(Transaction *transaction);

  /******* removeTransaction function *****/
  /*Precondition: A valid transaction ID
    Postcondition: Removes the transaction with the specified ID from the
    account
  */
  void removeTransaction(const int &transactionId);

  /******* operator<< function *****/
  /*Precondition: A valid Account object
    Postcondition: Outputs account details to the given stream
  */
  friend ostream &operator<<(ostream &os, const Account &account);

  /******* operator>> function *****/
  /*Precondition: A valid Account object
    Postcondition: Inputs account details from the given stream
  */
  friend istream &operator>>(istream &is, Account &account);

  /******* operator== function *****/
  /*Precondition: Two valid Account objects
    Postcondition: Returns true if the two accounts are equal, false otherwise
  */
  bool operator==(const Account &other) const;

  /******* operator> function *****/
  /*Precondition: Two valid Account objects
    Postcondition: Returns true if this account is greater than the other, false
    otherwise
  */
  bool operator>(const Account &other) const;

  /******* operator< function *****/
  /*Precondition: Two valid Account objects
    Postcondition: Returns true if this account is less than the other, false
    otherwise
  */
  bool operator<(const Account &other) const;

private:
  int accountNumber;                  // Unique identifier of the account
  string description;                 // Description of the account
  double balance;                     // Current balance of the account
  vector<Transaction *> transactions; // List of associated transactions
};

#endif
