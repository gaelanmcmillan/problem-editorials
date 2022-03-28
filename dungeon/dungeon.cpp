/**
 * "Dungeon master" by Unknown Author
 * as seen in University of Ulm Local Contest 1997
 * https://open.kattis.com/problems/dungeon
 * 
 * Solution by Gaelan McMillan
 * 
 * Problem:
 *  	Find the length of the shortest path
 *  	from some starting point to some ending point
 *  	in a three-dimensional grid
 *
 * Solution:
 * 		1. Store the grid from input, making note of 'S' and 'E' coordinates — O(LRC)
 * 		2. Simple BFS with DP to find the cost of the shortest path — O(LRC*6)
 */

#include <iostream>
#include <algorithm>
#include <numeric>
#include <queue>
#include <array>
#include <string>
#include <vector>

using namespace std;

void solve(int L, int R, int C)
{
	vector<vector<vector<char>>> cave (
		L, vector<vector<char>> (
			R, vector<char>(C)
		)
	);

	int S [3];
	int E [3];

	// read in the cave layout
	for (int i = 0; i < L; ++i)
		for (int j = 0; j < R; ++j)
		{
			string obs; cin >> obs;
			for (int k = 0; k < C; ++k)
			{
				cave[i][j][k] = obs[k];
				if (obs[k] == 'E') // make note of end node
				{
					E[0] = i;
					E[1] = j;
					E[2] = k;
				}
				else if (obs[k] == 'S') // make note of start node
				{
					S[0] = i;
					S[1] = j;
					S[2] = k;
				}
			}
		}

	// getting min-cost-path from S to E

	// initialize DP
	bool seen[L][R][C];
	int  cost[L][R][C];

	for (int i = 0; i < L; ++i)
		for (int j = 0; j < R; ++j)
			for (int k = 0; k < C; ++k)
			{
				seen[i][j][k] = false;
				cost[i][j][k] = 2147483647;
			}

	// helper functions
	auto in_range = [](int i, int& lim) -> bool { 
		return (i >= 0 and i < lim); // simple index-error check
	};

	auto passable = [&](int x, int y, int z) -> bool {
		if (in_range(x, L) and in_range(y, R) and in_range(z, C))
		{
			return (cave[x][y][z] != '#'); // make sure node at x,y,z is not impassable 
		}
		return false;
	};

	// possible moves from each node
	vector<array<int,3>> dirs = {
		{ 1, 0, 0}, // down
		{-1, 0, 0}, // up
		{ 0, 1, 0}, // south
		{ 0,-1, 0}, // north
		{ 0, 0, 1}, // east
		{ 0, 0,-1}, // west
	};

	// BFS with single queue

	queue<array<int,3>> queue;

	queue.push({S[0],S[1],S[2]}); // add starting node
	cost[S[0]][S[1]][S[2]] = 0; // initialize its cost

	while (!queue.empty())
	{
		auto& [x,y,z] = queue.front(); queue.pop();
		for (auto& [dx,dy,dz] : dirs)
		{
			if (passable(x+dx, y+dy, z+dz))
			{
				cost[x+dx][y+dy][z+dz] = min(   // minimum of
					cost[x+dx][y+dy][z+dz],     // set cost and
					cost[x][y][z] + 1           // current cost + 1
				);     

				if (!seen[x+dx][y+dy][z+dz]) // if we haven't already searched from this node
				{
					seen[x+dx][y+dy][z+dz] = true;
					queue.push({x+dx, y+dy, z+dz}); // send it to the back of the line to be searched
				}
			}
		}
	}

	if (seen[E[0]][E[1]][E[2]]) // we reached the end at least once
		cout << "Escaped in " << cost[E[0]][E[1]][E[2]] << " minute(s).\n";
	else // could not reach the end
		cout << "Trapped!\n";
}

int main()
{
	int L,R,C;
	cin>>L>>R>>C;
	while (L and R and C)
	{
		solve(L,R,C);
		cin>>L>>R>>C;
	}
	return 0;
}
