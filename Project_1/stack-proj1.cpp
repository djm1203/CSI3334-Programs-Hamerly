/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: stack-proj1.cpp
 * Student name: Derek Martinez
 * assignment: project 1
 * due date: September 8,2023
 * version: 1.0
 *
 * This file contains the code for the Stack class.
 */

#include "stack-proj1.h"
#include <cassert>
#include <iostream>

using namespace std;

/* LocationStack
*
*  Parameters: void
*  Return value: none
*
*  This function is the default constructor for the stack class
*/
LocationStack::LocationStack(void){
    this->top = NULL;
}

/* ~LocationStack
*
*  Parameters: void
*  Return value: none
*
*  This is the destructor for the stack class
*/
LocationStack::~LocationStack(){
    delete this->top;
    this->top = NULL;
}

/* push
*
*  Parameters:
*   loc -- location object passed by reference
*  Return value: none
*
*  This function pushes a location object to the stack
*/
void LocationStack::push(const Location &loc){
    this->top = new LocationStackNode(loc, this->top);
}

/* pop
*
*  Parameters: void
*  Return value: none
*
*  This function pops location objects from the stack
*/
void LocationStack::pop(void){
    //check
    assert(!isEmpty());

    //take top node and replace
    LocationStackNode *temp = this->top;
    this->top = this->top->getNextNode();
    temp->setNextNode(NULL);

    delete temp;
}

/* getTop
*
*  Parameters: void
*  Return value: none
*
*  This function returns the location object on the top of the stack
*/
const Location& LocationStack::getTop(void) const{
    return (this->top->getLocation());
}

/* isEmpty
*
*  Parameters: void
*  Return value: none
*
*  This function checks the stack for location objects
*/
bool LocationStack::isEmpty(void) const{
    return (this->top == NULL);
}

/* isOn
*
*  Parameters:
*   loc -- location object passed by reference
*  Return value: none
*
*  This function checks for loc through the stack
*/
bool LocationStack::isOn(const Location &loc) const{
    LocationStackNode *temp = this->top;
    while (temp != NULL){
        if (temp->getLocation() == loc){
            return true;
        }
        temp = temp->getNextNode();
    }
    return false;
}

/* operator<<
*
*  Parameters:
*   os -- ostream for stack values
*   s -- stack object passed by reference
*  Return value: none
*
*  This function prints out values in stack
*/
ostream &operator<<(ostream &os, const LocationStack &s){
    LocationStackNode *curr = s.top;
    LocationStackNode *next = NULL;
    LocationStackNode *prev = NULL;

    //reverse links
    while (curr != NULL){
        next = curr->getNextNode();
        curr->setNextNode(prev);
        prev = curr;
        curr = next;
    }

    curr = prev;
    prev = NULL;
    //go through undoing the reverse
    while (curr != NULL){
        os << curr->getLocation() << endl;
        next = curr->getNextNode();
        curr->setNextNode(prev);
        prev = curr;
        curr = next;
    }

    return os;
}

/* LocationStackNode
*
*  Parameters:
*   loc -- location object passed by reference
*   next -- pointer to the next node in stack
*  Return value: none
*
*  This function is the default constructor for the LocationStackNode class
*/
LocationStackNode::LocationStackNode(const Location &loc, LocationStackNode *next){
    this->location = loc;
    this->nextNode = next;
}

/* ~LocationStackNode
*
*  Parameters: none
*  Return value: none
*
*  This function is the destructor for the LocationStackNode class
*/
LocationStackNode::~LocationStackNode(){
    delete this->nextNode;
}

/* getLocation
*
*  Parameters: none
*  Return value: none
*
*  This function returns the location for current LocationStackNode
*/
const Location& LocationStackNode::getLocation() const{
    return (this->location);
}

/* getNextNode
*
*  Parameters: none
*  Return value: none
*
*  This function returns next Node of LocationStackNode
*/
LocationStackNode *LocationStackNode::getNextNode() const{
    return (this->nextNode);
}

/* setNextNode
*
*  Parameters:
*   next -- pointer to the next node in stack
*  Return value: none
*
*  This function sets the nextNode to the next pointer next
*/
void LocationStackNode::setNextNode(LocationStackNode *next){
    this->nextNode = next;
}
