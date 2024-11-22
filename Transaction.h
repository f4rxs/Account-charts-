#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <stdexcept> 

using namespace std;

class Transaction
{
public:
    Transaction();
    Transaction(int transactionId, const string &subaccount, double amount, char type);

    int getTransactionId() const;
    string getTransactionSubaccount() const;
    double getTransactionAmount() const;
    char getTransactionType() const;

    void setTransactionId(int transactionId);
    void setTransactionSubAccount(const string &subaccount);
    void setTransactionAmount(double amount);
    void setTransactionType(char type);
    void setTransaction(int transactionId, const string &subaccount, double amount, char type);

    friend ostream &operator<<(ostream &os, const Transaction &transaction);
    friend istream &operator>>(istream &is, Transaction &transaction);

private:
    int transactionId;
    string subaccount;
    double amount;
    char type; 
};

#endif