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

using namespace std;
//              {0,                 1,                          2,          3};
enum SortType {SelectionSortType, InsertionSortType, BubbleSortType, ShakerSortType};


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
        cout << "***Error: Conversion to long Failed. Unicode bytes detected in Data File." << endl;
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

//Results look like this
//Print 1000 SelectAve  InsertAve BubbleAve ShakerAve
//Print 2000 SelectAve  InsertAve BubbleAve ShakerAve
//Print 3000 SelectAve  InsertAve BubbleAve ShakerAve
//Print 5000 SelectAve  InsertAve BubbleAve ShakerAve
//Print 10000 SelectAve  InsertAve BubbleAve ShakerAve
//Print 20000 SelectAve  InsertAve BubbleAve ShakerAve

void runSort(vector<Person> people, SortType sortType){
    
    double startTime, endTime, totalTime;
    double average = 0;
    int numberOfRuns = 3;

    for(int i = 0; i< numberOfRuns; i++){
        startTime = getCPUTime();
        
        switch (sortType) {
            case SelectionSortType:
                //Our Code Goes here for Selection Sort
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
    cout << "is " << average << " for "<< people.size() <<  " records." << endl;
}

vector <Person> reversePeopleVector(vector<Person> people){
    vector <Person> reversePeopleVector;
    for (int j = int(people.size() - 1); j >= 0; j--){
        reversePeopleVector.push_back(people[j]);
    }
    return reversePeopleVector;
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

    startTime = getCPUTime();
    switch (sortType) {
        case SelectionSortType:
            //Our Code Goes here for Selection Sort
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
    startTime = getCPUTime();
    switch (sortType) {
        case SelectionSortType:
            //Our Code Goes here for Selection Sort
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
            //Our Code Goes here for Selection Sort
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
    cout << " for "<< people.size() <<  " records:";
    //cout << " AverageCase: " << aveCaseTime << endl;
    //cout << " BestCase: " << bestCaseTime << endl;
    //cout << " WorstCase: " << worstCaseTime << endl;
    
    
    cout << " \t" << aveCaseTime << " \t " << bestCaseTime << " \t"<< worstCaseTime << endl;
    
    
    
}


void runAllSortsForDatabaseForAveBestWorst(vector<Person> people){
    
    cout << endl << "** Running sorts for " << people.size() << " records." << endl;
    runSortAveBestWorst(people, SelectionSortType);
    runSortAveBestWorst(people, InsertionSortType);
    runSortAveBestWorst(people, BubbleSortType);
    runSortAveBestWorst(people, ShakerSortType);
}



void labTwo(){
    
    cout << endl;
    cout <<"**************************************************************"<< endl;
    cout << "  Part 1: Reading files and Printing database1.txt with " << endl;
    cout << "          birthday in YYYYMMDD format and age of the person." << endl;
    cout <<"**************************************************************"<< endl;
    
    vector <Person> peopleVectorDB1 = readFile("/Users/cj/Desktop/database1.txt");
    //printPeopleVector(peopleVectorDB1);
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
    cout <<"*****************************************************************"<< endl;
    cout << "  Part 3: Sorting Six Data Files via Four Different Algorithms in Average, Best and Worst Case." << endl;
    cout <<"*****************************************************************"<< endl;
    
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB1);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB2);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB3);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB5);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB10);
    runAllSortsForDatabaseForAveBestWorst(peopleVectorDB20);

}

int main(int argc, const char * argv[]){
    cout << "Lab 2, Parts 1 and 2 \n";
    labTwo();
    return 0;
}

