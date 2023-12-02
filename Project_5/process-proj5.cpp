/* CSI 3334
* Project 5 -- Real-Time Batch Operating System Simulator
* Filename: process-proj5.cpp
* Student name: Derek Martinez
* assignment: project 5
* due date: November 10,2023
* version: 1.0
*
* This file implements the class process
*/
#include "process-proj5.h"

/* Process
*
*  Parameters: none
*  Return value: none
*
*  This is the default constructor
*/
Process::Process(int theId){
    id = theId;
    submissionTime = 0;
    deadline = 0;
    requiredTime = 0;
    information = "";
}

/* Process
*
*  Parameters:
*       currentSystemTime -- current time
*  Return value: process finish time
*
*  This function returns the time the process finishes running
*/
int Process::run(int currentSystemTime) const{
    cout << information << endl;
    return currentSystemTime + requiredTime;
}

/* canComplete
*
*  Parameters:
*       currentSystemTime -- current time
*  Return value: if the process finishes before deadline
*
*  This function says whether the process finishes before the deadline
*/
bool Process::canComplete(int currentSystemTime) const{
    return (currentSystemTime + requiredTime) <= deadline;
}

/* getId
*
*  Parameters: none
*  Return value: id of process
*
*  This function returns the id of a process
*/
int Process::getId() const{
    return id;
}

/* getSubmissionTime
*
*  Parameters: none
*  Return value: submission time of process
*
*  This function returns the submission time of a process
*/
int Process::getSubmissionTime() const{
    return submissionTime;
}

/* operator<
*
*  Parameters:
*       p -- process to compare
*  Return value: if it this process is less than the other
*
*  This function determines if the process is less than the
*  other based on deadline, requiredTime and id
*/
bool Process::operator<(Process const &p) const{
    if (deadline < p.deadline) {
        return true;
    }else if (deadline == p.deadline) {
        if(requiredTime < p.requiredTime) {
            return true;
        }else if (requiredTime == p.requiredTime) {
            if(id < p.id){
                return true;
            }
        }
    }
    return false;
}

/* operator>>
*
*  Parameters:
*       is -- istream of process class' info
*       p -- process to compare
*  Return value:
*
*  This function reads all of a process' info
*/
istream &operator>>(istream &is, Process &p){
    is >> p.submissionTime >> p.deadline >> p.requiredTime;
    getline(is >> ws, p.information);

    return is;
}