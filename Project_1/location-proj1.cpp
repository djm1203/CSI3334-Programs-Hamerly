/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: location-proj1.cpp
 * Student name: Derek Martinez
 * assignment: project 1
 * due date: September 8,2023
 * version: 1.0
 *
 * This file contains the code for the Location class.
 */
#include <iostream>
#include "location-proj1.h"

using namespace std;

/* Location
*
*  Parameters: none
*  Return value: none
*
*  This is the default constructor for the Location class
*/
Location::Location(){
    this->row = 0;
    this->col = 0;
    this->nextDirection = RIGHT;
}

/* iterationBegin
*
*  Parameters: none
*  Return value: none
*
*  This function starts the iteration of nextDirection
*/
void Location::iterationBegin(){
    this->nextDirection = RIGHT;
}

/* iterationCurrent
*
*  Parameters: none
*  Return value: location of the neighbor location object
*
*  This function creates a location object to store the
*  neighbors location
*/
Location Location::iterationCurrent() const{
    Location nextLoc;
    nextLoc.row = this->row;
    nextLoc.col = this->col;

    if(this->nextDirection == RIGHT){
        nextLoc.col++;
    }else if(this->nextDirection == DOWN){
        nextLoc.row++;
    }else if(this->nextDirection == LEFT){
        nextLoc.col--;
    }else{
        nextLoc.row--;
    }

    return nextLoc;
}

/* iterationAdvance
*
*  Parameters: none
*  Return value: none
*
*  This function advances the nextDirection
*/
void Location::iterationAdvance(){
    this->nextDirection++;
}

/* iterationDone
*
*  Parameters: none
*  Return value: if the all the directions have been checked
*
*  This function returns DONE to complete the iteration
*/
bool Location::iterationDone() const{
    return (this->nextDirection == DONE);
}

/* operator==
*
*  Parameters:
*      loc-- the location object passed by reference
*  Return value: returns a boolean value
*
*  This function compares &loc to a location object for equivalence
*/
bool Location::operator==(const Location &loc) const{
    return (this->row == loc.row && this->col == loc.col);
}

/* &operator<<
*
*  Parameters:
*      os-- a reference to an ostream
*      loc-- location object that is put in ostream
*  Return value: the ostream with the row and columns
*
*  This function outputs the row and column of the Location object
*/
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.row << ' ' << loc.col;
    return os;
}

/* &operator>>
*
*  Parameters:
*      is-- reference to istream
*      loc-- reference to the location object
*  Return value: the istream with the row and columns
*
*  This function read the row and column from an input.
*/
istream &operator>>(istream &is, Location &loc){
    is >> loc.row >> loc.col;
    return is;
}