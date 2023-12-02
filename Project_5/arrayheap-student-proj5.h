/* CSI 3334
* Project 5 -- Real-Time Batch Operating System Simulator
* Filename: arrayheap-student-proj5.h
* Student name: Derek Martinez
* assignment: project 5
* due date: November 10,2023
* version: 1.0
*
* This file implements the classes ArrayHeap
*/

#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

/* ArrayHeap
*
*  Parameters: none
*  Return value: none
*
*  This is the default constructor
*/
template <typename T>
ArrayHeap<T>::ArrayHeap(){
    numItems = 0;
    capacity = 10;
    data = new T[capacity];
    heapAndFreeStack = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        heapAndFreeStack[i] = i;
    }
}

/* ArrayHeap
*
*  Parameters:
*       h -- object to be copied
*  Return value: none
*
*  This is the copy constructor
*/
template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    capacity = h.capacity;
    numItems = h.numItems;
    data = new T[capacity];
    heapAndFreeStack = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
        data[i] = h.data[i];
    }
}

/* ~ArrayHeap
*
*  Parameters: none
*  Return value: none
*
*  This is the destructor
*/
template <typename T>
ArrayHeap<T>::~ArrayHeap(){
    numItems = 0;
    capacity = 10;
    delete[] data;
    delete[] heapAndFreeStack;
}

/* getMinItem
*
*  Parameters: none
*  Return value: highest priority value
*
*  This function returns the min item
*/
template <typename T>
T const &ArrayHeap<T>::getMinItem() const{
    return data[heapAndFreeStack[0]];
}

/* getNumItems
*
*  Parameters: none
*  Return value: number of items
*
*  This function returns the number of items in heap
*/
template <typename T>
int ArrayHeap<T>::getNumItems() const{
    return numItems;
}

/* bubbleUp
*
*  Parameters:
*       ndx -- value to bubble up from
*  Return value: none
*
*  This function bubbles up from index to root
*/
template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx){
    int parent = (ndx - 1) / 2;

    if (data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]) {
        swap(heapAndFreeStack[ndx], heapAndFreeStack[parent]);
        bubbleUp(parent);
    }
}

/* bubbleDown
*
*  Parameters:
*       ndx -- value to start bubbling down from
*  Return value: none
*
*  This function bubbles down from index to leaf
*/
template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int child1 = (ndx * 2) + 1;
    int child2 = (ndx * 2) + 2;

    if (child1 < numItems) {
        int lesserChild = child1;

        if ((child2 < numItems) &&
        (data[heapAndFreeStack[child2]] <  data[heapAndFreeStack[child1]])) {
            lesserChild = child2;
        }

        if (data[heapAndFreeStack[lesserChild]] < data[heapAndFreeStack[ndx]]) {
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            bubbleDown(lesserChild);
        }
    }
}

/* insert
*
*  Parameters:
*       item -- value to place in heap
*  Return value: none
*
*  This function inserts a value to heap and bubbles
*  up from bottom of tree
*/
template <typename T>
void ArrayHeap<T>::insert(T const &item){
    if (numItems >= capacity){
        doubleCapacity();
    }

    data[heapAndFreeStack[numItems]] = item;
    bubbleUp(numItems);
    numItems++;
}

/* doubleCapacity
*
*  Parameters: none
*  Return value: none
*
*  This function doubles capacity of heap
*/
template <typename T>
void ArrayHeap<T>::doubleCapacity(){
    int newCapacity = capacity * 2;
    T *tmpData = new T[newCapacity];
    int *tmpHeap = new int[newCapacity];

    for (int i = 0; i < capacity; i++) {
        tmpData[i] = this->data[i];
        tmpHeap[i] = this->heapAndFreeStack[i];
    }
    for (int i = capacity; i < newCapacity; i++) {
        tmpHeap[i] = i;
    }

    delete[] data;
    delete[] heapAndFreeStack;
    data = tmpData;
    heapAndFreeStack = tmpHeap;
    capacity = newCapacity;
}

/* removeMinItem
*
*  Parameters: none
*  Return value: none
*
*  This function removes the smallest item
*/
template <typename T>
void ArrayHeap<T>::removeMinItem(){
    numItems--;
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems]);
    bubbleDown(0);
}

/* operator=
*
*  Parameters:
*       ah -- object set equal to
*  Return value: return address of new heap
*
*  This is the equals overloading function for array heap class
*/
template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    if (this != &ah) {
        delete[] data;
        delete[] heapAndFreeStack;

        capacity = ah.capacity;
        numItems = ah.numItems;
        data = new T[capacity];
        heapAndFreeStack = new int[capacity];

        for (int i = 0; i < capacity; i++) {
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            data[i] = ah.data[i];
        }
    }
    return *this;
}
#endif
