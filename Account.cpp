#include "Account.h"

// Constructors
Account::Account() : accountNumber(0), description(""), balance(0.0) {}

Account::Account(int accountNumber, const string &description, double balance)
    : accountNumber(accountNumber), description(description), balance(balance) {}

// Getter Methods
int Account::getAccountNumber() const
{
    return accountNumber;
}

string Account::getDescription() const
{
    return description;
}

double Account::getBalance() const
{
    return balance;
}

const vector<Transaction *> &Account::getTransactions() const
{
    return transactions;
}

// Setter Methods
void Account::setAccountNumber(int accountNumber)
{
    this->accountNumber = accountNumber;
}

void Account::setDescription(const string &description)
{
    this->description = description;
}

void Account::setBalance(double balance)
{
    this->balance = balance;
}

void Account::addTransaction(Transaction *transaction)
{
    transactions.push_back(transaction);
    if (transaction->getTransactionType() == 'C' || transaction->getTransactionType() == 'c')
    {
        this->balance -= transaction->getTransactionAmount();
    }
    else if (transaction->getTransactionType() == 'D' || transaction->getTransactionType() == 'd')
    {
        this->balance += transaction->getTransactionAmount();
    }
}

bool Account::operator==(const Account &other) const
{
    return (this->accountNumber == other.accountNumber ||
            this->description == other.description);
}

bool Account::operator>(const Account &other) const
{
    return this->accountNumber > other.accountNumber;
}

bool Account::operator<(const Account &other) const
{
    return this->accountNumber < other.accountNumber;
}


ostream &operator<<(ostream &os, const Account &account)
{
    os << "Account Number: " << account.accountNumber
       << ", Description: " << account.description
       << ", Balance: " << account.balance << endl;

    os << "Transactions: " << endl;
    for (Transaction *trans : account.transactions)
    {
        os << *trans << endl;
    }

    os << endl;

    return os;
}

istream &operator>>(istream &is, Account &account)
{
    cout << "\nEnter Account Number: ";
    is >> account.accountNumber;
    cout << "Enter Description: ";
    is.ignore();
    getline(is, account.description);
    cout << "Enter Balance: ";
    is >> account.balance;
    return is;
}
