#include<iostream> 
#include <queue> 
using namespace std; 
  
struct queueEntry 
{ 
    int v;   	//position or vertex of the point
    int dist;   //dice throw from starting point
}; 
 
//BFS Function to calculate the minimum number of dice throws to reach the end point
int getMinDiceThrows(int move[], int N) 
{   

    // Setting all the vertices as not visited
    bool *visited = new bool[N]; 
    for (int i = 0; i < N; i++) 
        visited[i] = false; 
    
    queue<queueEntry> q; 
  
    visited[0] = true; 
    queueEntry s = {0, 0}; 	// distance of 0'th vertex is also 0
    q.push(s); 

    queueEntry qe; 
    while (!q.empty()) 
    { 
        qe = q.front(); 
        int v = qe.v; 		// vertex no. of queue entry

	//if verted already at goal
        if (v == N-1) 
            break; 
  
        q.pop(); 

	//For a dice throw ranging from a 1 to 6
        for (int j=v+1; j<=(v+6) && j<N; ++j) 
        { 
            if (!visited[j]) 
            { 
                queueEntry a; 
                a.dist = (qe.dist + 1); 	//Computing the dice throws from starting point to the current vertex 
                visited[j] = true; 		//Setting visited to be true

                if (move[j] != -1) 		//Checking for a snake or ladder
                    a.v = move[j];   	
                else
                    a.v = j; 
                q.push(a); 
            } 
        } 
    } 

    return qe.dist; 				//returning the number of dice throws to reach the goal
} 
  
int main() 
{ 
    //100 points on the board
    int N = 100; 

    int moves[N]; 
    for (int i = 0; i<N; i++) 
        moves[i] = -1; 
  
    // Ladders 
    moves[1] = 38; 
    moves[4] = 14; 
    moves[9] = 31; 
    moves[21] = 42; 
    moves[28] = 84; 
    moves[51] = 67; 
    moves[72] = 91; 
    moves[80] = 99;

    // Snakes 
    moves[17] = 7; 
    moves[54] = 34; 
    moves[62] = 19; 
    moves[64] = 60; 
    moves[87] = 36; 
    moves[93] = 73; 
    moves[95] = 75; 
    moves[98] = 79;

    cout << "Min Dice throws required is " << getMinDiceThrows(moves, N); 
    return 0; 
} 
