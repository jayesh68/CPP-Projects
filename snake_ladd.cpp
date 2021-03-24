#include<iostream> 
#include <queue> 
using namespace std; 
  
struct queueEntry 
{ 
    int v;   
    int dist;  
}; 
  
int getMinDiceThrows(int move[], int N) 
{   
 
    bool *visited = new bool[N]; 
    for (int i = 0; i < N; i++) 
        visited[i] = false; 
    
    queue<queueEntry> q; 
  
    visited[0] = true; 
    queueEntry s = {0, 0}; 
    q.push(s); 

    queueEntry qe; 
    while (!q.empty()) 
    { 
        qe = q.front(); 
        int v = qe.v; 
        if (v == N-1) 
            break; 
  
        q.pop(); 
        for (int j=v+1; j<=(v+6) && j<N; ++j) 
        { 
            if (!visited[j]) 
            { 
                queueEntry a; 
                a.dist = (qe.dist + 1); 
                visited[j] = true; 

                if (move[j] != -1) 
                    a.v = move[j]; 
                else
                    a.v = j; 
                q.push(a); 
            } 
        } 
    } 

    return qe.dist; 
} 
  
int main() 
{ 
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
