/* CSI 3334
* Project 2 -- Word Melt Shortest-Path Solver
* Filename: driver-proj2.cpp
* Student name: Derek Martinez
* assignment: project 2
* due date: September 22,2023
* version: 1.0
*
* This file implements the classes location and maze
* to create and solve a word melt.
*/

#include <iostream>
#include <map>
#include <stack>
#include "location-proj2.h"
#include "maze-proj2.h"
#include "arrayqueue-student-proj2.h"

using namespace std;

/* main
 *  Parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  Return value: 0
 *
 * This main solves the shortest path of a word melt using Breadth First Search.
 * It takes an input of valid words and begins iterating through all words in
 * the maze set, keeping track of the previous word in the solution path. Once
 * the iteration is complete it prints out the solution path from beginning
 * to end.
 */

int main(int argc, char **argv) {
    //Variables
    Maze userM;
    Location currWord, finalWord;
    ArrayQueue<Location> wordQueue;
    stack<Location> solPath;
    map<Location, Location> locationMap, pathMap;
    bool done = false;

    cin >> userM;

    currWord = userM.getStartLocation();
    wordQueue.add(currWord);
    locationMap[currWord] = currWord;

    if(userM.isEndLocation(wordQueue.getFront())){
        done = true;
        finalWord = currWord;
    }

    while(!done && wordQueue.getLength() > 0){
        currWord = wordQueue.getFront();
        currWord.iterationBegin();
        wordQueue.remove();

        while(!currWord.iterationDone()){
            Location neighbor = currWord.iterationCurrent();
            if(userM.isEndLocation(neighbor)){
                locationMap[neighbor] = currWord;
                finalWord = neighbor;
                done = true;
            }else if(userM.isValidLocation(neighbor) &&
                    (locationMap.find(neighbor) == locationMap.end())){
                locationMap[neighbor] = currWord;
                wordQueue.add(neighbor);
            }
            currWord.iterationAdvance();
        }
    }

    if(done){
        cout << "Solution found" << endl;

        while(!(finalWord == userM.getStartLocation())){
            solPath.push(finalWord);
            finalWord = locationMap[finalWord];
        }
        solPath.push(finalWord);

        while(!solPath.empty()){
            cout << solPath.top() << endl;
            solPath.pop();
        }
    }else{
        cout << "No solution" << endl;
    }

    return 0;
}
