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
    
    //cout << "Year " << year << " " << " Month ";
    //if (month < 10) cout << "0" << month << "Day ";
    //if (day < 10) cout << "0" << day << endl;
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
    
    //Setters
    //TODO Set/Get: lastName
    //TODO Set/Get: firstName
    //TODO Set/Get: ssn
    //TODO Set/Get: Date
    //TODO setFullName(string name)
    
    //Getters are after this
    //TODO getFullName()
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

//TODO void Person::printInfo(){}
void Person::printInfo(){
    printf("SSN: %ld \n", ssn);
    printf("First Name: %s \n", firstName.c_str());
    printf("Last Name: %s \n", lastName.c_str());
    printf("Birthdate (YYYYMMDD): ");
    birthday.printInfo();
    //Birthdate (YYYYMMDD): 20140914
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


//Notes:
//I know I need to read in the file and get the YYYYMMDD string and then break it up into integers year=YYYY, month=MM, and day=DD
//Need to read file and also need to modify this code, I think



//ReadFile reads database and creates the objects
vector <Person> readFile(string filename){
    vector <Person> people; //Vector of TYPE Person named 'people'
    //Read each line, create object, add to people Vector  - Loop
    //use .push_back(MYOBJECT) on people Vector EX: people.push_back(MYOBJECT)
    //HINT: From Lab1E4 - instead of creating a book object, you will create a Person Object.... instead of a PersonStruct Object, you will create a date object.
    
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
            long ssn = convertStringToLong(ssnString);
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



//TODO: change 'vector <int>' to 'vector <Person>' because we are sorting people.
//TODO: When comparing people, call the .age()  -- Ex: myArray[i].age();  //Only during comparison
vector <int> bubbleSort(vector <int> myArray){
    //Loop through
    //Compare what ? if larger : swap ...
    for(int loop = 1; loop <myArray.size(); loop++ ){
        for(int i = 1 ; i <myArray.size(); i++){
            
            if(myArray[i-1] > myArray[i]){
                //Swap
                int temp = myArray[i];
                myArray[i] = myArray[i-1];
                myArray[i-1] = temp;
            }
        }
    }
    return myArray;
}

vector <int> insertionSort(vector <int> myArray){
    for(int i = 0; i <= myArray.size(); i++ ){
        for(int j = i - 1 ; j > 0; j--){
            if(myArray[j-1] > myArray[j]){
                //Swap
                int temp = myArray[j];
                myArray[j] = myArray[j-1];
                myArray[j-1] = temp;
            }
        }
    }
    return myArray;
}

vector <int> selectionSort(vector <int> myArray){
    int i, j, smallestNow;
    for(i=0; i<myArray.size()-1; i++){
        smallestNow = i;
        for(j=i+1; j<myArray.size(); j++){
            if(myArray[smallestNow] > myArray[j]) smallestNow=j;
        }
        int temp = myArray[i];
        myArray[i] = myArray[smallestNow];
        myArray[smallestNow] = temp;
    }
    return myArray;
}

vector <int> shakerSort(vector <int> myArray){
    for(int i=0; i<=myArray.size()/2; i++){
        for(int j=i; j<(myArray.size())-(i+1); j++){
            if(myArray[j] > myArray[j+1]){
                //Swap
                int temp = myArray[j];
                myArray[j] = myArray[j+1];
                myArray[j+1] = temp;
            }
        }
        for(int j= int(myArray.size()-(2+i)); j > i; j--){
            if(myArray[j] < myArray[j-1]){
                int temp = myArray[j];
                myArray[j] = myArray[j-1];
                myArray[j-1]=temp;
            }
        }
    }
    return myArray;
}

void labTwo(){
    cout << endl;
    cout <<"***************************************************"<< endl;
    cout << "  Reading file" << endl;
    cout <<"***************************************************"<< endl;
    vector <Person> peopleVectorDB1 = readFile("/Users/cj/Desktop/database1.txt");
    
    printPeopleVector(peopleVectorDB1);
    
    //Timer Start
    //vector <Person> bubbleSortedPeopleVector = bubbleSort(peopleVectorDB1);
    //Timer Stop
    //printPeopleVector(bubbleSortedPeopleVector);
    //Print timer Results
    
    
    //vector <Person> selectionSortedPeopleVector = selectionSort(peopleVectorDB1);
    //printPeopleVector(selectionSortedPeopleVector);
    
    
    //printAgeOfPeopleVector(peopleVectorDB1);
    
    
}


//Test Prep List
// 1 sort of the 4 - comparison sort analysis.
// variable scope
// function based question (parameters)
// Class based question
//

int main(int argc, const char * argv[]){
    cout << "Lab 2, Part 1 \n";
    labTwo();
    return 0;
}

