//
//  main.cpp
//  Lab 2 part 1 and 2
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "date.h"
#include "person.h"
#include "utility.h"

using namespace std;





//ReadFile reads database and creates the objects
vector <Person> readFile(string filename){
    vector <Person> people; //Vector of TYPE Person named 'people'
    
    ifstream infile(filename); //Open the file
    string str; //Declares a string and is used for temporary storage
    
	if (infile.is_open()){
		while (getline(infile,str, '\r')){
            string ssnString;
            string firstName;
            string lastName;
            string dateString;
            
            string token;
            stringstream stringStream(str);
            //Get SSN
            if (getline(stringStream, token, ' ')){
                ssnString = token;
            }
            
            if (getline(stringStream, token, ' ')){
                firstName = token;
            }
            
            if (getline(stringStream, token, ' ')){
                lastName = token;
            }
            
            if (getline(stringStream, token, ' ')){
                dateString = token;
            }

            //Date Object
            Date birthdayVariable(dateString); //Creates a new date object
            //Person     Person(long s, string first, string last, Date b);
            long ssn =  convertStringToLong(ssnString);
            
            Person personVariable(ssn, firstName, lastName, birthdayVariable);
            people.push_back(personVariable);
		}
		infile.close();
	}
	else{
		cout << "Unable to open file" << endl << endl;
	}
    return people;
}

void printPeopleVector(vector<Person> people){
    //Check our work by printing the information for the vector of people objects
    for(long i = 0; i < people.size(); i++){
        cout << i << ": " ;
        people[i].printInfo();
        cout << "Age: " << people[i].age() << endl << endl;
    }
}

void printAgeOfPeopleVector(vector<Person> people){
    //Check our work by printing the information for the vector of people objects
    for(long i = 0; i < people.size(); i++){
        cout << i << ": " <<  people[i].age() << endl;
    }
}

//Bubble Sort
vector <Person> bubbleSort(vector <Person> myArray){
    //Loop through
    //Compare and swap ...
    for(int loop = 1; loop <myArray.size(); loop++ ){
        for(int i = 1 ; i <myArray.size(); i++){
            if(myArray[i-1].age() > myArray[i].age()){
                //Swap
                Person temp = myArray[i];
                myArray[i] = myArray[i-1];
                myArray[i-1] = temp;
            }
        }
    }
    return myArray;
}

//Insertion Sort
vector <Person> insertionSort(vector <Person> myArray){
    for(int i = 0; i <= myArray.size(); i++ ){
        for(int j = i - 1 ; j > 0; j--){
            if(myArray[j-1].age() > myArray[j].age()){
                //Swap
                Person temp = myArray[j];
                myArray[j] = myArray[j-1];
                myArray[j-1] = temp;
            }
        }
    }
    return myArray;
}

//Selection Sort
vector <Person> selectionSort(vector <Person> myArray){
    int i, j, smallestNow;
    for(i=0; i<myArray.size()-1; i++){
        smallestNow = i;
        for(j=i+1; j<myArray.size(); j++){
            if(myArray[smallestNow].age() > myArray[j].age()) smallestNow=j;
        }
        Person temp = myArray[i];
        myArray[i] = myArray[smallestNow];
        myArray[smallestNow] = temp;
    }
    return myArray;
}

//Shaker Sort
vector <Person> shakerSort(vector <Person> myArray){
    for(int i=0; i<=myArray.size()/2; i++){
        for(int j=i; j<(myArray.size())-(i+1); j++){
            if(myArray[j].age() > myArray[j+1].age()){
                //Swap
                Person temp = myArray[j];
                myArray[j] = myArray[j+1];
                myArray[j+1] = temp;
            }
        }
        for(int j= int(myArray.size()-(2+i)); j > i; j--){
            if(myArray[j].age() < myArray[j-1].age()){
                Person temp = myArray[j];
                myArray[j] = myArray[j-1];
                myArray[j-1]=temp;
            }
        }
    }
    return myArray;
}

double getCPUTime(void) {
    struct timeval tv;
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    tv = ru.ru_utime;
    double t = (double)tv.tv_sec + (double)tv.tv_usec/1000000.0;
    tv = ru.ru_stime;
    t += (double)tv.tv_sec + (double)tv.tv_usec/1000000.0;
    return t;
}

void labTwo(){
    double startTime, endTime, totalTime;
    cout << endl;
    cout <<"***************************************************"<< endl;
    cout << "  Reading file" << endl;
    cout <<"***************************************************"<< endl;
    
    vector <Person> peopleVectorDB1 = readFile("/Users/cj/Desktop/database2.txt");
    
    printPeopleVector(peopleVectorDB1);
    
    cout << "Timing Output for Four Sort Algorithms: \n \n";
    cout << "Bubble Sort: " << endl;
    startTime = getCPUTime();
    vector <Person> bubbleSortedPeopleVector = bubbleSort(peopleVectorDB1);
    endTime = getCPUTime();
    totalTime = endTime - startTime;
    //printPeopleVector(bubbleSortedPeopleVector);
    cout << "Total time: " << totalTime << " = End time: " << endTime << " - Start time: " << startTime << endl;
    
    cout << endl;
    cout << "Insertion Sort: " << endl;
    startTime = getCPUTime();
    vector <Person> insertionSortedPeopleVector = insertionSort(peopleVectorDB1);
    endTime = getCPUTime();
    totalTime = endTime - startTime;
    //printPeopleVector(insertionSortedPeopleVector);
    cout << "Total time: " << totalTime << " = End time: " << endTime << " - Start time: " << startTime << endl;
    
    cout << endl;
    cout << "Selection Sort: " << endl;
    startTime = getCPUTime();
    vector <Person> selectionSortedPeopleVector = selectionSort(peopleVectorDB1);
    endTime = getCPUTime();
    totalTime = endTime - startTime;
    //printPeopleVector(selectionSortedPeopleVector);
    cout << "Total time: " << totalTime << " = End time: " << endTime << " - Start time: " << startTime << endl;
    
    cout << endl;
    cout << "Shaker Sort: " << endl;
    startTime = getCPUTime();
    vector <Person> shakerSortedPeopleVector = shakerSort(peopleVectorDB1);
    endTime = getCPUTime();
    totalTime = endTime - startTime;
    cout <<endl;
    printPeopleVector(shakerSortedPeopleVector);
    //printPeopleVector(shakerSortedPeopleVector);
    cout << "Total time: " << totalTime << " = End time: " << endTime << " - Start time: " << startTime << endl;
}

int main(int argc, const char * argv[]){
    cout << "Lab 2, Part 1 \n";
    labTwo();
    return 0;
}

