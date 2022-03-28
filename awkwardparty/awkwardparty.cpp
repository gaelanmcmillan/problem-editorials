/** 
 * "Awkward Party" Magnus Øian and Torstein Strømme
 * https://open.kattis.com/problems/awkwardparty
 * 
 * Solution by Gaelan McMillan
 * 
 * Problem: 
 * 		Given a list of integers,
 * 		find the "awkwardness" of the list,
 * 		where "awkwardness" is defined as
 * 		the distance between the two closest
 * 		same-value integers.
 * 
 * Solution: "Online" min distance between two closest integers
 * 	1. Read in integers, keeping track of the position each value was last seen in.
 *  2. If the current integer has been seen already, 
 *     take its distance from its last occurence and
 * 	   compare it against the current minimum.
 *
 * Complexity: O(n)
*/

#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;
void solve()
{
	int n;
	cin >> n;

	unordered_map<int,int> last;
	int guest;
	int distance = n;

	for (int i = 0; i < n; ++i)
	{
		cin >> guest;
		if (last.find(guest) == last.end())
		{
			last[guest] = i;
		}
		else
		{
			distance = min(distance, i - last[guest]);
			last[guest] = i;
		}
	}
	cout << distance << '\n';
}

int main()
{
	solve();
	return 0;
}
