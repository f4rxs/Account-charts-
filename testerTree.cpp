#include "Account.h"
#include "ForestTree.h"
#include <iostream>

using namespace std;

int main() {
  ForestTree tree;
  // Root account
  Account acc1(1, "Root Account", 100.0);
  Account acc13(88, "Child #1 of 8", 60.0);
  // Direct children of root
  Account acc4(13, "Child #1 of 1", 60.0);
  Account acc2(11, "Child #2 of 1", 50.0);
  Account acc3(12, "Child #3 of 1", 75.0);

  // Children of account 11
  Account acc5(111, "Child #1 of 11", 25.0);
  Account acc6(112, "Child #2 of 11", 40.0);

  // Children of account 12
  Account acc7(121, "Child #1 of 12", 35.0);

  // Further children
  Account acc8(1111, "Child #1 of 111", 20.0);
  Account acc9(1211, "Child #1 of 121", 30.0);

  // account with id 2
  Account acc10(2, "Account #2", 200.0);

  // Account with id 9
  Account acc11(9, "Account #9", 90.0);
  // child of 9
  Account acc12(91, "Child #1 of 9", 45.0);

  // Add accounts to the tree
  tree.insert(acc1); // Root
  tree.insert(acc4); // Yet another child of 1
  tree.insert(acc2); // Child of 1
  tree.insert(acc3); // Another child of 1

  tree.insert(acc5);  // Child of 11
  tree.insert(acc6);  // Another child of 11
  tree.insert(acc7);  // Child of 12
  tree.insert(acc8);  // Child of 111
  tree.insert(acc9);  // Child of 121
  tree.insert(acc10); // Account with id 2
  tree.insert(acc11); // Account with id 9
  tree.insert(acc12); // Child of 9
  tree.insert(acc13); // Child of 9

  // Print the tree structure
  cout << "Tree Structure:" << endl;
  tree.printTree();
  return 0;
}
