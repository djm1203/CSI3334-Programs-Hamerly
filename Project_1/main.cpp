/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: main.cpp
 * Student name: Derek Martinez
 * assignment: project 1
 * due date: September 8,2023
 * version: 1.0
 *
 * This file implements the classes to create and solve a maze
 */
#include <iostream>
#include "maze-proj1.h"
#include "stack-proj1.h"

/* main
 *  Parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  Return value: 0
 *
 * This file implements the maze, stack, and location classes
 * in order to read in a user inputted maze and uses DFS
 * to search for the end of the maze by starting the iterations.
 */
using namespace std;
int main(int argc, char **argv) {
    //variables
    Maze userM;
    Location start, next;
    LocationStack stack;
    bool endFound = false;

    //read maze
    cin >> userM;

    //get starting loc and begin iteration
    start = userM.getStartLocation();
    start.iterationBegin();
    stack.push(start);

    //Maze solving
    while(!endFound && !userM.isEndLocation(stack.getTop())){
        //get first location
        start = stack.getTop();
        stack.pop();
        //if not end of maze
        if(!start.iterationDone()){
            next = start.iterationCurrent();
            start.iterationAdvance();
            next.iterationBegin();
            stack.push(start);
            if(!stack.isOn(next) && userM.isValidLocation(next)){
                stack.push(next);
            }
        }else if(stack.isEmpty()){
            endFound = true;
        }
    }
    if(endFound){
        cout << "No solution" << endl;
    }else{
        cout << "Solution found\n" << stack;
    }
    return 0;
}
