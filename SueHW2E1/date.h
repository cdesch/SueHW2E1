//
//  date.h
//  SueHW2E1
//
//  Created by cj on 9/16/14.
//  Copyright (c) 2014 KickinEspresso. All rights reserved.
//

#ifndef SueHW2E1_date_h
#define SueHW2E1_date_h


#include <string>

using namespace std;

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


#endif
