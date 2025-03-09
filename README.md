# ForestTree

## 🌲 Description
**ForestTree** is a robust hierarchical data management system designed to organize accounts and transactions within a forest tree structure. With its powerful features, it supports flexible account relationships, efficient transaction handling, and seamless data visualization, making it ideal for financial and data hierarchy applications.

---

## ✨ Key Features
- **Hierarchical Account Management**:
  - Insert, update, and delete accounts dynamically.
  - Supports parent-child and ancestor-descendant relationships.
- **Transaction Processing**:
  - Apply transactions to individual accounts.
  - Automatically update parent account balances upon transaction changes.
- **Detailed Reporting**:
  - Generate account-specific reports for insights into balances and transactions.
  - Save transactions and tree structure into files for persistent storage.
- **Tree Visualization**:
  - Print the entire tree structure to the console with clear indentation to represent hierarchy.

---

## 🛠️ Core Functionalities
### **Tree Operations**
- **`insert(accountNumber, parentAccountNumber)`**:
  Adds a new account under the specified parent account. If the parent is not specified, the account is added as a root node.
- **`findAccount(accountNumber)`**:
  Retrieves the account node based on its unique account number.
- **`deleteAccount(accountNumber)`**:
  Removes the specified account and restructures the tree accordingly.

### **Transaction Handling**
- **`applyTransaction(accountNumber, transactionAmount)`**:
  Adds a transaction to an account, updating the account’s balance.
- **`removeTransaction(accountNumber, transactionID)`**:
  Deletes a specific transaction and adjusts the balances of the account and its parents.
  
### **Visualization and Reporting**
- **`printTree()`**:
  Recursively prints the tree hierarchy, showing all accounts and their balances.
- **`saveToFile(filename)`**:
  Exports the current tree structure and account data to a specified file.
- **`generateAccountReport(accountNumber)`**:
  Produces a detailed report of a specific account, including its balance and transaction history.

---

## 💂️ Project Structure
```plaintext
├── Account.h / Account.cpp       # Defines account-related data structures and logic.
├── ForestTree.h / ForestTree.cpp # Manages the tree structure and operations.
├── Transaction.h / Transaction.cpp # Implements transaction handling logic.
├── main.cpp                      # Entry point for running and testing the application.
```

---

## 🚀 Getting Started

### Prerequisites
- A C++17 or newer compiler (e.g., `g++`).
- Basic knowledge of navigating the terminal/command prompt.

### Compilation
Run the following command to compile the program:
```bash
g++ main.cpp account.cpp foresttree.cpp transaction.cpp -o ForestTree
```

### Running the Program
Execute the compiled binary:
```bash
./ForestTree
```

---

## 📚 Example Workflow
1. **Initialize the Tree**:
   Begin with an empty forest tree structure or load from the defined using option 10.
2. **Add Accounts**:
   Insert accounts using the `insert` method and specify parent-child relationships.
3. **Apply Transactions**:
   Use `applyTransaction` to add financial transactions, which update the balances.
4. **Visualize and Save**:
   - Call `printTree` to display the structure.
   - Save the structure and transaction history using `saveToFile`.
5. **Generate Reports**:
   Create detailed account-specific reports with `generateAccountReport`.

---

## 🌟 Why Choose ForestTree?
- **Automatic Updates**:
  Parent account balances automatically adjust with child transactions.
- **Clear Hierarchies**:
  A simple and intuitive representation of account relationships.
- **Persistent Data**:
  Save and load your tree structure and transactions with ease.

---
## Images
<img width="960" alt="Screenshot 2025-03-09 123126" src="https://github.com/user-attachments/assets/d1387092-6a46-4589-9faf-27bde5ba7580" />
<img width="960" alt="Screenshot 2025-03-09 123335" src="https://github.com/user-attachments/assets/6ff33c24-71f5-4c52-8503-b85e467d9ba2" />
<img width="960" alt="Screenshot 2025-03-09 123445" src="https://github.com/user-attachments/assets/c83dd968-5936-4ecc-9c1a-7420ea69f8b3" />
<img width="960" alt="Screenshot 2025-03-09 123518" src="https://github.com/user-attachments/assets/7428d660-7f96-41fe-9ceb-f4b124dcabd3" />






