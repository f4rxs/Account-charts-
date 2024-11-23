#include "Transaction.h"

Transaction::Transaction() : transactionId(0), account(""), amount(0.0), type('D') {}

Transaction::Transaction(int transactionId, const string &subaccount, double amount, char type)
{
    setTransaction(transactionId, subaccount, amount, type);
}

// Getters
int Transaction::getTransactionId() const { return transactionId; }
string Transaction::getTransactionAccount() const { return account; }
double Transaction::getTransactionAmount() const { return amount; }
char Transaction::getTransactionType() const { return type; }

// Setters
void Transaction::setTransactionId(int transactionId)
{
    this->transactionId = transactionId;
}

void Transaction::setTransactionAccount(const string &subaccount)
{
    this->account = subaccount;
}

void Transaction::setTransactionAmount(double amount)
{
    if (amount < 0)
    {
        throw invalid_argument("Amount must be positive.");
    }
    this->amount = amount;
}

void Transaction::setTransactionType(char type)
{
    if (type != 'D' && type != 'd' && type != 'C' && type != 'c')
    {
        throw invalid_argument("Transaction type must be 'D' (Debit) or 'C' (Credit).");
    }
    this->type = toupper(type);
}

void Transaction::setTransaction(int transactionId, const string &subaccount, double amount, char type)
{
    setTransactionId(transactionId);
    setTransactionAccount(subaccount);
    setTransactionAmount(amount);
    setTransactionType(type);
}

bool Transaction::operator==(const Transaction &other) const
{
    return this->transactionId == other.transactionId;
}

bool Transaction::operator>(const Transaction &other) const
{
    return this->amount > other.amount;
}

bool Transaction::operator<(const Transaction &other) const
{
    return this->amount < other.amount;
}

// Overloaded Operators
ostream &operator<<(ostream &os, const Transaction &transaction)
{
    os << "Transaction ID: " << transaction.transactionId
       << ", Account: " << transaction.account
       << ", Amount: " << transaction.amount
       << ", Type: " << (transaction.type == 'D' ? "Debit" : "Credit");
    return os;
}

istream &operator>>(istream &is, Transaction &transaction)
{
    cout << "Enter Transaction ID: ";
    is >> transaction.transactionId;

    cout << "Enter account: ";
    is >> transaction.account;

    cout << "Enter Amount: ";
    is >> transaction.amount;

    cout << "Enter Type (D for Debit, C for Credit): ";
    is >> transaction.type;

    // Validation
    if (transaction.amount < 0)
    {
        throw invalid_argument("Amount must be positive.");
    }
    if (transaction.type != 'D' && transaction.type != 'C' && transaction.type != 'd' && transaction.type != 'c')
    {
        throw invalid_argument("Transaction type must be 'D' (Debit) or 'C' (Credit).");
    }

    transaction.type = toupper(transaction.type);

    return is;
}