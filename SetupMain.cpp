//Names: Alexis Martinez, Angie Campos, Neidy Malaga, & Vivian Huynh
//Date: 10/23/2023
//Description: Chapter 8 Assignment - Applications using Queues

#include <iostream> //For cout
#include <queue>    //For queue
#include <deque>    //For deque
#include <vector>   //For vector
#include <thread>   //For thread
#include <chrono>   //For chrono
#include <random>   //For random_device

//HEADER FILES
#include "input.h"  //For input validation
#include "Patient.h" //For option 2
using namespace std;

//PROTOTYPES
int menuOption();

//Option 1 - Simulation of War Card Game (Angie, Neidy, Vivian)
void option1();
void fillDeck(int, int, deque<int>&, deque<int>&);
//Option 2 - Simulation of emergency room (Alexis)
char option2Menu();
void option2();
//Option 3 - Simulation of checkout lines (Neidy)
void option3();

//Precondition : N/A
//Postcondition: Calls option 1, 2, and 3
int main()
{
	do
	{
		system("cls");
		switch (menuOption())
		{
		case 0: exit(0);
		case 1: system("cls"); option1(); break;
		case 2: system("cls"); option2(); break;
		case 3: system("cls"); option3(); break;
		default: cout << "\t\tERROR: - Invalid option. Please re-enter"; break;
		}
		cout << "\n";
		system("pause");
	} while (true);
	return 0;
}

//Precondition : Calls from main
//Postcondition: Returns integer choice
int menuOption()
{
    cout << "\n\tCMPR131 Chapter 8: Applications using Queues (Final Group 2)";
	cout << "\n\t" << string(100, char(205));
    cout << "\n\t\t1> Simulation of War (card game) using deque STL";
    cout << "\n\t\t2> Simulation of an emergency room (ER) using priority queue STL";
    cout << "\n\t\t3> Simulation of checkout lines at CostCo using multiple queues STL";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\t0> Exit";
	cout << "\n\t" << string(100, char(205));

	return inputInteger("\n\t\tOption: ", 0, 3);
}

//Precondition : Called from main
//Postcondition: Simulate the war card game
void option1()
{
	int suite = 4;       //Contains the amount of suites in a deck of cards (Normal deck has 4)
	int numberCards = 0; //Contains the amount of cards user inputs
	deque<int> player1;  //Contains the cards of player1
	deque<int> player2;  //Contains the cards of player2

	cout << "\n\t1> Simulation of War (card game) using deque STL\n";
	numberCards = inputInteger("\n\tEnter a number of cards per suite: ", 1, 13);

	fillDeck(suite, numberCards, player1, player2);

	while (!player1.empty() && !player2.empty())
	{
		int card1 = player1.front(); //Contains player1's top card
		int card2 = player2.front(); //Contains player2's top card
		player1.pop_front();
		player2.pop_front();

		//Player1 wins
		if (card1 > card2)
		{
			cout << "\n\t\tPlayer1:  " << card1 << "\tPlayer2:  " << card2 << " -> Player1 wins!";
			player1.push_back(card1);
			player1.push_back(card2);
			cin.get(); //To pause each time a card is played
		}
		//Player2 wins
		else if (card1 < card2)
		{
			cout << "\n\t\tPlayer1:  " << card1 << "\tPlayer2:  " << card2 << " -> Player2 wins!";
			player2.push_back(card2);
			player2.push_back(card1);
			cin.get();
		}
		//Tie
		else if (card1 == card2)
		{
			cout << "\n\t\tPlayer1:  " << card1 << "\tPlayer2:  " << card2 << " -> Tie breaker begins!";
			vector<vector<int>> store_all(2); //Store all of the cards popped out while tied
			store_all.at(0).push_back(card1);
			store_all.at(1).push_back(card2);

			do {
				//If player1's deck is empty, push in all the cards to player2, the winner.
				if (player1.empty())
				{
					for (int i = 0; i < store_all.size(); ++i) {
						for (int j = 0; j < store_all.at(i).size(); ++j) {
							player2.push_back(store_all.at(i).at(j));
						}
					}
					break;
				}
				//If player2's deck is empty, push in all the cards to player1, the winner.
				else if (player2.empty()) 
				{
					for (int i = 0; i < store_all.size(); ++i) {
						for (int j = 0; j < store_all.at(i).size(); ++j) {
							player1.push_back(store_all.at(i).at(j));
						}
					}

					break;
				}

				//Remove the top three cards
				for (int i = 0; i < 3; i++){
					if (!player1.empty())
					{
						store_all.at(0).push_back(player1.front());
						player1.pop_front();
					}

					if (!player2.empty())
					{
						store_all.at(1).push_back(player2.front());
						player2.pop_front();
					}
				}

				int last_element_1 = store_all.at(0).at(store_all.at(0).size() - 1); //Contains player1's fourth card
				int last_element_2 = store_all.at(1).at(store_all.at(1).size() - 1); //Contains player2's fourth card

				//Player1 wins tie breaker
				if (last_element_1 > last_element_2) 
				{
					cout << "\n\t\tPlayer1:  " << last_element_1 << "\tPlayer2:  " << last_element_2 << " -> Player1 wins tie breaker!";
					for (int i = 0; i < store_all.size(); ++i) {
						for (int j = 0; j < store_all.at(i).size(); ++j) {
							player1.push_back(store_all.at(i).at(j));
						}
					}
					cin.get();
					break;
				}
				//Player2 wins tie breaker
				else if (last_element_1 < last_element_2) 
				{
					cout << "\n\t\tPlayer1:  " << last_element_1 << "\tPlayer2:  " << last_element_2 << " -> Player2 wins tie breaker!";
					for (int i = 0; i < store_all.size(); ++i) {
						for (int j = 0; j < store_all.at(i).size(); ++j) {
							player2.push_back(store_all.at(i).at(j));
						}
					}
					cin.get();
					break;
				}
				//Tie again
				else if (last_element_1 == last_element_2)
				{
					cout << "\n\t\tPlayer1:  " << last_element_1 << "\tPlayer2:  " << last_element_2 << " -> Tie Breaker again!";
				}
			} while (true);
		}
	}
	//Number of cards winner has at the end
	if (player2.empty())
		cout << "\n\tPlayer1 wins the war with most number of cards (" << player1.size() << ")\n";
	else
		cout << "\n\tPlayer2 wins the war with most number of cards (" << player2.size() << ")\n";
}
//Precondition : Called from option1, Pass in valid parameters
//Postcondition: Push in elements into the two containers player1 & player2
void fillDeck(int suite, int numberCards, deque<int> &player1, deque<int> &player2)
{
	srand(time(0)); //To randomize by the GMT time
	deque<int> currentDeck; //Contains the number of cards 

	//Initialize the deck by pushing in the cards
	for (int i = 0; i < suite; i++){
		for (int j = 1; j <= numberCards; j++){
			currentDeck.push_back(j);
		}
	}

	random_shuffle(currentDeck.begin(), currentDeck.end());

	//Push in each half of the deck to each player
	for (int i = 0; i < (suite * numberCards); i++){
		if( i % 2 == 0){
			player2.push_back(currentDeck[i]);
			continue;
		}
		player1.push_back(currentDeck[i]);
	}
}

//Precondition : Called from option 2
//Postcondition: Returns the char option
char option2Menu() {
	cout << "\n\t2> Simulation of an emergency room (ER) using priority queue STL";
	cout << "\n\t" << string(100, char(205));
	cout << "\n\t\tA> Register a patient";
	cout << "\n\t\tB> Transfer patient(s) to the designation";
	cout << "\n\t\tC> Display transferred patients";
	cout << "\n\t" << string(100, char(196));
	cout << "\n\t\t0> return";
	cout << "\n\t" << string(100, char(205));
	return inputChar("\n\t\tOption: ", static_cast<string>("ABC0"));
}
//Precondition : Called from main
//Postcondition: Simulate the emergency room
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
			patient.setAge(inputInteger("\tEnter the patient's age: ", true));
			patient.setGender(inputChar("\tChoose the patient's gender (F-female or M-male): ", 'F', 'M'));
			patient.setPriority(inputInteger("\tChoose the ER level 1)Non-urgent, 2)Less Urgent, 3)Urgent, 4)Emergent, or 5)Resuscitation: ", 1, 5));
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
					cout << "\n\t\t" << line.top().getName() << " - transfers to ICU...\n";
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

//Precondition : Called from main
//Postcondition: Simulate the checkout line
void option3()
{
	random_device develop;
	mt19937 rng(develop());

	cout << "\n\t3> Simulation of checkout lines at a CostCo warehouse store";
	int second = inputInteger("\n\n\tEnter the time(0..37800 in seconds) of the store will be operated : ", 0, 37800);
	int cash_register = inputInteger("\n\tEnter the number of cash registers(1..10) :", 1, 10);

	//variables for random number distribution
	int line_start = 0, line_end = 5, customer_start = 0, customer_end = 0;

	//choice to change them to make the time more realistic
	if (inputChar("\n\tDo you want to customize the simulation or leave it as a fast paced simulation (Y/N): ") == 'Y') {
		line_start = inputInteger("\n\tPlease put in the minimum time it will take for the cashier to service a customer: ", 0, 1500);
		line_end = inputInteger("\n\tPlease put in the maximum time it will take for the cashier to service a customer: ", line_start, 5000);
		customer_start = inputInteger("\n\tPlease put in the minimum time it will take for a customer to enter the line: ", 0, 1800);
		customer_end = inputInteger("\n\tPlease put in the maximum time it will take for a customer to enter the line: ", customer_start, 1800);
	}

	//creates the distribution
	uniform_int_distribution<int> line_wait_dist(line_start, line_end);
	uniform_int_distribution<int> customer_dist(customer_start, customer_end);

	//to hold all queues, to hold individual queue
	vector <queue<int>> CostCo_Line(cash_register);
	queue <int> swap_Queue;

	int new_customer = customer_dist(rng), served_amount = 0; //set first customer rng

	do {
		system("cls"); //clears output
		cout << "\n\t CostCo warehouse store: " << second << "       Number of served customers : " << served_amount;

		//if customer has entered
		if (new_customer < 1) {

			for (int i = 0; i < 4; ++i) {
				//finds row of line with less people (must have 2 less)
				int location = 0;
				size_t smallest_size = CostCo_Line.at(0).size();

				for (int i = 1; i < CostCo_Line.size(); ++i) {
					if (CostCo_Line.at(i).size() + 2 < smallest_size) {
						smallest_size = (CostCo_Line.at(i).size());
						location = i;
					}
				}

				//if row is empty, pushes the waiting time
				if (CostCo_Line.at(location).empty()) {
					CostCo_Line.at(location).push(line_wait_dist(rng) + 1);
				}

				//pushes person char number only (254), resets customer rng
				CostCo_Line.at(location).push(254);
			}

			new_customer = customer_dist(rng);
		}

		//displays and changes CostCo_Line
		for (int i = 0; i < CostCo_Line.size(); ++i) {

			//if line has many people
			//else if line only has time stored and no people, empty so it is not displayed
			if (CostCo_Line.at(i).size() > 1) {

				//if the top is a 0, pops a person and reinitalizes time, counts as serving a  person
				if (CostCo_Line.at(i).front() == 0) {
					CostCo_Line.at(i).pop();
					CostCo_Line.at(i).front() = line_wait_dist(rng) + 1;
					++served_amount;
				}

				//subtracts one second as this is a way to ensure seconds start subtracting when
				//there is at least one customer present
				CostCo_Line.at(i).front() = CostCo_Line.at(i).front() - 1;
			}
			else if (CostCo_Line.at(i).size() == 1)
				CostCo_Line.at(i).pop();

			//copies to retain all people and time
			swap_Queue = CostCo_Line.at(i);

			cout << "\n\t\tCash register #" << (i + 1);

			//displays cash register and customers (as blocks)
			for (int iter = 0; !CostCo_Line.at(i).empty(); ++iter) {
				if (iter == 0) {
					cout << "\n\t\t\t" << char(254) << CostCo_Line.at(i).front() << char(254) << " ";
					CostCo_Line.at(i).pop();
					continue;
				}

				cout << char(CostCo_Line.at(i).front());

				if (iter % 4 == 0) {
					cout << " ";
				}

				CostCo_Line.at(i).pop();
			}

			//swaps back into normal queue
			CostCo_Line.at(i).swap(swap_Queue);
			cout << endl;
		}

		--new_customer;
		--second;

		//to make more visible to person watching the simulation occur
		this_thread::sleep_for(chrono::milliseconds(200));
	} while (second > -1);
}
