//Name: Alexis, Angie, Neidy, Vivian
//Date: 10/23/2023
//Description: Chapter 8 Assignment - Applications using Queues

#include <iostream> //For cout
#include <queue>    //For queue
#include <deque>    //For deque

//HEADER FILES
#include "input.h"  //For input validation
using namespace std;

//PROTOTYPES
int menuOption();
void option1();
void fillDeck(int, int, deque<int>&, deque<int>&);

int main()
{
	switch (menuOption())
	{
	case 0: exit(0);
	case 1: system("cls"); option1(); break;
	default:
		break;
	}
	return 0;
}

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

void option1()
{
	int numberCards = 0; //Contains the amount of cards user inputs
	deque<int> player1, player2;

	cout << "\n\t1> Simulation of War (card game) using deque STL\n";

	fillDeck(player1, player2);


	while (!player1.empty() && !player2.empty())
	{
		int card1 = player1.front();
		int card2 = player2.front();
		player1.pop_front();
		player2.pop_front();

		if (card1 > card2)
		{
			cout << "\n\t\tPlayer1:  " << card1 << "\tPlayer2:  " << card2 << " -> Player1 wins!";
			player1.push_back(card1);
			player1.push_back(card2);
		}
		else if (card1 < card2)
		{
			cout << "\n\t\tPlayer1:  " << card1 << "\tPlayer2:  " << card2 << " -> Player2 wins!";
			player2.push_back(card2);
			player2.push_back(card1);

		}
		else if (card1 == card2)
		{
			cout << "\n\t\tPlayer1:  " << card1 << "\tPlayer2:  " << card2 << " -> Tie breaker begins!";
			vector<vector<int>> store_all(2);
			store_all.at(0).push_back(card1);
			store_all.at(1).push_back(card2);

			do{
				if (player1.empty()) {
					for (int i = 0; i < store_all.size(); ++i) {
						for (int j = 0; j < store_all.at(i).size(); ++j) {
							player2.push_back(store_all.at(i).at(j));
						}
					}
					break;
				}
				else if (player2.empty()) {
					for (int i = 0; i < store_all.size(); ++i) {
						for (int j = 0; j < store_all.at(i).size(); ++j) {
							player1.push_back(store_all.at(i).at(j));
						}
					}

					break;
				}

				for (int i = 0; i < 3; i++)
				{
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

				int last_element_1 = store_all.at(0).at(store_all.at(0).size() - 1), last_element_2 = store_all.at(1).at(store_all.at(1).size() - 1);

				if (last_element_1 > last_element_2) {

					cout << "\n\t\tPlayer1:  " << last_element_1 << "\tPlayer2:  " << last_element_2 << " -> Player1 wins tie breaker!";
					for (int i = 0; i < store_all.size(); ++i) {
						for (int j = 0; j < store_all.at(i).size(); ++j) {
							player1.push_back(store_all.at(i).at(j));
						}
					}

					break;
				}
				else if (last_element_1 < last_element_2) {
					cout << "\n\t\tPlayer1:  " << last_element_1 << "\tPlayer2:  " << last_element_2 << " -> Player2 wins tie breaker!";
					for (int i = 0; i < store_all.size(); ++i) {
						for (int j = 0; j < store_all.at(i).size(); ++j) {
							player2.push_back(store_all.at(i).at(j));
						}
					}
					break;
				}
				else if(last_element_1 == last_element_2)
					cout << "\n\t\tPlayer1:  " << last_element_1 << "\tPlayer2:  " << last_element_2 << " -> Tie Breaker Again";
			} while (true);

		}

	}

	if (player2.empty())
		cout << "\n\tPlayer1 wins the war with most number of cards (" << player1.size() << ")";
	
	else
		cout << "\n\tPlayer2 wins the war with most number of cards (" << player2.size() << ")";	
}

void fillDeck(int suite, int numberCards, deque<int> &player1, deque<int> &player2)
{
	int numberCards = inputInteger("\n\tEnter a number of cards per suite: ", 1, 13);

	srand(unsigned(time(0)));
	deque<int> currentDeck;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= numberCards; ++j)
		{
			currentDeck.push_back(j);
		}
	}
	
	
	random_shuffle(currentDeck.begin(), currentDeck.end());


	for (int i = 0; i < (4 * numberCards); ++i)
	{
		if (i % 2 == 0) 
		{
			player2.push_back(currentDeck[i]);
			continue;
		}
		player1.push_back(currentDeck[i]);
	}
}