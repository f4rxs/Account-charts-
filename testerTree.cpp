#include "Account.h"
#include "ForestTree.h"
#include <iostream>

using namespace std;

int main() {
    ForestTree tree;

    // Root account
    Account acc1(1, "Root Account", 100.0);

    // Direct children of root
    Account acc4(13, "Child of 1", 60.0);
    Account acc2(11, "Child of 1", 50.0);
    Account acc3(12, "Child of 1", 75.0);
   

    // Children of account 11
    Account acc5(111, "Child of 11", 25.0);
    Account acc6(112, "Child of 11", 40.0);

    // Children of account 12
    Account acc7(121, "Child of 12", 35.0);

    // Further children
    Account acc8(1111, "Child of 111", 20.0);
    Account acc9(1211, "Child of 121", 30.0);

    // Add accounts to the tree
    tree.insert(acc1); // Root
    tree.insert(acc4); // Yet another child of 1
    tree.insert(acc2); // Child of 1
    tree.insert(acc3); // Another child of 1
   
    tree.insert(acc5); // Child of 11
    tree.insert(acc6); // Another child of 11
    tree.insert(acc7); // Child of 12
    tree.insert(acc8); // Child of 111
    tree.insert(acc9); // Child of 121

    // Print the tree structure
    cout << "Tree Structure:" << endl;
    tree.printTree();

    return 0;
}
