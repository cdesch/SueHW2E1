//
//  person.cpp
//  SueHW2E1
//
//  Created by cj on 9/11/14.
//  Copyright (c) 2014 KickinEspresso. All rights reserved.
//

#include "person.h"


//Constructor with params
Person::Person(long s, string first, string last, Date b){
    ssn = s;
    firstName = first;
    lastName = last;
    birthday = b;
}

//Deconstructor
Person::~Person(){
}

//Member Functions//
//Prints full name
void Person::printName(){
    printf("%s %s \n", firstName.c_str(), lastName.c_str());
}

void Person::printInfo(){
    printf("SSN: %ld \n", ssn);
    printf("First Name: %s \n", firstName.c_str());
    printf("Last Name: %s \n", lastName.c_str());
    printf("Birthdate (YYYYMMDD): ");
    birthday.printInfo();  //Birthdate (YYYYMMDD): 20140914
}

long Person::age(){
    //This function computes the age to the nearest year.
    int age;
    age = 2014 - int(birthday.getYear());
    return age; //Implement
}

//Getters//
long Person::getSsn(){
    return ssn; //Type of long
}
string Person::getFirstName(){
    return firstName;
}
string Person::getLastName(){
    return lastName;
}
Date Person::getBirthday(){
    return birthday;
}

//Setters//
void Person::setSsn(long s){
    ssn = s;
}
void Person::setFirstName(string first){
    firstName = first;
}
void Person::setLastName(string last){
    lastName = last;
}

//Overloading -- two different means to the same end.
void Person::setBirthday(Date b){
    birthday = b;
}
void Person::setBirthday(string b){
    birthday = Date(b);
}