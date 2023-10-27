//Name: Alexis Martinez
//Date: 10/27/2023
//Description: Header file for class Patient

#pragma once
#include <iostream> //For ostream
#include <string>   //For string
using namespace std;

class Patient
{
private:
	int priority;
	unsigned int checkedInTime;
	string name;
	int age;
	char gender;
	unsigned int admittedTime;
	string careUnit;
	static string ER_description[5];

public:
	//CONSTRUCTOR
	Patient();

	//MUTATORS
	void setCheckedInTime(unsigned int);
	void setPriority(int);
	void setName(string);
	void setAge(int);
	void setGender(char);

	//ACCESSORS
	unsigned int getCheckedInTime() const;
	int getPriority() const;
	string getName() const;
	int getAge() const;
	char getGender() const;

	//FRIENDS
	friend bool operator <(const Patient&, const Patient&); //key in priority queue
	friend ostream& operator<<(ostream&, const Patient&);
};
