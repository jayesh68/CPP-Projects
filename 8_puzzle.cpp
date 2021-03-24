#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm> 

class Puzzle{
public:
	std::vector<int> node;
	std::vector<Puzzle*> children;
	Puzzle* parent;
	
public:
	Puzzle() {};

	Puzzle(std::vector<int> _node, Puzzle* _parent)
		: node(_node), parent(_parent)
	{}

	void printNode(); 
	int blankTile(); 
	void Up();
	void Down();
	void Left();
	void Right();
	void bfs(std::vector<int> const&, std::vector<int> const&);
	bool visitedCheck(std::queue<Puzzle*> q, Puzzle* n);

};

void Puzzle::printNode() {
	int count = 0;
	for (auto i : node) {
		if (count % 3 == 0)
			std::cout << std::endl;
		std::cout << i << ' ';
		count++;
	}
}

int Puzzle::blankTile() {
	auto it = std::find(node.begin(), node.end(), 0);
	auto z = std::distance(node.begin(), it);
	return (int)z;
}

void Puzzle::Up() {
	int blank = blankTile();
	std::vector<int> n = node;
	if (blank != 0 && blank != 1 && blank != 2)
		std::swap(n[blank], n[blank - 3]);
	Puzzle* child = new Puzzle(n, this);
	children.push_back(child);
}

void Puzzle::Down() {
	int blank = blankTile();
	std::vector<int> n = node;
	if (blank != 6 && blank != 7 && blank != 8)
		std::swap(n[blank], n[blank + 3]);
	Puzzle* child = new Puzzle(n, this);
	children.push_back(child);
}

void Puzzle::Right() {
	int blank = blankTile();
	std::vector<int> n = node;
	if (blank != 2 && blank != 5 && blank != 8)
		std::swap(n[blank], n[blank + 1]);
	Puzzle* child = new Puzzle(n, this);
	children.push_back(child);
}

void Puzzle::Left() {
	int blank = blankTile();
	std::vector<int> n = node;
	if (blank != 0 && blank != 3 && blank != 6)
		std::swap(n[blank], n[blank - 1]);
	Puzzle* child = new Puzzle(n, this);
	children.push_back(child);
}

void Puzzle::bfs(std::vector<int> const& start, std::vector<int> const& goal) {

	bool goalReached = false;
	std::queue<Puzzle*> openList;
	std::queue<Puzzle*> visitedList;
	std::vector<Puzzle*> path;

	Puzzle initnode = Puzzle(start, NULL);
	openList.push(&initnode);

	while (!openList.empty() && !goalReached) 
	{
		Puzzle* action = openList.front();
		visitedList.push(action);

		openList.pop();
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

			if (!visitedCheck(visitedList, c))
			{
				openList.push(c);
			}
		}
	}
}

bool Puzzle::visitedCheck(std::queue<Puzzle*> q, Puzzle* p) {
	bool exist = false;
	while (!q.empty()) {
		if (q.front()->node == p->node)
			exist = true;
		q.pop();
	}
	return exist;
}

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
	std::vector<int> s;
	std::vector<int> g = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	
	int element;
	int choice;

	std::cout << "\n Enter the elements 0 - 8 without repeating" << std::endl;
	for (int i = 0; i <= 8; i++) {
		std::cout << "Element num - " << i << " : ";
		std::cin >> element;
		s.push_back(element);
	}

	if (solvability(s)) {
		std::cout << "\nNode is valid :" << std::endl;
		for (int i = 0, len = s.size(); i < len; i++)
			std::cout << s.at(i) << ' ';
		Puzzle p;
		p.bfs(s, g);
	}
	else {
		std::cout << "\nSolution does not exist since there are odd number of inversions" << std::endl;
	}

}
