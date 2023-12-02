/* CSI 3334
* Project 5 -- Real-Time Batch Operating System Simulator
* Filename: driver-proj5.cpp
* Student name: Derek Martinez
* assignment: project 5
* due date: November 10,2023
* version: 1.0
*
* This file implements the classes ArrayHeap
*/

#include <iostream>
#include "arrayheap-student-proj5.h"
#include "process-proj5.h"

/* main
 *  Parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  Return value: 0
 *
 * The main takes in a user inputted number of processes,
 * places them into a high priority heap, only when
 * submission time is reached. Highest Priority process is
 * either ran if able to compolete before deadline or skips
 * it. Output clock, number of processes ran and skipped.
 */
int main(int argc, char **argv) {
    int n = 0;
    int numInputs = 0;
    int time = 0;
    int numSkip = 0;
    int numRun = 0;
    int procId = 0;
    ArrayHeap<Process> pHeap;
    Process *proc = new Process();
    Process currProc;

    cin >> n;
    cin >> *proc;
    numInputs = n;

    while (n > 0){
        while (proc->getSubmissionTime() <= time && numInputs > 0) {
            pHeap.insert(*proc);
            numInputs--;
            procId++;
            delete proc;
            proc = new Process(procId);

            if (numInputs > 0) {
                cin >> *proc;
            }
        }

        if (pHeap.getNumItems() != 0) {
            currProc = pHeap.getMinItem();
            pHeap.removeMinItem();
            n--;

            if (currProc.canComplete(time)) {
                cout << "running process id " << currProc.getId() << " at " << time << endl;
                time = currProc.run(time);
                numRun++;
            } else {
                cout << "skipping process id " << currProc.getId() << " at " << time << endl;
                numSkip++;
                time++;
            }
        } else {
            time++;
        }
    }
    delete proc;

    cout << "final clock is                 " << time << endl;
    cout << "number of processes run is     " << numRun << endl;
    cout << "number of processes skipped is " << numSkip << endl;


    return 0;
}
