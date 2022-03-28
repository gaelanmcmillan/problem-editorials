"""
"Awkward Party" Magnus Øian and Torstein Strømme
https://open.kattis.com/problems/awkwardparty

Solution by Gaelan McMillan

Problem: 
	Given a list of integers,
	find the "awkwardness" of the list,
	where "awkwardness" is defined as
	the distance between the two closest
	same-value integers.

Solution: "Online" min distance between two closest integers
	1.  Read in integers, keeping track of the position each value was last seen in.
    2.  If the current integer has been seen already, 
        take its distance from its last occurence and
	    compare it against the current minimum.

Complexity: O(n)
"""

from sys import stdin

if __name__ == "__main__":
    awkwardness = int(next(stdin)) # awkwardness defaults to n
    last = {}
    for place, guest in enumerate(map(int, next(stdin).split())):
        if guest not in last:
            last[guest] = place
        else:
            awkwardness = min(place-last[guest], awkwardness)
            if awkwardness == 1: break
            last[guest] = place

    print(awkwardness)