/* CSI 3334
* Project 6 -- Network Broadcasting
* Filename: arrayheap-student-proj6.cpp
* Student name: Derek Martinez
* assignment: project 6
* due date: December 8,2023
* version: 1.0
*
* This file implements the function from arrayHeap
*/

#ifndef ARRAY_HEAP_STUDENT_PROJ6_H
#define ARRAY_HEAP_STUDENT_PROJ6_H

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>

using namespace std;

/*********************************************************
* INSERT YOUR CODE HERE                                  *
*********************************************************/

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
    dataToHeap = new int[capacity];

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
    dataToHeap = new int[capacity];

    for (int i = 0; i < capacity; i++) {
        data[i] = h.data[i];
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
        dataToHeap[i] = h.dataToHeap[i];
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
    delete[] dataToHeap;
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
        delete[] dataToHeap;

        capacity = ah.capacity;
        numItems = ah.numItems;
        data = new T[capacity];
        heapAndFreeStack = new int[capacity];
        dataToHeap = new int[capacity];

        for (int i = 0; i < capacity; i++) {
            data[i] = ah.data[i];
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            dataToHeap[i] = ah.dataToHeap[i];
        }
    }
    return *this;
}

/* insert
*
*  Parameters:
*       item -- value to place in heap
*  Return value: index of new value
*
*  This function inserts a value to heap and bubbles
*  up from bottom of tree
*/
template <typename T>
int ArrayHeap<T>::insert(T const &item){
    if (numItems >= capacity) {
        doubleCapacity();
    }

    int oNdx = heapAndFreeStack[numItems];

    data[heapAndFreeStack[numItems]] = item;
    dataToHeap[heapAndFreeStack[numItems]] = numItems;
    bubbleUp(numItems);
    numItems++;

    return oNdx;
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
    swap(dataToHeap[heapAndFreeStack[0]], dataToHeap[heapAndFreeStack[numItems]]);
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems]);
    bubbleDown(0);
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

/* isOnHeap
*
*  Parameters:
*       key -- index to be checked
*  Return value: whether value is on the heap
*
*  This function returns whether the key is in the heap
*/
template <typename T>
bool ArrayHeap<T>::isOnHeap(int key) const{
    if (key >= 0 && key < capacity) {
        if (dataToHeap[key] >= 0 && dataToHeap[key] < numItems) {
            if (heapAndFreeStack[dataToHeap[key]] == key) {
                return true;
            }
        }
    }
    return false;
}

/* changeItemAtKey
*
*  Parameters:
*       key -- item to be replaced
*       newItem -- item that replaces key
*  Return value: none
*
*  This function changes an item at the key location
*/
template <typename T>
void ArrayHeap<T>::changeItemAtKey(int key, T const &newItem){
    if (isOnHeap(key)) {
        data[key] = newItem;
        bubbleUp(dataToHeap[key]);
        bubbleDown(dataToHeap[key]);
    }
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
    int *tmpDataToHeap = new int[newCapacity];

    for (int i = 0; i < capacity; i++) {
        tmpData[i] = data[i];
        tmpHeap[i] = heapAndFreeStack[i];
        tmpDataToHeap[i] = dataToHeap[i];
    }

    for (int i = capacity; i < newCapacity; i++) {
        tmpHeap[i] = i;
    }

    capacity = newCapacity;
    delete[] data;
    delete[] heapAndFreeStack;
    delete[] dataToHeap;
    data = tmpData;
    heapAndFreeStack = tmpHeap;
    dataToHeap = tmpDataToHeap;
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
        swap(dataToHeap[heapAndFreeStack[ndx]], dataToHeap[heapAndFreeStack[parent]]);
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
            swap(dataToHeap[heapAndFreeStack[ndx]], dataToHeap[heapAndFreeStack[lesserChild]]);
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            bubbleDown(lesserChild);
        }
    }
}

#endif