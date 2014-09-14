//
//  main.cpp
//  Lab 2 part 1
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;


//This function converts a string to an integer
//It returns a variable of type int
int converStringToInt(string myString){
    //atoi() isn't something you would normally know about it
    //Documentation link http://www.cplusplus.com/reference/cstdlib/atoi/
    return atoi(myString.c_str());
}
//This function converts a string to an long
//It returns a variable of type long
long convertStringToLong(string myString){
    //Documentation Link http://www.cplusplus.com/reference/cstdlib/atol/
    return atol(myString.c_str());
}

class Date {
    
private:
    int year;
    int month;
    int day;
    
public:
    //Constructor
    Date(); //Default Constructor
    Date(int y, int m, int d); //This is the constructor
    Date(string d); //Overloaded Constructor with accepting long date format
    //Deconstructor
    ~Date();
    
    //Member functions//
    void printInfo();
    
    //GETTERS//
    int getYear();
    int getMonth();
    int getDay();
    
    //SETTERS//
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
};

//Default Constructor
Date::Date(){
    this->year =  0;
    this->month =  0;
    this->day =  0;
}

//Constructor with params
Date::Date(int y, int m, int d){
    year = y;
    month = m;
    day = d;
}

Date::Date(string d){
    
    //Change from string to a long
    long dateValue = convertStringToLong(d);
    
    //break the dateValue into Year Month Day
    int year = dateValue/10000;
    int month = (dateValue/100) % 100;
    int day = dateValue % 100;
    
    cout << "Year " << year << " " << " Month ";
    if (month < 10) cout << "0" << month << "Day ";
    if (day < 10) cout << "0" << day << endl;
    
}

//Deconstructor
Date::~Date(){
}

//Member Functions//
void Date::printInfo(){
    int zero = 0;
    printf("Year: %d \n", year);
    if(month < 10) printf("%d \n", zero);
    printf("Month: %d \n", month);
    if(day < 10) printf("%d \n, zero");
    printf("Day: %d \n", day);
}

//GETTERS//
int Date::getYear(){
    return year;
}
int Date::getMonth(){
    return month;
}
int Date::getDay(){
    return day;
}

//SETTERS//
void Date::setYear(int y){
    year = y;
}
void Date::setMonth(int m){
    month = m;
}
void Date::setDay(int d){
    day = d;
}



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
    
    //Setters
    //TODO Set/Get: lastName
    //TODO Set/Get: firstName
    //TODO Set/Get: ssn
    //TODO Set/Get: Date
    //TODO setFullName(string name)
    
    //Getters are after this
    //TODO getFullName()
    //GETTERS//
    string getSsn();
    string getFirstName;
    string getLastName();
    string getBirthday();
    string setFullName(string fullname);
    
    //SETTERS//
    
    void setSsn(string s);
    void setFirstName(string first);
    void setLastName(string last);
    void setBirthday(string b);
    void setFullName(string fullname);
    
};

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

//TODO void Person::printInfo(){}
void Person::printInfo(int i){
    person[i].printInfo();
}

long Person::age(){
    //This function computes the age to the nearest year.
    //int age = 2014 - year;
    //Hint: birthday.getYear();
    return 0; //Implement
}

//TODO:Setters Implementation

//TODO:Getters Implementation
//Getters//
string Person::getSsn(){
    return ssn;
}
string Person::getFirstName(){
    return first;
}
string Person::getLastName(){
    return last;
}
string Person::getBirthday(){
    return birthday;
}

//Setters//
void Person::setSsn(string s){
    ssn = s;
}
void Person::setFirstName(string first){
    firstName = first;
}
void Person::setLastName(string last){
    lastName = last;
}
void Person::setBirthday(birthday){
    birthday=b;
}

//Notes:
//I know I need to read in the file and get the YYYYMMDD string and then break it up into integers year=YYYY, month=MM, and day=DD
//Need to read file and also need to modify this code, I think

//ReadFile reads database and creates the objects


vector <Person> readFile(string filename){
    vector <Person> people;
    
    //Read each line, create object, add to people Vector  - Loop
    //use .push_back(MYOBJECT) on people Vector EX: people.push_back(MYOBJECT)
    //HINT: From Lab1E4 - instead of creating a book object, you will create a Person Object.... instead of a PersonStruct Object, you will create a date object.
    
    return people;
}

void labTwo(){
    cout << endl;
    cout <<"***************************************************"<< endl;
    cout << "  Reading file" << endl;
    cout <<"***************************************************"<< endl;
    vector <Person> people = readFile("/Users/susanchang/Desktop/database1.txt");
}

int main(int argc, const char * argv[]){
    cout << "Lab 2, Part 1 \n";
    labTwo();
    return 0;
}

