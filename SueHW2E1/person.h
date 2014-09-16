//
//  person.h
//  SueHW2E1
//
//  Created by cj on 9/11/14.
//  Copyright (c) 2014 KickinEspresso. All rights reserved.
//

#ifndef SueHW2E1_person_h
#define SueHW2E1_person_h



#include <string>
#include "date.h"

using namespace std;


//**************************
//  Class Person
//**************************
class Person {
    
private:
    string lastName;
    string firstName;
    long ssn;
    Date birthday;
    
public:
    //Constructor
    Person(long s, string first, string last, Date b);
    ~Person(); //Deconstructor
    
    //Member Functions//
    void printName();
    void printInfo(); //Print Name (first and last), SSN, Birthdate
    long age();     //Calculate the age of the person based on the birthdate
    
    //Setters and Getters
    
    
    //GETTERS//
    long getSsn();
    string getFirstName();
    string getLastName();
    Date getBirthday();
    string getFullName(string fullname);
    
    //SETTERS//
    void setSsn(long s);
    void setFirstName(string first);
    void setLastName(string last);
    void setBirthday(Date b);      //Overloaded!!
    void setBirthday(string b);    //Overloaded!!
    void setFullName(string fullname);
};

#endif
