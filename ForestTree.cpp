#include "ForestTree.h"
#include <cstddef>

// constructor to initialize the tree
ForestTree::ForestTree() : root(nullptr) {}

// destructor to delete the tree
ForestTree::~ForestTree() { destroy(root); }

// helper function to destroy and delete from a specific node
void ForestTree::destroy(FNodePtr node) {
  if (node != nullptr) {
    destroy(node->left);  // Destroy children
    destroy(node->right); // Destroy siblings
    delete node;
  }
}

// function to get the root of the tree
ForestTree::FNodePtr ForestTree::getRoot() const { return root; }

// check if the tree is empty
bool ForestTree::isEmpty() const { return root == nullptr; }

// function to check if an account is a sub-account of another (his child)
bool ForestTree::isChild(const Account &parent,
                         const Account &potentialChild) const {
  string parentStr = to_string(parent.getAccountNumber());
  string childStr = to_string(potentialChild.getAccountNumber());
  cout << "Parent: " << parentStr
       << " Child substring: " << childStr.substr(0, parentStr.size()) << endl;
  cout << "is he the child? "
       << ((childStr.substr(0, parentStr.size()) == parentStr) ? "yes" : "No")
       << endl;
  return childStr.substr(0, parentStr.size()) == parentStr;
}

// function to insert an account (node) in the tree
bool ForestTree::insert(const Account &account) {
  if (isEmpty()) {
    root = new ForestNode(account);
    return true;
  }
  cout << "Inserting account: " << account.getAccountNumber() << endl;
  return insert(root, account);
}

// if the account is not on the 1st level
// find the parent of the account
FNodePtr parent = findParent(root, account.getAccountNumber());
if (parent == nullptr) {
  cout << "\nParent account not found for account: "
       << account.getAccountNumber()
       << "\nParent account: " << account.getAccountNumber() / 10
       << " should exist first before inserting this account."
       << "\nAborting insertion...\n"
       << endl;
  return false;
}
return insert(parent, account);
}

// helper function to insert an account in the tree
bool ForestTree::insert(FNodePtr &current, const Account &account) {
  // If the current node is nullptr, insert here

  cout << "Inserting account: " << account.getAccountNumber() << endl;
  if (current == nullptr) {
    current = new ForestNode(account);
    return true;
  }

  // check if it is the same account (either same id or same description)
  if (current->data.getAccountNumber() == account.getAccountNumber() ||
      current->data.getDescription() == account.getDescription()) {
    cout << "Account already exists. id and description should be unique!"
         << endl;
    return false;
  }

  // Check if the current node is the parent of the account
  if (isChild(current->data, account)) {
    // check if the 1st child is bigger than the account
    if (current->left != nullptr &&
        current->left->data.getAccountNumber() > account.getAccountNumber()) {
      // insert the account as the child of the current node
      FNodePtr temp = current->left; // Save the child of the current node
      current->left = new ForestNode(account); // Insert the account node
      current->left->right =
          temp; // link the child to the new node created as a sibling
      return true;
    }
    // Recur to the next level (left child)
    return insert(current->left, account);
  } else {
    // check if next sibling is bigger than the account
    if (current->right != nullptr &&
        current->right->data.getAccountNumber() > account.getAccountNumber()) {
      // insert the account as the sibling of the current node
      FNodePtr temp = current->right; // Save the sibling of the current node
      current->right = new ForestNode(account); // Insert the account node
      current->right->right = temp; // link the sibling to the new node created
      return true;
    }

    // Otherwise, move to the next sibling
    return insert(current->left, account);
  }
}

// Helper function to find the parent node of a given account
ForestTree::FNodePtr ForestTree::findParent(FNodePtr current,
                                            int accountNumber) const {
  // Base case
  if (current == nullptr) {
    return nullptr; // No parent found in this branch
  }

  // Check if the current node is the parent of the given account
  if (isChild(current->data.getAccountNumber(), accountNumber)) {
    return current;
  }

  // Recursively search in the children (next level)
  FNodePtr parentInRight = findParent(current->right, accountNumber);
  if (parentInRight != nullptr) {
    return parentInRight; // Parent found in the right subtree
  }

  // If not found in the right, check the left sibling (same level)
  return findParent(current->left, accountNumber);
}

// function to find an account in the tree
ForestTree::FNodePtr ForestTree::findAccount(int accountNumber) const {
  return findNode(root, accountNumber);
}

// Helper function to find a node with a given account number
ForestTree::FNodePtr ForestTree::findNode(FNodePtr current,
                                          int accountNumber) const {
  // Base case
  if (current == nullptr) {
    return nullptr; // Account not found
  }

  // Check if the current node is the one we are looking for
  if (current->data.getAccountNumber() == accountNumber) {
    return current;
  }

  // check if current node is the parent of the account
  if (isChild(current->data.getAccountNumber(), accountNumber)) {
    // Recur to the next level (right child)
    return findNode(current->right, accountNumber);
  }

  // Otherwise, move to the next sibling
  return findNode(current->left, accountNumber);
}

// Public function to print the tree
void ForestTree::printTree() const {
  if (root == nullptr) {
    cout << "Tree is empty." << endl;
  } else {
    printTree(root, 0, "|_ ");
    cout << endl << "End of Tree" << endl;
  }
}

// Private helper function
void ForestTree::printTree(FNodePtr node, int level, string prefix) const {
  if (node == nullptr) {
    return;
  }

  // Indent according to the level
  for (int i = 0; i < level; ++i) {
    cout << "|     "; // 5 spaces
  }

  // Print current node
  cout << prefix << node->data.getAccountNumber() << " "
       << node->data.getDescription() << " (" << node->data.getBalance() << ")"
       << endl;

  // Recursively print children (left subtree)
  if (node->left != nullptr) {
    printTree(node->left, level + 1, "|_ ");
  }

  // Recursively print siblings (right subtree at the same level)
  if (node->right != nullptr) {
    printTree(node->right, level, "|_ ");
  }
}
