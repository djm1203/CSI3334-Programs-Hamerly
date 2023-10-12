/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: arrayqueue-student-proj2.h
 * Student name: Derek Martinez
 * assignment: project 2
 * due date: September 22,2023
 * version: 1.0
 *
 * This file implements the arrayqueue functions
 */

#ifndef ARRAY_QUEUE_STUDENT_PROJ2_H
#define ARRAY_QUEUE_STUDENT_PROJ2_H

#include "arrayqueue-prof-proj2.h"
#include <cassert>

/*********************************************************
 * PUT YOUR CODE HERE                                    *
 *********************************************************/

/* ArrayQueue
*
*  Parameters: none
*  Return value: none
*
*  This is the default constructor for the arrayqueue class
*/
template <class Base>
ArrayQueue<Base>::ArrayQueue(){
    this->capacity = 10;
    this->front = 0;
    this->length = 0;
    this->data = new Base[this->capacity];
}

/* ArrayQueue
*
*  Parameters:
*       q -- info placed into arrayqueue constructor
*  Return value: none
*
*  This is the constructor for the arrayqueue class
*/
template <class Base>
ArrayQueue<Base>::ArrayQueue(const ArrayQueue<Base> &q){
    this->front = 0;
    this->length = q.length;
    this->capacity = q.capacity;
    this->data = new Base[this->capacity];

    for(int i = 0; i < this->length; i++){
        this->data[i] = q.data[(q.front + i) % this->capacity];
    }
}

/* ~ArrayQueue
*
*  Parameters: none
*  Return value: none
*
*  This is the destructor for the arrayqueue class
*/
template <class Base>
ArrayQueue<Base>::~ArrayQueue(){
    delete[] this->data;
    this->length = 0;
    this->capacity = 0;
    this->front = 0;
}

/* add
*
*  Parameters:
*       item -- value added onto arrayqueue
*  Return value: none
*
*  This function adds a value to front of queue
*/
template <class Base>
void ArrayQueue<Base>::add(const Base &item){
    if(this->length >= this->capacity){
        this->doubleCapacity();
    }
    this->data[(this->front + this->length) % this->capacity] = item;
    this->length++;
}

/* remove
*
*  Parameters: none
*  Return value: none
*
*  This function removes an object from the front of the queue
*/
template <class Base>
void ArrayQueue<Base>::remove(){
    assert(this->length > 0);
    this->length--;
    this->front = (this->front + 1) % this->capacity;
}

/* getFront()
*
*  Parameters: none
*  Return value: last value of placed into Array Queue
*
*  This functions returns the front of the queue
*/
template <class Base>
const Base &ArrayQueue<Base>::getFront() const{
    return (this->data[this->front]);
}

/* getLength
*
*  Parameters: none
*  Return value: number of values in Array Queue
*
*  This is the constructor for the arrayqueue class
*/
template <class Base>
int ArrayQueue<Base>::getLength() const{
    return (this->length);
}

/* operator=
*
*  Parameters:
*       q -- arrayqueue set equal to other queue
*  Return value: none
*
*  This is the overloaded equal operator for ArrayQueue
*/
template <class Base>
const ArrayQueue<Base> &ArrayQueue<Base>::operator=(const ArrayQueue<Base> &q){
    if (this != &q){
        delete[] this->data;
        this->capacity = q.capacity;
        this->length = q.length;
        this->front = 0;
        this->data = new Base[this->capacity];

        for (int i = 0; i < this->length; i++) {
            this->data[i] = q.data[(q.front + i) % this->capacity];
        }
    }
    return *this;
}

/* doubleCapacity
*
*  Parameters: none
*  Return value: none
*
*  This function doubles the size of the ArrayQueue
*/
template <class Base>
void ArrayQueue<Base>::doubleCapacity(){
    Base *tmp = this->data;
    int oldCap = this->capacity;

    this->capacity *= 2;
    this->data = new Base[this->capacity];

    for(int i = 0; i < this->length; i++){
        this->data[i] = tmp[(this->front + i) % oldCap];
    }
    delete[] tmp;
    this->front = 0;
}

#endif