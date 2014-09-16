//
//  utility.cpp
//  SueHW2E1
//
//  Created by cj on 9/16/14.
//  Copyright (c) 2014 KickinEspresso. All rights reserved.
//

#include "utility.h"


//This function converts a string to an integer
//It returns a variable of type int
int converStringToInt(string myString){
    //atoi() isn't something you would normally know about it
    //Documentation link http://www.cplusplus.com/reference/cstdlib/atoi/
    return atoi(myString.c_str());
}
//This function converts a string to an long
//It returns a variable of type long
//This function assumes that the string being converted is NOT a zero!!
long convertStringToLong(string myString){
    //Documentation Link http://www.cplusplus.com/reference/cstdlib/atol/
    long convertedNumber;
    convertedNumber = atol(myString.c_str());
    //Check if conversion failed
    if (convertedNumber == 0){
        cout << "***Error: Conversion to long Failed. BOM Unicode bytes detected. " << endl;
        cout << "***Remove Bytes!! " << endl;
        cout << "***Error Reading File. Remove Unicode Bytes from first line" << endl;
        for (int i = 0; i < myString.length(); i++){
            cout << i << ": " << myString[i] << " ";
            //If it is not a digit, remove it
            if (!isdigit(myString[i])){
                cout << " <--  ***** Not a integer *****" ;
            }
            cout << endl;
        }
        throw  "***Error Reading File. Remove Unicode Bytes from first line";
        string newString = myString.substr(3);
        convertedNumber = atol(newString.c_str());
    }
    return convertedNumber;
}
