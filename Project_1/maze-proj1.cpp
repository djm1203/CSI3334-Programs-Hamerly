/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: maze-proj1.cpp
 * Student name: Derek Martinez
 * assignment: project 1
 * due date: September 8,2023
 * version: 1.0
 *
 * This file contains the code for the maze class.
 */

#include <iostream>
#include <cassert>
#include "maze-proj1.h"

const int MIN = 1;
const int MAX = 10000;

using namespace std;

/* Maze
*
*  Parameters: void
*  Return value: none
*
*  This is the default constructor for the maze class
*/
Maze::Maze(void){
    this->validLocationCount = 0;
    this->validLocations = NULL;
}

/* ~Maze
*
*  Parameters: none
*  Return value: none
*
*  This is the destructor for the maze class
*/
Maze::~Maze(){
    delete[] this->validLocations;
    this->validLocations = NULL;
    this->validLocationCount = 0;
}

/* getStartLocation
*
*  Parameters: void
*  Return value: none
*
*  This function returns start of maze location
*/
Location Maze::getStartLocation(void) const{
    return (this->startLocation);
}

/* isValidLocation
*
*  Parameters:
*   loc -- location object passed by reference
*  Return value: none
*
*  This function checks that loc is a valid location in the maze
*/
bool Maze::isValidLocation(const Location &loc) const{
    for(int i = 0; i < this->validLocationCount; i++){
        if(loc == this->validLocations[i]){
            return true;
        }
    }
    return false;
}

/* isEndLocation
*
*  Parameters:
*   loc -- location object passed by reference
*  Return value: none
*
*  This function checks loc to see if it is the end location of the maze
*/
bool Maze::isEndLocation(const Location &loc) const{
    return (loc == this->endLocation);
}

/* operator>>
*
*  Parameters:
*   is -- istream for values
*   m -- maze object passed by reference
*  Return value: none
*
*  This function streams a maze object in
*/
istream &operator>>(istream &is, Maze &m){
    delete[] m.validLocations;

    is >> m.validLocationCount;

    m.validLocations = new Location[m.validLocationCount];
    for(int i = 0; i < m.validLocationCount; ++i){
        is >> m.validLocations[i];
    }
    is >> m.startLocation >> m.endLocation;

    return is;
}