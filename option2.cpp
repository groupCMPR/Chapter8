#include <iostream>
#include "Patient.h"
#include "input.h"
#include <queue>

using namespace std;


int mainMenu();

void option2();
char option2Menu();


int main() {
	do {
		system("cls");
		switch (mainMenu()) {
		case 0: return EXIT_SUCCESS;
		case 2: option2(); break;
		default: cout << "\n\tERROR - INVALID OPTION"; break;
		}
		cout << "\n\n\t";
		system("pause");
	} while (true);

	return EXIT_SUCCESS;
}


int mainMenu() {
	cout << "\n\tCMPR131 Chapter 8: Applications using Queues";
	cout << "\n\t" << string(100, char(205));
	cout << "\n\t\t1> Simulation of War (card game) using deque STL";
	cout << "\n\t\t2> Simulation of an emergency room (ER) using priority queue STL";
	cout << "\n\t\t3> Simulation of checkout lines at CostCo using multiple queues STL";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\t0> Exit";
	cout << "\n\t" << string(100, char(205));

	return inputInteger("\n\t\tOption: ", 0, 3);
}

char option2Menu() {
	cout << "\n\t2> Simulation of an emergency room (ER) using priority queue STL";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\tA> Register a patient";
	cout << "\n\t\tB> Transfer patient(s) to the designation";
	cout << "\n\t\tC> Display transferred patients";
	cout << "\n\t" << string(100, char(196)); 
	cout << "\n\t\t0> return";
	cout << "\n\t" << string(100, char(205));
	return inputChar("\n\t\tOption: ", static_cast<string>("ABC0"));
}

void option2() {
	priority_queue<Patient> line;
	vector<Patient> submit;
	Patient patient;
	
	do {
		system("cls");
		switch (option2Menu()) {
		case '0': return;
		case 'A':
			patient.setName(inputString("\n\tEnter the patient's name: ", true));
			patient.setAge(inputInteger("\n\tEnter the patient's age: ", true));
			patient.setGender(inputChar("\n\tChoose the patient's gender (F-female or M-male): ", 'F', 'M'));
			patient.setPriority(inputInteger("\n\tChoose the ER level 1)Non-urgent, 2)Less Urgent, 3)Urgent, 4)Emergent, or 5)Resuscitation: ", 1, 5));
			patient.setCheckedInTime(time(0));

			line.push(patient);
			cout << "\n\tPatient information has been registered.";
			break;

		case 'B': 
			if (!line.empty())
			{
				if (line.top().getPriority() == 5)
				{
					submit.push_back(line.top());
					cout << "\n\t\t" << line.top().getName() << " - transfers to ICU...\n" ;
					line.pop(); 
					break;
				}
				else if (line.top().getPriority() == 4)
				{
					submit.push_back(line.top());
					cout << "\n\t\t" << line.top().getName() << " - transfers to surgery room...\n";
					line.pop();
					break;
				}
				else if (line.top().getPriority() == 3)
				{
					submit.push_back(line.top());
					cout << "\n\t\t" << line.top().getName() << " - transfers to emergency room...\n";
					line.pop();
					break;
				}
				else if (line.top().getPriority() == 2)
				{
					submit.push_back(line.top());
					cout << "\n\t\t" << line.top().getName() << " - transfers to x-ray lab...\n";
					line.pop();
					break;
				}
				else if (line.top().getPriority() == 1)
				{
					submit.push_back(line.top());
					cout << "\n\t\t" << line.top().getName() << " - examines and gives prescription...\n";
					line.pop();
					break;
				}
			}
			else  cout << "\n\tNo one is in line."; 
		
		break;

		case 'C':
			if (!submit.empty()) {

				sort(submit.begin(), submit.end());
				reverse(submit.begin(), submit.end());

				for (int i = 0; i < submit.size(); i++) {
					cout << "\n\t\t" << (i + 1) << " - " << submit[i];
				}
			}
			else  cout << "\n\tNo patient has been transferred."; 

			break;

		default: cout << "\n\tERROR - INVALID OPTION"; break;
		}
		cout << "\n\n\t";
		system("pause");
	} while (true);
}
