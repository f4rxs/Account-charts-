/******************************************************************
  Header file for the `Transaction` class:

  This class represents a transaction associated with an account,
  supporting functionality for accessing, modifying, and comparing
  transaction details.

  * Public Methods:
    - Transaction: constructors to initialize a transaction
    - getTransactionId: function to get the transaction ID
    - getTransactionAmount: function to get the transaction amount
    - getTransactionType: function to get the type of transaction
    - setTransactionId: function to set the transaction ID
    - setTransactionAmount: function to set the transaction amount
    - setTransactionType: function to set the transaction type
    - setTransaction: function to set all transaction details
    - operator<<: function to output transaction details
    - operator>>: function to input transaction details
    - operator==: function to compare equality of two transactions
    - operator>: function to compare two transactions
    - operator<: function to compare two transactions

  * Private Members:
    - nextTransactionId: static member for generating unique transaction IDs
    - transactionId: stores the unique ID of the transaction
    - amount: stores the monetary value of the transaction
    - type: stores the transaction type (e.g., debit 'D' or credit 'C')

******************************************************************/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Transaction {
public:
  /******* Default Constructor *******/
  /* Precondition: None
     Postcondition: Initializes a transaction with default values
                    and generates a unique transaction ID.
  */
  Transaction();

  /******* Parameterized Constructor *******/
  /* Precondition: A valid amount and type ('D' for debit, 'C' for credit)
     Postcondition: Initializes a transaction with the given values
                    and generates a unique transaction ID.
  */
  Transaction(const double &amount, const char &type);

  /******* getTransactionId function *******/
  /* Precondition: None
     Postcondition: Returns the unique ID of the transaction.
  */
  int getTransactionId() const;

  /******* getTransactionAmount function *******/
  /* Precondition: None
     Postcondition: Returns the monetary value of the transaction.
  */
  double getTransactionAmount() const;

  /******* getTransactionType function *******/
  /* Precondition: None
       Postcondition: Returns the type of the transaction.
  */
  char getTransactionType() const;

  /******* setTransactionId function *******/
  /* Precondition: A valid transaction ID
       Postcondition: Sets the unique ID of the transaction.
  */
  void setTransactionId(int transactionId);

  /******* setTransactionAmount function *******/
  /* Precondition: A valid amount
       Postcondition: Sets the monetary value of the transaction.
  */
  void setTransactionAmount(double amount);

  /******* setTransactionType function *******/
  /* Precondition: A valid type ('D' for debit, 'C' for credit)
       Postcondition: Sets the type of the transaction.
  */
  void setTransactionType(char type);

  /******* setTransaction function *******/
  /* Precondition: A valid transaction ID, account number, amount, and type
       Postcondition: Sets all transaction details.
  */
  void setTransaction(int transactionId, const string &account, double amount,
                      char type);

  /******* operator<< function *******/
  /* Precondition: A valid ostream object and transaction object
       Postcondition: Outputs the transaction details to the console.
  */
  friend ostream &operator<<(ostream &os, const Transaction &transaction);

  /******* operator>> function *******/
  /* Precondition: A valid istream object and transaction object
       Postcondition: Inputs the transaction details from the console.
  */
  friend istream &operator>>(istream &is, Transaction &transaction);

  /******* operator== function *******/
  /* Precondition: A valid transaction object
       Postcondition: Returns true if the transaction IDs are equal.
  */
  bool operator==(const Transaction &other) const;

  /******* operator> function *******/
  /* Precondition: A valid transaction object
       Postcondition: Returns true if the transaction ID is greater.
  */
  bool operator>(const Transaction &other) const;

  /******* operator< function *******/
  /* Precondition: A valid transaction object
       Postcondition: Returns true if the transaction ID is less.
  */
  bool operator<(const Transaction &other) const;

private:
  static int nextTransactionId; // static member for generating unique IDs
  int transactionId;            // unique identifier for the transaction
  double amount;                // monetary amount involved in the transaction
  char type; // type of the transaction ('C' for credit, 'D' for debit, etc.)
};

#endif