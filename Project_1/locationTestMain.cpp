/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: locationTestMain.cpp
 * Student name: Derek Martinez
 * assignment: project 1
 * due date: September 1,2023
 * version: 1.0
*/

#include <iostream>
#include <sstream>
#include "location-proj1.h"

using namespace std;

int main(){
    //Default constructor test
    Location loc;

    cout << loc << endl;
    loc.iterationBegin();
    while(!loc.iterationDone()){
        Location neighLoc = loc.iterationCurrent();
        cout << neighLoc << endl;
        loc.iterationAdvance();
    }
    cout << endl;

    //Second test from different location
    Location secLoc;
    string location = "2 2";
    stringstream inSS(location);

    inSS >> secLoc;

    cout << secLoc << endl;
    secLoc.iterationBegin();
    while(!secLoc.iterationDone()){
        Location nextLoc = secLoc.iterationCurrent();
        cout << nextLoc << endl;
        secLoc.iterationAdvance();
    }
    cout << endl;

    //Final test from larger maze
    Location thrLoc;
    string othrLoc = "10 10";
    stringstream ss(othrLoc);

    ss >> thrLoc;

    cout << thrLoc << endl;
    thrLoc.iterationBegin();
    while(!thrLoc.iterationDone()){
        Location nextLoc = thrLoc.iterationCurrent();
        cout << nextLoc << endl;
        thrLoc.iterationAdvance();
    }
    return 0;
}
/*
 * Test Mazes
 * 12
 * 0 1
 * 2 1
 * 3 1
 * 4 1
 * 2 2
 * 3 2
 * 4 2
 * 1 1
 * 2 3
 * 2 4
 * 2 5
 * 3 3
 * 1 1
 * 3 3
 *
 *
 * 2
 * 0 1
 * 2 2
 * 0 1
 * 2 2
 *
 *
 * 5
 * 0 0
 * 2 2
 * 1 2
 * 0 2
 * 2 2
 * 0 0
 *
 *
 * 3
 * 0 1
 * 0 0
 * 0 2
 * 0 0
 * 0 2
 *
 *
 * 3
 * 0 1
 * 2 0
 * 0 1
 * 2 0
 *
 *
 * 2
 * 1 1
 * 1 2
 * 1 1
 * 1 2
 *
 *
 * 8
 * 0 1
 * 1 1
 * 2 1
 * 3 1
 * 3 3
 * 1 2
 * 0 3
 * 1 3
 * 0 1
 * 3 3
 *
 *
 * 6
 * 0 1
 * 1 1
 * 2 1
 * 1 2
 * 0 3
 * 1 1
 * 0 3
 *
 *
 * 12
 * 0 3
 * 0 4
 * 0 5
 * 1 2
 * 1 3
 * 1 5
 * 2 1
 * 2 3
 * 2 4
 * 3 1
 * 3 2
 * 3 3
 * 0 5
 * 3 2
 *
 *
 * 10
 * 0 1
 * 0 2
 * 0 3
 * 0 0
 * 1 1
 * 1 3
 * 2 0
 * 2 1
 * 2 2
 * 3 1
 * 0 0
 * 1 3
 */