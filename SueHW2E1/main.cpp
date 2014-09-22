//
//  main.cpp
//  Lab 2 part 1 and 2
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <thread>
using namespace std;
//              {0,                 1,                          2,          3};
enum SortType {SelectionSortType, InsertionSortType, BubbleSortType, ShakerSortType};

int randomNumberUnder(unsigned long maxVal){
    return  rand() % maxVal;
}

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
        cout << "***Error: Conversion to long Failed. Unicode bytes " << endl;
        cout << "***       detected in Data File." << endl;
        cout << "***Error Reading File. Remove Unicode Bytes in Data File." << endl;
        for (int i = 0; i < myString.length(); i++){
            //cout << i << ": " << myString[i] << " ";
            //If it is not a digit, remove it
            if (!isdigit(myString[i])){
                cout << " <--  ***** Not a integer *****"<< endl;
            }
        }
        //throw  "***Error Reading File. Remove Unicode Bytes from first line";
        string newString = myString.substr(3);
        convertedNumber = atol(newString.c_str());
    }
    return convertedNumber;
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
    Person(); //Default Constructor
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
 //Default Constructor
Person::Person(){
    
}

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
    return age;
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
            //Get First Name
            if (getline(stringStream, token, ' ')){
                firstName = token;
            }
            //Get Last Name
            if (getline(stringStream, token, ' ')){
                lastName = token;
            }
            //Get Birthday
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

//ReadFile reads database and creates the objects
//There were extra characters in database2.txt and this function was required to read this file line by line
vector <Person> readFileByLine(string filename){
    vector <Person> people; //Vector of TYPE Person named 'people'
    
    ifstream infile(filename); //Open the file
    string str; //Declares a string and is used for temporary storage
    
    if (infile.is_open()){
        while (getline(infile,str)){
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
            //Get First Name
            if (getline(stringStream, token, ' ')){
                firstName = token;
            }
            //Get Last Name
            if (getline(stringStream, token, ' ')){
                lastName = token;
            }
            //Get Birthday
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
    //Check work by printing the information for the vector of people objects
    for(long i = 0; i < people.size(); i++){
        cout << i+1 << ": " ;
        people[i].printInfo();
        cout << "Age: " << people[i].age() << endl << endl;
    }
}

void printAgeOfPeopleVector(vector<Person> people){
    //Check work by printing the information for the vector of people objects
    for(long i = 0; i < people.size(); i++){
        cout << i << ": " <<  people[i].age() << endl;
    }
}
vector <Person> selectionSort(vector <Person> myArray){
    int i, j, smallestNow;
    for(i=0; i < myArray.size()-1; i++){
        smallestNow=i;
        for(j=i+1; j < myArray.size(); j++){
            if(myArray[j].age()< myArray[smallestNow].age()){
                smallestNow=j;
            }
        }
        if(smallestNow != i){
            Person temp = myArray[i];
            myArray[i] = myArray[smallestNow];
            myArray[smallestNow] = temp;
        }
    }
    return myArray;
}

/*
 //Insertion Sort
 vector <Person> insertionSort(vector <Person> myArray){
 for(int i = 1; i <= myArray.size(); i++ ){
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
 */

vector <Person> insertionSort(vector <Person> myArray){
    for(int i = 1; i < myArray.size(); i++){
        int j=i;
        while(j > 0 && myArray[j].age() < myArray[j-1].age()){
            //Swap
            Person temp = myArray[j];
            myArray[j] = myArray[j-1];
            myArray[j-1] = temp;
            j--;
        }
    }
    return myArray;
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

vector <Person> reduceVectorSize(vector <Person> people, int reduceAmount){
    
    //Check if the vector can be reduced by a certain size
    if (people.size() > reduceAmount){
        people.resize(people.size() - reduceAmount);
        people.shrink_to_fit();
        return people;
        
    }else{
        //Cannot reduce further. return the original vector
        return people;
    }
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

//Run Sorts three times and take average of the runs
void runSort(vector<Person> people, SortType sortType){
    
    double startTime, endTime, totalTime;
    double average=0.;
    int numberOfRuns = 3;
    
    for(int i = 0; i< numberOfRuns; i++){
        startTime = getCPUTime();
        switch (sortType) {
            case SelectionSortType:
                //Code Goes here for Selection Sort
                //cout << "Selection Sort: " << endl;
                selectionSort(people);
                break;
            case InsertionSortType:
                //cout << "Insertion Sort: " << endl;
                insertionSort(people);
                break;
            case BubbleSortType:
                //cout << "Bubble Sort: " << endl;
                bubbleSort(people);
                break;
            case ShakerSortType:
                //cout << "Shaker Sort: " << endl;
                shakerSort(people);
                break;
            default:
                //This gets trigger if SortType
                break;
        }
        endTime = getCPUTime();
        totalTime = endTime - startTime;
        average += totalTime;
    }
    average = average / numberOfRuns;
    
    cout << "Average Time for ";
    switch (sortType) {
        case SelectionSortType:
            cout << "Selection Sort ";
            break;
        case InsertionSortType:
            cout << "Insertion Sort ";
            break;
        case BubbleSortType:
            cout << "Bubble Sort ";
            break;
        case ShakerSortType:
            cout << "Shaker Sort ";
            break;
        default:
            //This gets trigger if SortType is out of range
            break;
    }
    //cout << "is " << average << " for "<< people.size() <<  " records." << endl;
    cout << "is " << average << endl;
}

vector <Person> reversePeopleVector(vector<Person> people){
    vector <Person> reversePeopleVector;
    for (int j = int(people.size() - 1); j >= 0; j--){
        reversePeopleVector.push_back(people[j]);
    }
    people = reversePeopleVector;
    return people;
}

void runAllSortsForDatabase(vector<Person> people){
    cout << endl << "** Running sorts for " << people.size() << " records." << endl;
    runSort(people, SelectionSortType);
    runSort(people, InsertionSortType);
    runSort(people, BubbleSortType);
    runSort(people, ShakerSortType);
}

void runSortAveBestWorst(vector<Person> people, SortType sortType){
    
    vector <Person> sortedData;
    double startTime, endTime, totalTime;
    double aveCaseTime, bestCaseTime, worstCaseTime;
    
    //Run Average Case
    //Sort the Unsorted Data
    startTime = getCPUTime();
    switch (sortType) {
        case SelectionSortType:
            //Code for Selection Sort
            //cout << "Selection Sort: " << endl;
            sortedData = selectionSort(people);
            break;
        case InsertionSortType:
            //cout << "Insertion Sort: " << endl;
            sortedData = insertionSort(people);
            break;
        case BubbleSortType:
            //cout << "Bubble Sort: " << endl;
            sortedData = bubbleSort(people);
            break;
        case ShakerSortType:
            //cout << "Shaker Sort: " << endl;
            sortedData = shakerSort(people);
            break;
        default:
            //This gets trigger if SortType
            break;
    }
    endTime = getCPUTime();
    totalTime = endTime - startTime;
    aveCaseTime = totalTime;
    
    //Best Case
    //Sort the Sorted
    startTime = getCPUTime();
    switch (sortType) {
        case SelectionSortType:
            //Code Goes here for Selection Sort
            //cout << "Selection Sort: " << endl;
            selectionSort(sortedData);
            break;
        case InsertionSortType:
            //cout << "Insertion Sort: " << endl;
            insertionSort(sortedData);
            break;
        case BubbleSortType:
            //cout << "Bubble Sort: " << endl;
            bubbleSort(sortedData);
            break;
        case ShakerSortType:
            //cout << "Shaker Sort: " << endl;
            shakerSort(sortedData);
            break;
        default:
            //This gets trigger if SortType
            break;
    }
    endTime = getCPUTime();
    totalTime = endTime - startTime;
    bestCaseTime = totalTime;
    
    //Worst Case
    //Reverse the SORTED People Vector
    vector<Person> reverseSortedPeople = reversePeopleVector(people);
    
    startTime = getCPUTime();
    switch (sortType) {
        case SelectionSortType:
            //Code Goes here for Selection Sort
            //cout << "Selection Sort: " << endl;
            sortedData = selectionSort(reverseSortedPeople);
            break;
        case InsertionSortType:
            //cout << "Insertion Sort: " << endl;
            sortedData = insertionSort(reverseSortedPeople);
            break;
        case BubbleSortType:
            //cout << "Bubble Sort: " << endl;
            sortedData = bubbleSort(reverseSortedPeople);
            break;
        case ShakerSortType:
            //cout << "Shaker Sort: " << endl;
            sortedData = shakerSort(reverseSortedPeople);
            break;
        default:
            //This gets trigger if SortType
            break;
    }
    endTime = getCPUTime();
    totalTime = endTime - startTime;
    worstCaseTime = totalTime;
    
    cout << "Average Time for ";
    switch (sortType) {
        case SelectionSortType:
            cout << "Selection Sort ";
            break;
        case InsertionSortType:
            cout << "Insertion Sort ";
            break;
        case BubbleSortType:
            cout << "Bubble Sort ";
            break;
        case ShakerSortType:
            cout << "Shaker Sort ";
            break;
        default:
            //This gets trigger if SortType is out of range
            break;
    }
    //cout << " for "<< people.size() <<  " records:"<< endl;
    cout << endl;
    cout << " Sort unsorted data (Ave): " << aveCaseTime << endl;
    cout << " Sort sorted data (Best): " << bestCaseTime << endl;
    cout << " Sort sorted data to opposite order (Worse): " << worstCaseTime << endl;
    
    //cout << " \t \t " << aveCaseTime << " \t " << bestCaseTime << " \t"<< worstCaseTime << endl;
}


double runTimedSort(vector<Person> people, SortType sortType){
    double startTime, endTime, totalTime;

    //Run Average Case
    //Sort the Unsorted Data
    startTime = getCPUTime();
    switch (sortType) {
        case SelectionSortType:
            //Code for Selection Sort
            //cout << "Selection Sort: " << endl;
            selectionSort(people);
            break;
        case InsertionSortType:
            //cout << "Insertion Sort: " << endl;
            insertionSort(people);
            break;
        case BubbleSortType:
            //cout << "Bubble Sort: " << endl;
            bubbleSort(people);
            break;
        case ShakerSortType:
            //cout << "Shaker Sort: " << endl;
            shakerSort(people);
            break;
        default:
            //This gets trigger if SortType
            break;
    }
    endTime = getCPUTime();
    totalTime = endTime - startTime;
    return totalTime;
}

void runAllSortsForDatabaseForAveBestWorst(vector<Person> people){
    
    cout << endl << "** Running sorts for " << people.size() << " records." << endl;
    runSortAveBestWorst(people, SelectionSortType);
    runSortAveBestWorst(people, InsertionSortType);
    runSortAveBestWorst(people, BubbleSortType);
    runSortAveBestWorst(people, ShakerSortType);
}

vector <double> runGranularSorts(vector <Person> people, SortType sortType, int reduceAmount){
    vector<double> sizes;
    vector<double> results;
    double runTime;
    
    while (people.size() > reduceAmount +1){
        
        runTime = runTimedSort(people, sortType);
        sizes.push_back(people.size());
        results.push_back(runTime);
        people = reduceVectorSize(people, reduceAmount);
        
    }
    
    
    return results;
    
}

void printVectorSizes(vector <Person> people,  int reduceAmount){
    
    vector<double> sizes;
    while (people.size() > reduceAmount +1){
        sizes.push_back(people.size());
        people = reduceVectorSize(people, reduceAmount);
    }

    for (int i = (int)sizes.size() - 1; i > 0 ; i--){
        cout << sizes[i] << "\t";
    }
    cout << endl;
}


void printSortName(SortType sortType){
    
    switch (sortType) {
        case SelectionSortType:
            cout << "Selection Sort ";
            break;
        case InsertionSortType:
            cout << "Insertion Sort ";
            break;
        case BubbleSortType:
            cout << "Bubble Sort ";
            break;
        case ShakerSortType:
            cout << "Shaker Sort ";
            break;
        default:
            //This gets trigger if SortType is out of range
            break;
    }
    cout << endl;
    
}

void printResults(vector<double> results){
    
    //Print Results
    for (int i = (int)results.size() - 1; i > 0; i--){
        cout << results[i] << "\t";
    }
    cout << endl;
}

void runAllCasesGranular(vector<Person> people, SortType sortType){
    
    
    int reduceAmount = 500;

    //Run Ave Case

    vector <double> aveCaseResults = runGranularSorts(people, sortType, reduceAmount);
    //Run Best Case
    vector<Person>bestCase = selectionSort(people);
    vector <double> bestCaseResults = runGranularSorts(people, sortType, reduceAmount);

    //run Worst Case
    vector<Person>worstCase = reversePeopleVector(bestCase);
    vector <double> worstCaseResults = runGranularSorts(worstCase, sortType, reduceAmount);
    
    printSortName(sortType);
    printVectorSizes(people, reduceAmount);
    printResults(aveCaseResults);
    printResults(bestCaseResults);
    printResults(worstCaseResults);

}

void runAllSortTypeGranular(vector<Person> people, bool isMultiThreaded){
    //Should we run as multiThreaded?
    if(isMultiThreaded){
        //Multi threaded
        thread selectionThread(runAllCasesGranular, people, SelectionSortType);
        thread insertionThread(runAllCasesGranular, people, InsertionSortType);
        thread bubbleThread(runAllCasesGranular, people, BubbleSortType);
        thread shakerThread(runAllCasesGranular, people, ShakerSortType);
        
        //Wait until all threads finish
        selectionThread.join();
        insertionThread.join();
        bubbleThread.join();
        shakerThread.join();
    }else{
        //Single Threaded
        runAllCasesGranular(people, SelectionSortType);
        runAllCasesGranular(people, InsertionSortType);
        runAllCasesGranular(people, BubbleSortType);
        runAllCasesGranular(people, ShakerSortType);

    }
}



void runGranularAlgoDebug(){

    //Load Largest DB
    vector <Person> peopleVectorDB20 = readFile("/Users/cj/Desktop/database20.txt");
    
    bool runMultiThreaded = true;
    runAllSortTypeGranular(peopleVectorDB20, runMultiThreaded);
}

void printSorted(vector<Person> people){
    for (int i = 0; i < people.size(); i++){
        cout << people[i].age() << endl;
    }
}

void testSort(){
    vector <Person> peopleVectorDB1 = readFile("/Users/cj/Desktop/database1.txt");
    vector <Person> people = selectionSort(peopleVectorDB1);
    printSorted(people);
    people  = reversePeopleVector(people);
    cout << "reverse" << endl;
    
    printSorted(people);
}

void labTwo(){
    cout << endl;
    cout <<"**************************************************************"<< endl;
    cout << "  Part 1: Reading files and Printing database1.txt with " << endl;
    cout << "          birthday in YYYYMMDD format and age of the person." << endl;
    cout <<"**************************************************************"<< endl;
    
    vector <Person> peopleVectorDB1 = readFile("/Users/cj/Desktop/database1.txt");
    printPeopleVector(peopleVectorDB1);
    vector <Person> peopleVectorDB2 = readFileByLine("/Users/cj/Desktop/database2.txt");
    vector <Person> peopleVectorDB3 = readFile("/Users/cj/Desktop/database3.txt");
    vector <Person> peopleVectorDB5 = readFile("/Users/cj/Desktop/database5.txt");
    vector <Person> peopleVectorDB10 = readFile("/Users/cj/Desktop/database10.txt");
    vector <Person> peopleVectorDB20 = readFile("/Users/cj/Desktop/database20.txt");
    
    cout << endl;
    cout <<"*****************************************************************"<< endl;
    cout << "  Part 2: Sorting Six Data Files via Four Different Algorithms." << endl;
    cout <<"*****************************************************************"<< endl;
    
    runAllSortsForDatabase(peopleVectorDB1);
    runAllSortsForDatabase(peopleVectorDB2);
    runAllSortsForDatabase(peopleVectorDB3);
    runAllSortsForDatabase(peopleVectorDB5);
    runAllSortsForDatabase(peopleVectorDB10);
    runAllSortsForDatabase(peopleVectorDB20);
    
    cout << endl;
    cout << "*****************************************************************"<< endl;
    cout << "                       Extra Credit" << endl;
    cout << "Part 3: Sorting Six Data Files via Four Different Algorithms for" << endl;
    cout << "        Sort Unsorted Data (Average), Sort Sorted Data (Best)" << endl;
    cout << "        and Sort Unsorted Opposite Date (Worst) Cases." << endl;
    cout << "*****************************************************************"<< endl;
    
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB1);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB2);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB3);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB5);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB10);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB20);
    
}

int main(int argc, const char * argv[]){
    cout << "Lab 2, Parts 1, 2, and Extra Credit \n";
    //labTwo();
    
//    runGranularAlgoDebug();
    testSort();
    return 0;
}

