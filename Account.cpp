#include "Account.h"

Account::Account() : accountNumber(0), description(""), balance(0.0) {}

Account::Account(int accountNumber, const string &description, double balance)
    : accountNumber(accountNumber), description(description), balance(balance)
{
}

int Account::getAccountNumber() const { return accountNumber; }

string Account::getDescription() const { return description; }

double Account::getBalance() const { return balance; }

// Return a non-const reference so we can modify the transactions vector
vector<Transaction *> &Account::getTransactions() { return transactions; }

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
  if (this->balance > 0)
    this->balance = balance;
  else
  {
    this->balance = 0;
  }
}

void Account::addTransaction(Transaction *transaction)
{
  transactions.push_back(transaction);
  if (transaction->getTransactionType() == 'C' ||
      transaction->getTransactionType() == 'c')
  {
    this->balance -= transaction->getTransactionAmount();
  }
  else if (transaction->getTransactionType() == 'D' ||
           transaction->getTransactionType() == 'd')
  {
    this->balance += transaction->getTransactionAmount();
  }
}

void Account::removeTransaction(const int &transactionId)
{
  auto &transactions =
      getTransactions(); // Get the transactions (non-const reference)

  for (auto it = transactions.begin(); it != transactions.end(); ++it)
  {
    if ((*it)->getTransactionId() == transactionId)
    {
      if ((*it)->getTransactionType() == 'D' ||
          (*it)->getTransactionType() == 'd')
      {
        balance -= (*it)->getTransactionAmount(); // Revert debit
      }
      else if ((*it)->getTransactionType() == 'C' ||
               (*it)->getTransactionType() == 'c')
      {
        balance += (*it)->getTransactionAmount(); // Revert credit
      }

      transactions.erase(it);
      cout << "Transaction with ID " << transactionId << " has been removed."
           << endl;
      return;
    }
  }

  cout << "Transaction with ID " << transactionId << " not found." << endl;
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
  if (account.transactions.empty())
  {
    os << "No transactions found." << endl;
  }
  else
  {
    // const auto &transactions =account.transactions;
    // for (const auto &trans : transactions)
    // {
    //   os << "Transaction ID: " << trans->getTransactionId() << endl;
    //   os << "Amount: " << trans->getTransactionAmount() << endl;
    //   os << "Type: " << trans->getTransactionType() << endl;
    // }
    const auto &transactions = account.transactions;
    for (const auto &trans : transactions)
    {
      if (trans == nullptr)
      {
        std::cerr << "Warning: Null pointer in transactions vector.\n";
        continue;
      }
      os << "Transaction ID: " << trans->getTransactionId() << std::endl;
      os << "Amount: " << trans->getTransactionAmount() << std::endl;
      os << "Type: " << trans->getTransactionType() << std::endl;
    }
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
