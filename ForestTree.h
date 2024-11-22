#ifndef FORRESTTREE_H
#define FORRESTTREE_H

#include <iostream>
using namespace std;

template <typename ElementType>
class ForestTree {
    private:
    // class for a node in the tree
    class ForestNode {
        public:
            ElementType data; // data of the node
            ForestNode* left; // pointer to first child in the next level
            ForestNode* right; // pointer to sibling in the same level

            // constructor to initialize the node
            ForestNode(ElementType data) {
                this->data = data;
                left = nullptr;
                right = nullptr;
        }
    };

    typedef ForestNode * FNodePtr; ;
    FNodePtr root; // pointer to the root of the tree

    public: 
        ForestTree();
        ~ForestTree();
        bool isEmpty();
        bool insert(ElementType& data);   
        bool remove(ElementType& data);
        bool search(ElementType& data);

    private:
        bool insert(FNodePtr& root, ElementType& data);
};

#endif // end of FORRESTTREE_H

/*Starting the implementation of the ForestTree class
************************************************************/

// constructor to initialize the tree
template <typename ElementType>
ForestTree<ElementType>::ForestTree() {
    root = nullptr;
}

// destructor to delete the tree
template <typename ElementType>
ForestTree<ElementType>::~ForestTree() {
    // to be implemented
}

// function to check if the tree is empty
template <typename ElementType>
bool ForestTree<ElementType>::isEmpty() {
    return root == nullptr;
}

// function to insert a new node in the tree
template <typename ElementType>
bool ForestTree<ElementType>::insert(ElementType& data) {
    // base case: if the tree is empty
    if (isEmpty()) {
        root = new ForestNode(data);
        return true;
    }

    // recursive case: if the tree is not empty
    return insert(root, data);
}

// helper function to insert a new node in the tree
template <typename ElementType>
bool ForestTree<ElementType>::insert(FNodePtr& root, ElementType& data) {
    // if the data is already in the tree
    if (root->data == data) {
        return false;
    }

    // still did not implement the rest lol
}

/*End of the implementation of the ForestTree class */