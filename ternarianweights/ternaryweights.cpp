#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

/*

given a starting weight
placed on the left side of the scales,
balance the scales using only powers of 3, non-repeating

item starts left,
weights start right
	        _R
	L _-.-^^ 
   	^^  |
   		|
==================

L+x - R = 0

what we know:

for the set a where a<i> = 3**i,
a<0> + a<1> + ... + a<n-1> <= (a<n> - 1) / 2

*/

/** 
 * print( { 1,2,3 } ) -> "1 2 3"
*/
void print(vector<ll>& v)
{
	auto b = v.begin();
	while (b != v.end())
		cout << *b++ << (b==v.end() ? "" : " ");
	cout << '\n';
}


// keep our pows between runs
vector<ll> pows {1};
ll c = 1;

void solve()
{

/** 
 * get input
*/
	ll x; // value to balance
	cin >> x;

/** 
 * populate required powers
 * pows will always have the next greatest power of 3
*/
	while (c < x) {
		pows.push_back(c*=3);
	}

/** 
 * balance scales
 * 
 * we can do this greedily using the fact that
 * we should always subtract or add the largest power of 3 that is
 * less than twice the size of |n|
*/

	/**
	 * Find the largest exponent which is less than twice the size of n
	 * log3(2*n) = log(2*n)/log(3)
	 */
	auto find_pow = [&] (ll& n) -> int {
		return floor(log( 2*abs(n) ) / log(3));
	};

	int i = find_pow(x);

	vector<ll> right;
	vector<ll> left;

	while (x != 0)
	{
		if (x > 0)
		{
			x -= pows[i];
			right.push_back(pows[i]);
		}
		else
		{
			x += pows[i];
			left.push_back(pows[i]);
		}
		i = find_pow(x);
	}

	cout << "left pan: ";
	print(left);
	cout << "right pan: ";
	print(right);
}

int main()
{
	int t; cin >> t;
	while (t--)
	{
		solve();
		cout << '\n';
	}
	return 0;
}
