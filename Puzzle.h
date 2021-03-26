#ifndef PUZZLE_H
#define PUZZLE_H

//CLass which consists of vector variables to store the current node, parent and children info
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

#endif
