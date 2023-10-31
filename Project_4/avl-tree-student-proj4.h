/* CSI 3334
* Project 4 -- AVL Based Encryption
* Filename: avl-tree-student-proj4.h
* Student name: Derek Martinez
* assignment: project 4
* due date: October 27,2023
* version: 1.0
*
* This file implements the classes BST,
* BSTNode, and encryptionTree
*/

#ifndef PROJECT_4_AVL_TREE_STUDENT_PROJ4_H
#define PROJECT_4_AVL_TREE_STUDENT_PROJ4_H

#include "avl-tree-prof-proj4.h"
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <queue>

/* ~AVLNode
*
*  Parameters: none
*  Return value: none
*
*  This is the destructor for the BSTNode class
*/
template <class Base>
AVLNode<Base>::~AVLNode(){
    delete right;
    delete left;
    left = right = nullptr;
}

/* singleRotateLeft
*
*  Parameters:
*       none
*  Return value: child with highest height
*
*  This function rotates left
*/
template <class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateLeft(){
    AVLNode<Base> *rightChild = right;
    right = rightChild->left;
    rightChild->left = this;

    this->updateHeight();
    rightChild->updateHeight();

    return rightChild;
}

/* singleRotateRight
*
*  Parameters:
*       none
*  Return value: child with highest height
*
*  This function rotates right
*/
template <class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateRight(){
    AVLNode<Base> *leftChild = left;
    left = leftChild->right;
    leftChild->right = this;

    this->updateHeight();
    leftChild->updateHeight();

    return leftChild;
}

/* doubleRotateLeftRight
*
*  Parameters:
*       none
*  Return value: child with highest height
*
*  This function rotates left right
*/
template <class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateLeftRight(){
    left = left->singleRotateLeft();
    return this->singleRotateRight();
}

/* doubleRotateRightLeft
*
*  Parameters:
*       none
*  Return value: child with highest height
*
*  This function rotates right left
*/
template <class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateRightLeft(){
    right = right->singleRotateRight();
    return this->singleRotateLeft();
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
void AVLTree<Base>::insert(const Base &item){
    //store path
    vector<AVLNode<Base>*> nodePtr;

    AVLNode<Base> *curr = root;
    AVLNode<Base> *prev = nullptr;
    AVLNode<Base> *node = new AVLNode<Base>(item);

    //empty tree
    if (root == nullptr) {
        root = node;
        return;
    }

    //start insertion

    while (curr != nullptr) {
        nodePtr.push_back(curr);
        prev = curr;

        if (item < curr->data) { //insert on left
            curr = curr->left;
            //nodePtr.push_back(curr->left);
        } else if (curr->data < item) { //insert on right
            curr = curr->right;
            //nodePtr.push_back(curr->right);
        } else { //item already in tree
            delete node;
            return;
        }
    }

    if (item < prev->data) {
        prev->left = node;
    } else {
        prev->right = node;
    }
    //fix path after insertion
    this->rebalancePathToRoot(nodePtr);
}

/* rebalancePathToRoot
*
*  Parameters:
*       path -- pointers to tree path
*  Return value: none
*
*  This function rebalances path
*/
template <class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path){
    for (int i = path.size() - 1; i >= 0; i--) {
        AVLNode<Base> *node = path.at(i);
        AVLNode<Base> *pNode;

        //keep track of previous node
        if (i > 0) {
            pNode = path.at(i - 1);
        } else {
            pNode = nullptr;
        }

        //Store height differences
        int heightDiff = node->getHeight(node->left) - node->getHeight(node->right);

        //Test each side for imbalances
        if (heightDiff > 1) {
            if (node->left->getHeight(node->left->left) <
                node->left->getHeight(node->left->right)) {
                //left-right rotation
                if (i == 0) {
                    root = node->doubleRotateLeftRight();
                } else if (pNode->right == node) {
                    pNode->right = node->doubleRotateLeftRight();
                } else {
                    pNode->left = node->doubleRotateLeftRight();
                }
            } else {
                // left-left case
                if (i == 0) {
                    this->root = node->singleRotateRight();
                } else if (pNode->right == node) {
                    pNode->right = node->singleRotateRight();
                } else {
                    pNode->left = node->singleRotateRight();
                }
            }
        } else if (heightDiff < -1) {
            if (node->right->getHeight(node->right->left) >
                node->right->getHeight(node->right->right)){
                if(i == 0) {
                    root = node->doubleRotateRightLeft();
                } else if (pNode->right == node) {
                    pNode->right = node->doubleRotateRightLeft();
                } else {
                    pNode->left = node->doubleRotateRightLeft();
                }
            } else {
                if (i == 0) {
                    root = node->singleRotateLeft();
                } else if (pNode->right == node) {
                    pNode->right = node->singleRotateLeft();
                } else {
                    pNode->left = node->singleRotateLeft();
                }
            }
        }
        node->updateHeight();
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
void AVLTree<Base>::remove(const Base &item){
    if (root == nullptr) {
        return;
    }
    vector<AVLNode<Base>*> nodePtr;

    AVLNode<Base> *toRemove = root;
    AVLNode<Base> *parent = nullptr;
    bool found = false;

    //find the node and parent
    while (toRemove != nullptr && !found) {
        nodePtr.push_back(toRemove);
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
        AVLNode<Base> *leftMost = toRemove->right;
        AVLNode<Base> *leftMostParent = toRemove;
        int ndx = nodePtr.size() - 1;

        if (leftMost->left != nullptr) {
            while (leftMost->left != nullptr) {
                nodePtr.push_back(leftMost);
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }
            leftMostParent->left = leftMost->right;
            leftMost->right = toRemove->right;
        }
        leftMost->left = toRemove->left;
        nodePtr.at(ndx) = leftMost;

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
        this->rebalancePathToRoot(nodePtr);
        delete toRemove;
    } else if (toRemove->left != nullptr || toRemove->right != nullptr) { //has one child
        AVLNode<Base> *child = nullptr;

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
        this->rebalancePathToRoot(nodePtr);
        delete toRemove;
    } else {
        if (parent != nullptr) {
            if (parent->left == toRemove) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }

        this->rebalancePathToRoot(nodePtr);
        delete toRemove;
        if (parent == nullptr) {
            root = nullptr;
        }
    }
}

/* printLevelOrder
*
*  Parameters:
*       os -- outputs the object in the tree
*  Return value: none
*
*  This function prints the tree in level order
*/
template <class Base>
void AVLTree<Base>::printLevelOrder(ostream &os) const{
    if (root == nullptr) {
        os << "NULL" << endl;
        return;
    }

    int nodes = 0;
    const int MAX = 20;
    queue<AVLNode<Base>*> path;
    path.push(root);

    while(!path.empty()){
        AVLNode<Base> *curr = path.front();
        path.pop();
        nodes++;

        //has value
        if (curr) {
            os << curr->data;
            //push children in order left to right
            path.push(curr->left);
            path.push(curr->right);
        } else {
            cout << "NULL";
        }

        //reset and move to nxt level
        if (!path.empty()) {
            if (nodes >= MAX) {
                os << endl;
                nodes = 0;
            } else {
                os << " ";
            }
        }
    }
    os << endl;
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
void AVLNode<Base>::printPreorder(ostream &os, string indent) const{
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

/* minNode
*
*  Parameters: none
*  Return value: none
*
*  This function locates the min node of the tree
*/
template <class Base>
const AVLNode<Base> *AVLNode<Base>::minNode() const{
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
const AVLNode<Base> *AVLNode<Base>::maxNode() const{
    if(right == nullptr){
        return this;
    }else{
        return right->maxNode();
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
    const AVLNode<Base> *tmp = this->root;

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
    const AVLNode<Base> *tmp = this->root;

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
#endif //PROJECT_4_AVL_TREE_STUDENT_PROJ4_H
