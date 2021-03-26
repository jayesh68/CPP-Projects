#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm> 
#include "Puzzle.h"

//Function to print the different nodes traversed after goal node is reached
void Puzzle::printNode() {
	int count = 0;
	for (auto i : node) {
		if (count % 3 == 0)
			std::cout << std::endl;
		std::cout << i << ' ';
		count++;
	}
}

//Checking for the blank tile before performing an action
int Puzzle::blankTile() {
	auto it = std::find(node.begin(), node.end(), 0);
	auto z = std::distance(node.begin(), it);
	return (int)z;
}

//Action to move up the puzzle
void Puzzle::Up() {
	int blank = blankTile();
	std::vector<int> n = node;
	if (blank != 0 && blank != 1 && blank != 2)
		std::swap(n[blank], n[blank - 3]);
	Puzzle* child = new Puzzle(n, this);
	children.push_back(child);
}

//Action to move down the puzzle
void Puzzle::Down() {
	int blank = blankTile();
	std::vector<int> n = node;
	if (blank != 6 && blank != 7 && blank != 8)
		std::swap(n[blank], n[blank + 3]);
	Puzzle* child = new Puzzle(n, this);
	children.push_back(child);
}

//Action to move right in the puzzle
void Puzzle::Right() {
	int blank = blankTile();
	std::vector<int> n = node;
	if (blank != 2 && blank != 5 && blank != 8)
		std::swap(n[blank], n[blank + 1]);
	Puzzle* child = new Puzzle(n, this);
	children.push_back(child);
}

//Action to move left in the puzzle
void Puzzle::Left() {
	int blank = blankTile();
	std::vector<int> n = node;
	if (blank != 0 && blank != 3 && blank != 6)
		std::swap(n[blank], n[blank - 1]);
	Puzzle* child = new Puzzle(n, this);
	children.push_back(child);
}

//Function to perform the BFS method to find the goal node
void Puzzle::bfs(std::vector<int> const& start, std::vector<int> const& goal) {

	bool goalReached = false;
	std::queue<Puzzle*> openList;		//Queue which contain the next node to be processes
	std::queue<Puzzle*> visitedList;	//Queue to store the visited nodes traversed by the blank tile
	std::vector<Puzzle*> path;		//array to store the parent info for the children which would be used for backtracking

	Puzzle initnode = Puzzle(start, NULL);	
	openList.push(&initnode);		//Initializing the open list with the node entered by the user

	while (!openList.empty() && !goalReached) 
	{
		Puzzle* action = openList.front();	//Getting the element in the queue
		visitedList.push(action);		//Moving the node to the visited queue

		openList.pop();				//Popping the queue to store the info of the next node

		//Perfroming to different actions to move th blank tile
		action->Up();				
		action->Down();
		action->Right();
		action->Left();

		for (auto i : action->children) 
		{
			Puzzle* c = i;
			int a = 0;

			if (c->node == goal) 
			{	
				std::cout << std::endl << "Goal Reached" << std::endl;
				//If goal is reached performing backtracking to obtain the different nodes traversed
				path.push_back(c);
				while (c->parent != NULL) 
				{
					c = c->parent;
					path.push_back(c);
					goalReached = true;
				}
				std::reverse(path.begin(), path.end());
				std::cout << "Solution \n" << std::endl;
				for (auto i : path) {
					i->printNode();
					std::cout << std::endl;
				}
			}

			//If the child is not the goal and not visited, add it to the open list to perform action operations to get the children
			if (!visitedCheck(visitedList, c))
			{
				openList.push(c);
			}
		}
	}
}

//Boolean Function to check if a child node has been visited or not
bool Puzzle::visitedCheck(std::queue<Puzzle*> q, Puzzle* p) {
	bool exist = false;
	while (!q.empty()) {
		if (q.front()->node == p->node)
			exist = true;
		q.pop();
	}
	return exist;
}

//Function to check if the start node can be solved by counting the number of inversions. If odd num of inversions the puzzle cannot be solved
bool solvability(std::vector<int> const& puzzle) {
	int inv = 0, x = 0, 
	len = puzzle.size();

	for (int m = 0; m < len; m++) {
		x = puzzle.at(m);
		for (int n = m + 1; n < 9; n++) {
			if (puzzle.at(n) != 0 && x > puzzle.at(n))
				inv++;
		}
	}

	if (inv % 2 == 0)
		return 1;
	else
		return 0;
}

int main()
{
	std::vector<int> s;					//Start node to be entered by user
	std::vector<int> g = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };	//Goal node to be reached
	
	int element;
	int choice;

	//Getting user input
	std::cout << "\n Enter the elements 0 - 8 without repeating" << std::endl;
	for (int i = 0; i <= 8; i++) {
		std::cout << "Element num - " << i << " : ";
		std::cin >> element;
		s.push_back(element);
	}

	//Checking for inversions
	if (solvability(s)) {
		std::cout << "\nNode is valid :" << std::endl;
		for (int i = 0, len = s.size(); i < len; i++)
			std::cout << s.at(i) << ' ';
		Puzzle p;
		//Calling the main function to perform BFS to reach the goal node
		p.bfs(s, g);
	}
	else {
		std::cout << "\nSolution does not exist since there are odd number of inversions" << std::endl;
	}

}
