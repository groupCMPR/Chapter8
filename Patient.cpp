//Name: Alexis Martinez & Vivian Huynh
//Date: 10/27/2023
//Description: cpp file for class Patient

#include "Patient.h"
string Patient::ER_description[5] = { "Stable, with no resources anticipated or prescriptions", "Stable, with only one type of resource anticipated " ,"Stable, with multiple types of resources needed to investigate or treat", "High risk of deterioration, or signs of a time-critical problem", "Immediate, life-saving intervention required without delay" };

//Precondition : N/A
//Postcondition: Initalize the private members
Patient::Patient()
{
	checkedInTime;
	priority = 0;
	name = "unknown";
	age = 0;
	gender = 'u';
}

//--------------------------------------------------------------------
// Mutators Section
//--------------------------------------------------------------------
//Precondition : Passing in current time
//Postcondition: Private member checkedInTime is changed
void Patient::setCheckedInTime(unsigned int t)
{
	this->checkedInTime = t;
}
//Precondition : Passing in integer values 1...5
//Postcondition: Private member priority is changed
void Patient::setPriority(int priority)
{
	this->priority = priority;
}
//Precondition : Passing in string with spaces
//Postcondition: Private member name is changed
void Patient::setName(string name)
{
	this->name = name;
}
//Precondition : Passing in positive integer values
//Postcondition: Private member age is changed
void Patient::setAge(int age)
{
	this->age = age;
}
//Precondition : Passing in char F or M
//Postcondition: Private member gender is changed
void Patient::setGender(char gender)
{
	this->gender = gender;
}

//--------------------------------------------------------------------
// Accessors Section
//--------------------------------------------------------------------
//Precondition : N/A
//Postcondition: Return private member checkedInTime
unsigned int Patient::getCheckedInTime() const
{
	return checkedInTime;
}
//Precondition : N/A
//Postcondition: Return private member priority
int Patient::getPriority() const
{
	return priority;
}
//Precondition : N/A
//Postcondition: Return private member name
string Patient::getName() const
{
	return name;
}
//Precondition : N/A
//Postcondition: Return private member age
int Patient::getAge() const
{
	return age;
}
//Precondition : N/A
//Postcondition: Return private member gender
char Patient::getGender() const
{
	return gender;
}

//--------------------------------------------------------------------
// Friends Section
//--------------------------------------------------------------------
//Precondition : Cpmpares the two objects of class Patient
//Postcondition: Returns true when patient 1 has less priority or returns false if patient 2 has less priority
bool operator <(const Patient& P1, const Patient& P2)
{
	return P1.priority < P2.priority;
}
//Precondition : Passing in ostream and an object of class Patient
//Postcondition: Output the information of the patient
ostream& operator <<(ostream& outs, const Patient& obj)
{
	outs << "ER level: " << obj.getPriority() << " - " << obj.ER_description[obj.getPriority() - 1] << '\n';
	outs << "\t\t\tChecked-In time: " << obj.getCheckedInTime() << '\n';
	outs << "\t\t\tPatient's name: " << obj.getName() << '\n';
	outs << "\t\t\tPatient's age: " << obj.getAge() << '\n';
	outs << "\t\t\tPatient's gender: " << obj.getGender() << '\n';
	return outs;
}