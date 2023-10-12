/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: maze-proj2.cpp
 * Student name: Derek Martinez
 * assignment: project 2
 * due date: September 22,2023
 * version: 1.0
 *
 * This file implements the maze class functions
 */

#include <iostream>
#include <set>
#include "maze-proj2.h"

using namespace std;

/* Maze
*
*  Parameters: void
*  Return value: none
*
*  This is the default constructor for the maze class
*/
Maze::Maze(void){
    this->validLocations = set<Location>();
}

/* getStartLocation
*
*  Parameters: void
*  Return value: starting location in maze
*
*  This function returns start location
*/
Location Maze::getStartLocation(void) const{
    return this->startLocation;
}

/* isValidLocation
*
*  Parameters:
*   loc -- location in maze
*  Return value: none
*
*  This function checks that loc is a valid location in the maze
*/
bool Maze::isValidLocation(const Location &loc) const{
    return this->validLocations.find(loc) != this->validLocations.end();
}

/* isEndLocation
*
*  Parameters:
*   loc -- location in maze
*  Return value: none
*
*  This function checks loc to see if it is the end location of the word
*/
bool Maze::isEndLocation(const Location &loc) const{
    return loc == this->endLocation;
}

/* operator>>
*
*  Parameters:
*   is -- istream of valid words in maze
*   m -- maze object with valid locations
*  Return value: istream
*
*  This function streams a maze object in with valid words
*/
istream &operator>>(istream &is, Maze &m){
    int size;

    Location words;
    m.validLocations.clear();
    is >> size;
    for(int i = 0; i < size; ++i){
        is >> words;
        m.validLocations.insert(words);
    }
    is >> m.startLocation >> m.endLocation;
    return is;
}