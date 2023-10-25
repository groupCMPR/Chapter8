#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>
#include "input.h"
using namespace std;

//attempting a new way to make random number
#include <random>

int main() {
	//making a random number
	random_device develop;
	mt19937 rng(develop());

	int second = inputInteger("Enter the time(0..37800 in seconds) of the store will be operated : ", 0, 37800);
	int cash_register = inputInteger("Enter the number of cash registers(1..10) :", 1, 10);

	//variables for random number distribution
	int line_start = 5, line_end = 10, customer_start = 0, customer_end = 1; 

	//choice to change them to make the time more realistic
	if (inputChar("\n\tDo you want to customize the simulation or leave it as a fast paced simulation (Y/N): ") == 'Y') {
		line_start = inputInteger("\n\tPlease put in the minimum time it will take for the cashier to service a customer: ", true);
		line_end = inputInteger("\n\tPlease put in the maximum time it will take for the cashier to service a customer: ", line_start + 1, 5000);
		customer_start = inputInteger("\n\tPlease put in the minimum time it will take for a customer to enter the line: ", 0, 1800);
		customer_end = inputInteger("\n\tPlease put in the maximum time it will take for a customer to enter the line: ", customer_start + 1, 1800);
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

			//pushes person char(254), resets customer rng
			CostCo_Line.at(location).push(254);
			new_customer = customer_dist(rng);
		}

		//displays and changes CostCo_Line
		for (int i = 0; i < CostCo_Line.size(); ++i) {
			
			//if line has many people
			//else if line only has time stored and no people, empty so it is not displayed
			if (CostCo_Line.at(i).size() > 1) {

				//if the top is a 0, pops a person and reinitalizes time, counts as serving a  person
				int top = CostCo_Line.at(i).front();
				if (top == 0) {
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
			for(int iter = 0; !CostCo_Line.at(i).empty(); ++iter){
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
		this_thread::sleep_for(chrono::milliseconds(1000));
	} while (second > -1);


	return EXIT_SUCCESS;
}
