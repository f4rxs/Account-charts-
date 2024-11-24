#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>
#include <string>
#include "Transaction.h"

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
     vector<Transaction*>& getTransactions(); 

    // Setter Methods
    void setAccountNumber(int accountNumber);
    void setDescription(const string &description);
    void setBalance(double balance);
    void addTransaction(Transaction* transaction);  
    void removeTransaction(const int &transactionId);


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
