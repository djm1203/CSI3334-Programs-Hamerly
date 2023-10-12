/* CSI 3334
* Project 3 -- Tree Based Encryption
* Filename: driver-proj3.cpp
* Student name: Derek Martinez
* assignment: project 3
* due date: October 6,2023
* version: 1.0
*
* This file implements the classes BST,
* BSTNode, and encryptionTree to read and
* solve given input from a tree
*/
#include <iostream>
#include "bst-student-proj3.h"

using namespace std;

/* main
 *  Parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  Return value: 0
 *
 * The main creates a tree based on the inputs. Then read commands to either
 * remove, insert items into the tree or prints out the current state of the tree.
 * As well as encrypt or decrypt a message using the encryption tree.
 */

int main(int argc, char **argv) {
    char cmd;
    string item;
    const string *msg;
    int start;
    EncryptionTree<string> eTree;

    cin >> cmd;
    while (cmd != 'q') {
        if (cmd == 'i') { //insert
            cin >> item;
            eTree.insert(item);
        } else if (cmd == 'r') { //remove
            cin >> item;
            eTree.remove(item);
        } else if (cmd == 'e') { //encrypt
            getline(cin, item, '\'');
            getline(cin, item, '\'');
            cin.ignore();
            start = 0;
            for(int i = 0; i < item.length(); i++){
                if(item[i] == ' '){
                    cout << eTree.encrypt(item.substr(start, i - start)) << " ";
                    start = i + 1;
                }
            }
            cout << eTree.encrypt(item.substr(start, item.length() - start)) << endl;
        } else if (cmd == 'd') { //decrypt
            getline(cin, item, '\'');
            getline(cin, item, '\'');
            cin.ignore();
            start = 0;
            for(int i = 0; i < item.length(); i++){
                if(item[i] == ' '){
                    msg = eTree.decrypt(item.substr(start, i - start));
                    start = i + 1;
                    if(msg != nullptr){
                        cout << *msg << " ";
                    }else{
                        cout << "? ";
                    }
                }
            }
            msg = eTree.decrypt(item.substr(start, item.length()-start));
            if(msg == nullptr){
                cout << "?" << endl;
            }
            else{
                cout << *msg << endl;
            }
        } else if (cmd == 'p') { //print
            eTree.printPreorder();
        } else { //invalid cmd
            cmd = 'q';
        }
        cin >> cmd;
    }
    return 0;
}
