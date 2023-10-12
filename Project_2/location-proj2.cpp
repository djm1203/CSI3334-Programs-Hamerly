/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: location-proj2.cpp
 * Student name: Derek Martinez
 * assignment: project 2
 * due date: September 22,2023
 * version: 1.0
 *
 * This file implements the location class functions
 */

#include <iostream>
#include <string>
#include "location-proj2.h"

using namespace std;

/* Location
*
*  Parameters: none
*  Return value: none
*
*  This is the default constructor for the Location class
*/
Location::Location(){
    this->word = "";
    this->indexToChange = 0;
    this->nextLetter = 'a';
    this->iterationMode = CHANGE_LETTER;
}

/* iterationBegin
*
*  Parameters: void
*  Return value: none
*
*  This function starts the iteration of iterationMode
*/
void Location::iterationBegin(void){
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
    this->nextLetter = 'a';
    if(this->word[this->indexToChange] == 'a'){
        this->nextLetter++;
    }
}

/* iterationCurrent
*
*  Parameters: none
*  Return value: location of the neighbor
*
*  This function creates a Location object to store
*  the surrounding words while using BFS
*/
Location Location::iterationCurrent(void) const{
    Location nxtWord;
    nxtWord.word = this->word;

    if(this->iterationMode == CHANGE_LETTER){
        nxtWord.word[this->indexToChange] = this->nextLetter;
    }else if(this->iterationMode == INSERT_LETTER){
        nxtWord.word.insert(this->indexToChange, 1, this->nextLetter);
    }else{
        nxtWord.word.erase(this->indexToChange, 1);
    }
    return nxtWord;
}

/* iterationAdvance
*
*  Parameters: void
*  Return value: none
*
*  This function advances the iterationMode
*/
void Location::iterationAdvance(void){
    if(this->iterationMode == DELETE_LETTER) {
        this->indexToChange++;
        if(this->indexToChange >= this->word.size()){
            this->iterationMode++;
            this->indexToChange = 0;
        }
    }else if(this->iterationMode == INSERT_LETTER){
        if(this->nextLetter != 'z'){
            this->nextLetter++;
        }else if (this->word.length() >= this->indexToChange){
            this->nextLetter = 'a';
            this->indexToChange++;
        }

        if(this->indexToChange > word.size()){
            this->iterationMode++;
            this->indexToChange = 0;
            this->nextLetter = 'a';
        }
    }else{
        if(this->nextLetter != 'z'){
            this->nextLetter++;
        }else if(this->word.length() > this->indexToChange) {
            this->nextLetter = 'a';
            this->indexToChange++;
            if(this->word[this->indexToChange] == this->nextLetter){
                this->nextLetter++;
            }
        }
        if(this->word[this->indexToChange] == this->nextLetter){
            if(this->nextLetter >= 'z'){
                this->indexToChange++;
                this->nextLetter = 'a';
                if(this->word[this->indexToChange] == 'a'){
                    this->nextLetter++;
                }
            }else{
                this->nextLetter++;
            }
        }
        if(this->indexToChange >= this->word.size()) {
            this->iterationMode++;
            this->indexToChange = 0;
            this->nextLetter = 'a';
        }
    }
}

/* iterationDone
*
*  Parameters: void
*  Return value: if the all the directions have been checked
*
*  This function returns DONE to complete the iteration
*/
bool Location::iterationDone(void) const{
    return this->iterationMode == DONE;
}

/* operator==
*
*  Parameters:
*      loc -- location compared to word
*  Return value: if the location word is the same as word
*
*  This function compares &loc to a location object for equivalence
*/
bool Location::operator==(const Location &loc) const{
    return this->word == loc.word;
}

/* &operator<<
*
*  Parameters:
*      os -- ostream for location
*      loc -- location outputted to screen
*  Return value: the ostream with the words
*
*  This function outputs the words of the location object
*/
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.word;
    return os;
}

/* &operator>>
*
*  Parameters:
*      is -- istream of location classes word
*      loc -- location streamed to the istream
*  Return value: none
*
*  This function reads the word from input
*/
istream &operator>>(istream &is, Location &loc){
    is >> loc.word;
    return is;
}

/* operator<
*
*  Parameters:
*      loc -- location object compared to word
*  Return value: none
*
*  This function compares two words to each other
*/
bool Location::operator<(const Location &loc) const{
    return this->word < loc.word;
}
