/** 
 * "Where's My Internet??" by Bjarki Ágúst Guðmundsson
 * https://open.kattis.com/problems/wheresmyinternet
 * 
 * Solution by Gaelan McMillan
*/

#include <iostream>
#include <algorithm>
#include <numeric>

#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

/**
 * Problem:
 * 		Find all the nodes in a graph
 * 		that are not reachable from node "1"
 * 
 * Solution:
 * 		1. Link up the graph from input — O(2*m)
 * 		2. Traverse graph from node "1" — O(n*adjacencies)
 * 		3. Print all disconnected nodes — O(n)
 */

void bfs(int i, vector<bool>& disconnected, vector<unordered_set<int>>& adj)
{
	disconnected[i] = false;
	for (auto& j : adj[i])
	{
		if (disconnected[j])
			bfs(j, disconnected, adj);
	}
}
void solve()
{
	int n,m;
	cin >> n >> m;

	int count = 0;
	vector<int> ptr (n, -1);
	vector<unordered_set<int>> adj (n);

	auto if_not_in_then_add = [&] (unordered_set<int>& s, int x) {
		if (s.find(x) == s.end()) s.insert(x);
	};

	for (int i = 0; i < m; ++i)
	{
		int a,b; cin >> a >> b; a--; b--;
		if_not_in_then_add(adj[a], b);
		if_not_in_then_add(adj[b], a);
	}

	vector<bool> disconnected (n, true);
	
	bfs(0, disconnected, adj);

	vector<int> res;
	for (int i = 0; i < n; ++i)
		if (disconnected[i])
			res.push_back(i);

	if (res.empty()) cout << "Connected";
	else
		for (int i : res)
			cout << i+1 << '\n';
}

int main()
{
	solve();
	return 0;
}
