/* CSI 3334
* Project 3 -- Tree Based Encryption
* Filename: bst-student-proj3.h
* Student name: Derek Martinez
* assignment: project 3
* due date: October 6,2023
* version: 1.0
*
* This file implements the classes BST,
* BSTNode, and encryptionTree
*/
#ifndef BST_STUDENT_PROJ3
#define BST_STUDENT_PROJ3

#include "bst-prof-proj3.h"

/* ~BSTNode
*
*  Parameters: none
*  Return value: none
*
*  This is the destructor for the BSTNode class
*/
template <class Base>
BSTNode<Base>::~BSTNode(){
    delete right;
    delete left;
    left = right = nullptr;
}

/* minNode
*
*  Parameters: none
*  Return value: none
*
*  This function locates the min node of the tree
*/
template <class Base>
const BSTNode<Base> *BSTNode<Base>::minNode() const{
    if(this->left == nullptr){
        return this;
    }else{
        return this->left->minNode();
    }
}

/* maxNode
*
*  Parameters: none
*  Return value: none
*
*  This function locates the max node of the tree
*/
template <class Base>
const BSTNode<Base> *BSTNode<Base>::maxNode() const{
    if(right == nullptr){
        return this;
    }else{
        return right->maxNode();
    }
}

/* printPreorder
*
*  Parameters:
*       os -- outputs the object in the tree
*       indent -- amount of space depending on height in tree
*  Return value: none
*
*  This function prints the tree in preorder
*/
template <class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const{
    os << indent << data << endl;
    if (left != nullptr) {
        left->printPreorder(os, indent + "  ");
    } else {
        os << indent << "  NULL" << endl;
    }

    if (right != nullptr) {
        right->printPreorder(os, indent + "  ");
    } else {
        os << indent << "  NULL" << endl;
    }
}

/* remove
*
*  Parameters:
*       item -- object to be removed from tree
*  Return value: none
*
*  This function locates the item and removes it from the tree
*/
template <class Base>
void BST<Base>::remove(const Base &item){
    BSTNode<Base> *toRemove = root;
    BSTNode<Base> *parent = nullptr;
    bool found = false;

    //find the node and parent
    while (toRemove != nullptr && !found) {
        if (item < toRemove->data) {
            parent = toRemove;
            toRemove = toRemove->left;
        } else if (toRemove->data < item) {
            parent = toRemove;
            toRemove = toRemove->right;
        } else {
            found = true;
        }
    }

    //if not in tree exit
    if (!found) {
        return;
    }

    //else start looking for each case
    if(toRemove->left != nullptr && toRemove->right != nullptr) { //has two children
        BSTNode<Base> *leftMost = toRemove->right;
        BSTNode<Base> *leftMostParent = toRemove;

        if (leftMost->left != nullptr) {
            while (leftMost->left != nullptr) {
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }
            leftMostParent->left = leftMost->right;
            leftMost->right = toRemove->right;
        }
        leftMost->left = toRemove->left;

        if(parent != nullptr) {
            if (parent->left == toRemove) {
                parent->left = leftMost;
            } else {
                parent->right = leftMost;
            }
        }else{
            root = leftMost;
        }

        toRemove->left = toRemove->right = nullptr;
        leftMostParent = nullptr;
        delete toRemove;
    } else if (toRemove->left != nullptr || toRemove->right != nullptr) { //has one child
        BSTNode<Base> *child = nullptr;

        if (toRemove->left != nullptr) {
            child = toRemove->left;
            toRemove->left = nullptr;
        } else {
            child = toRemove->right;
            toRemove->right = nullptr;
        }

        if (parent != nullptr) {
            if (parent->left == toRemove) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            root = child;
        }
        delete toRemove;
    } else {
        if (parent != nullptr) {
            if (parent->left == toRemove) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }

        delete toRemove;
        if (parent == nullptr) {
            root = nullptr;
        }
    }
}

/* insert
*
*  Parameters:
*       item -- object to be inserted to the tree
*  Return value: none
*
*  This function inserts a node into the tree
*/
template <class Base>
void BST<Base>::insert(const Base &item) {
    BSTNode<Base> *node = new BSTNode<Base>(item);
    BSTNode<Base> *curr = root;
    BSTNode<Base> *prev = nullptr;

    if (root == nullptr) {
        root = node;
        return;
    }

    while (curr != nullptr) {
        prev = curr;

        if (item < curr->data) {
            curr = curr->left;
        } else if ( curr->data < item) {
            curr = curr->right;
        } else {
            delete node;
            return;
        }
    }

    if (item < prev->data) {
        prev->left = node;
    } else {
        prev->right = node;
    }
}

/* encrypt
*
*  Parameters:
*       item -- object to be encrypted
*  Return value: none
*
*  This function encrypts a message
*/
template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const{
    string msg = "r";
    bool valid = false;
    const BSTNode<Base> *tmp = this->root;

    while (tmp != nullptr) {
        if (item < tmp->getData()) {
            msg += "0";
            tmp = tmp->getLeft();
        }else if (tmp->getData() < item) {
            msg += "1";
            tmp = tmp->getRight();
        }else{
            valid = true;
            tmp = nullptr;
        }
    }

    if(!valid){
        msg = "?";
    }

    return msg;
}

/* decrypt
*
*  Parameters:
*       path -- object to be decrypted
*  Return value: none
*
*  This function decrypts a string
*/
template <class Base>
const Base *EncryptionTree<Base>::decrypt(const string &path) const{
    const BSTNode<Base> *tmp = this->root;

    if (tmp == nullptr) {
        return nullptr;
    }

    for(int i = 0; i < path.length(); i++){
        if (tmp == nullptr) {
            return nullptr;
        }

        if (path[i] == '0') {
            tmp = tmp->getLeft();
        }else if (path[i] == '1') {
            tmp = tmp->getRight();
        }
    }

    return &tmp->getData();
}


#endif
