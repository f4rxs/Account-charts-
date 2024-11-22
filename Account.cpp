#include "Account.h"

// Constructors
Account::Account() : accountNumber(0), description(""), balance(0.0) {}

Account::Account(int accountNumber, const string &description, double balance)
    : accountNumber(accountNumber), description(description), balance(balance) {}

// Getter Methods
int Account::getAccountNumber() const {
    return accountNumber;
}

string Account::getDescription() const {
    return description;
}

double Account::getBalance() const {
    return balance;
}

const vector<Transaction*>& Account::getTransactions() const {
    return transactions;
}

const vector<Account*>& Account::getSubAccounts() const {
    return subAccounts;
}

// Setter Methods
void Account::setAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

void Account::setDescription(const string &description) {
    this->description = description;
}

void Account::setBalance(double balance) {
    this->balance = balance;
}

void Account::addTransaction(Transaction* transaction) {
    transactions.push_back(transaction);  // Adds the transaction pointer to the vector
}

void Account::addSubAccount(Account* subAccount) {
    subAccounts.push_back(subAccount);  // Adds the subaccount pointer to the vector
}

// Method to check if an account is a child of another
bool Account::isChildOf(const Account &parentAccount) const {
    // Logic for determining if this account is a child of the parent account
    return false;  // Placeholder for actual logic
}

// Overloaded Operators
ostream &operator<<(ostream &os, const Account &account) {
    os << "Account Number: " << account.accountNumber
       << ", Description: " << account.description
       << ", Balance: " << account.balance << endl;
    
      os << "Transactions: " << endl;
    for (Transaction* trans : account.transactions) {
        os << "Transaction ID: " << trans->getTransactionId() << ", "
           << "Subaccount: " << trans->getTransactionSubaccount() << ", "
           << "Amount: " << trans->getTransactionAmount() << ", "
           << "Type: " << trans->getTransactionType() << endl;
    }

    os << "Subaccounts: ";
    for (Account* sub : account.subAccounts) {
        os << sub->getAccountNumber() << " ";
    }
    os << endl;

    return os;
}

istream &operator>>(istream &is, Account &account) {
    cout << "Enter Account Number: ";
    is >> account.accountNumber;
    cout << "Enter Description: ";
    is.ignore();
    getline(is, account.description);
    cout << "Enter Balance: ";
    is >> account.balance;
    return is;
}
