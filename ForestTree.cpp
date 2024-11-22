#include "ForestTree.h"

// constructor to initialize the tree
ForestTree::ForestTree() : root(nullptr) {}

// destructor to delete the tree
ForestTree::~ForestTree() {
    destroy(root);
}

// helper function to destroy and delete from a specific node
void ForestTree::destroy(FNodePtr node) {
    if (node != nullptr) {
        destroy(node->left);  // Destroy children
        destroy(node->right); // Destroy siblings
        delete node;
    }
}

// function to get the root of the tree
ForestTree::FNodePtr ForestTree::getRoot() const {
    return root;
}

// check if the tree is empty
bool ForestTree::isEmpty() const {
    return root == nullptr;
}


// function to check if an account is a sub-account of another (his child)
bool ForestTree::isChild(const Account& parent, const Account& potentialChild) const {
    string parentStr = to_string(parent.getAccountNumber());
    string childStr = to_string(potentialChild.getAccountNumber());
    cout << "Parent: " << parentStr << " Child substring: " << childStr.substr(0, parentStr.size()) << endl;
    cout << "is he the child? " << ((childStr.substr(0, parentStr.size()) == parentStr)? "yes" : "No") << endl;
    return childStr.substr(0, parentStr.size()) == parentStr;
}


// function to insert an account (node) in the tree
bool ForestTree::insert(const Account& account) {
    if (isEmpty()) {
        root = new ForestNode(account);
        return true;
    }
    cout << "Inserting account: " << account.getAccountNumber() << endl;
    return insert(root, account);
}

// helper function to insert an account in the tree
bool ForestTree::insert(FNodePtr& current, const Account& account) {
    // If the current node is nullptr, insert here
    if (current == nullptr) {
        current = new ForestNode(account);
        return true;
    }

    // Check if the current node is the parent of the account
    if (isChild(current->data, account)) {
        // Recur to the next level (left child)
        return insert(current->left, account);
    } else {
        // Otherwise, move to the next sibling
        return insert(current->right, account);
    }
}

// Public function to print the tree
void ForestTree::printTree() const {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
    } else {
        printTree(root, 0, "");
    }
}

// Private helper function
void ForestTree::printTree(FNodePtr node, int level, string prefix) const {
    if (node == nullptr) {
        return;
    }

    // Indent according to the level
    for (int i = 0; i < level; ++i) {
        cout << "|    "; // 4 spaces for each level
    }

    // Print current node
    cout << prefix << node->data.getAccountNumber() << " " 
         << node->data.getDescription() << " (" 
         << node->data.getBalance() << ")" << endl ;

    // Recursively print children (left subtree)
    if (node->left != nullptr) {
        printTree(node->left, level + 1, "|_ ");
    }

    // Recursively print siblings (right subtree at the same level)
    if (node->right != nullptr) {
        printTree(node->right, level, "|_ ");
    }
}


