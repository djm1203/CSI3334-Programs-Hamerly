/* CSI 3334
* Project 0 -- Undo Redo
* Filename: main.cpp
* Student name: Derek Martinez
* Date: August 24, 2023
* version: 1.0
*
* In this file, we are given a number of cmd lines, and if they
* do not adhere to a limit of 1-1000 we terminate the program,
* otherwise we read the command given (t, u, r) which also checks
* for validity, if it works then we complete the action of each cmd
* t = text, u = undo, r = redo. If they use u or r without any txt
* a error prompt is outputted. Finally, when finished the typing and
* undo stack is printed to the screen after being reversed.
*/
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

const int MIN_CMDS = 1;
const int MAX_CMDS = 1000;
const int MAX_WORD_LENGTH = 10;

/* validLength
*
*  This function checks the int num passed by value,
*  this check is verifying that the number is between
*  1-1000, using the const global variables MIN_CMDS and MAX_CMDS
*  and throws a boolean response based on the outcome
*
*  Parameters:
*     num -- number of commands expected
 *
*  return value: returns if the num value is between 1-1000
*/
bool validLength(int num){
    return (num >= MIN_CMDS && num <= MAX_CMDS);
}

/* validCmd
*
*  This function checks the char comparing it to the valid cmds of
*  t, u, r, then throws a boolean response based on the outcome
*
*  Parameters:
*     cmd -- single character command
*
*  return value: returns if the character cmd if it is a
*  acceptable command
*/
bool validCmd(char cmd){
    return (cmd == 't' || cmd == 'u' || cmd == 'r');
}

/* validWord
*
*  This function checks the string passed for validity by
*  checking the length and that it's a letter A-Z, and
*  throws a boolean case depending on the outcome
*
*  Parameters:
*     text -- reference to orignal string
*
*  return value: returns if the string text fits the criteria
*  of correct length and A-Z
*/
bool validWord(const string &text){
    bool valid = true;
    if(text.length() > MAX_WORD_LENGTH){
        valid = false;
    }
    for(int i = 0; i < text.length(); i++){
        if(!isalpha(text.at(i))){
            valid = false;
        }
    }
    return valid;
}

/* fixOrder
*
*  This function pulls out the objects in original stack, which is passed by pointer
*  and reverses them in the tmp, then sets *o = to tmp to return the value
*
*  Parameters:
*      o -- is a pointer to the original stack
*
*  return value: no return, only reverses the order of original stack
*
*/
void fixOrder(stack<string> *o){
    stack<string> tmp;
    while(!o->empty()){
        tmp.push(o->top());
        o->pop();
    }
    *o = tmp;
}

/* main
*
*  reads the number of text from the first line and validates it,
*  if the validation fails then cassert terminates the program.
*  Otherwise, it reads the command given for the program,
*  if it is 't' then it checks the following word and places it
*  in the typing stack. If 'u' then it places the previous word in
*  the undo stack, and before it prints it the stack is reversed.
*
*  Parameters:
*      argc -- the number of arguments from the command line
*      argv -- the command line argument values
*
*  return value: 0 (indicating a successful run)
*
*/
int main(int argc, char **argv) {
// these are the two stacks used to store the typed words and the undone
// words
    stack<string> typing, undo;

//Variables
    int numCmd;
    int count = 1;
    char cmd;
    string text;

//check for valid input
    cin >> numCmd;
    assert(validLength(numCmd));

//if valid then start typing
    while(count <= numCmd){
        cin >> cmd;
        assert(validCmd(cmd));
        //check for cmd type then proceed
        if(cmd == 't'){
            cin >> text;
            assert(validWord(text));
            typing.push(text);
        }else if(cmd == 'u'){
            if(typing.empty()){
                cout << "nothing to undo on command " << count << endl;
            }else{
                undo.push(typing.top());
                typing.pop();
            }
        }else if(cmd == 'r'){
            if(undo.empty()){
                cout << "nothing to redo on command " << count << endl;
            }else{
                typing.push(undo.top());
                undo.pop();
            }
        }
        count++;
    }

    //reverse order of stacks
    fixOrder(&typing);
    fixOrder(&undo);

    //printing out stacks
    while(!typing.empty()){
        cout << typing.top();
        typing.pop();
        if(!typing.empty()){
            cout << " ";
        }
    }
    cout << endl;
    while(!undo.empty()){
        cout << undo.top();
        undo.pop();
        if(!undo.empty()){
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}
