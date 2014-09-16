//
//  date.cpp
//  SueHW2E1
//
//  Created by cj on 9/16/14.
//  Copyright (c) 2014 KickinEspresso. All rights reserved.
//

#include "date.h"
#include "utility.h"

//Default Constructor
Date::Date(){
    this->year = 0;
    this->month = 0;
    this->day = 0;
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
    year = int(dateValue/10000);
    month = (dateValue/100) % 100;
    day = dateValue % 100;
}

//Deconstructor
Date::~Date(){
}

//Member Functions//
//YYYYMMDD Format
void Date::printInfo(){
    int zero = 0;
    printf("%d", year);
    if(month < 10) printf("%d", zero);
    printf("%d", month);
    if(day < 10) printf("%d", zero);
    printf("%d\n", day);
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