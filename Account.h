#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>
#include <string>
#include "Transaction.h" // Include the Transaction class

using namespace std;

class Account
{
public:
    // Constructors
    Account();
    Account(int accountNumber, const string &description, double balance);

    // Getter Methods
    int getAccountNumber() const;
    string getDescription() const;
    double getBalance() const;
    const vector<Transaction*>& getTransactions() const;  // Returns the vector of transaction pointers

    // Setter Methods
    void setAccountNumber(int accountNumber);
    void setDescription(const string &description);
    void setBalance(double balance);
    void addTransaction(Transaction* transaction);  // Adds a transaction pointer


    // Overloaded Operators
    friend ostream &operator<<(ostream &os, const Account &account);
    friend istream &operator>>(istream &is, Account &account);

    bool operator==(const Account &other) const;
    bool operator>(const Account &other) const;
    bool operator<(const Account &other) const;
    


private:
    int accountNumber;
    string description;
    double balance;
    vector<Transaction*> transactions; 
};

#endif
