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
    Transaction(const double &amount,const  char &type); ;

    int getTransactionId() const;
    // string getTransactionAccount() const;
    double getTransactionAmount() const;
    char getTransactionType() const;

    void setTransactionId(int transactionId);
    // void setTransactionAccount(const string &subaccount);
    void setTransactionAmount(double amount);
    void setTransactionType(char type);
    void setTransaction(int transactionId, const string &account, double amount, char type);

    friend ostream &operator<<(ostream &os, const Transaction &transaction);
    friend istream &operator>>(istream &is, Transaction &transaction);

    bool operator==(const Transaction &other) const;
    bool operator>(const Transaction &other) const;
    bool operator<(const Transaction &other) const;

private:
    static int nextTransactionId;
    int transactionId;
    double amount;
    char type;
};

#endif