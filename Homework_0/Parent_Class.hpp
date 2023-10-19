//
// Created by User on 8/29/2023.
//

#ifndef HOMEWORK_0_PARENT_CLASS_HPP
#define HOMEWORK_0_PARENT_CLASS_HPP

#include <iostream>

using namespace std;

class Person {
protected:
    string name;
    string phoneNumber;
};

class Employee:: public Person {
private:
    int employeeNumber;
};
class Student:: public Person {
private:
    int studentID;
};


#endif //HOMEWORK_0_PARENT_CLASS_HPP
