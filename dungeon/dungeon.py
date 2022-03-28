"""
"Dungeon master" by Unknown Author
as seen in University of Ulm Local Contest 1997
https://open.kattis.com/problems/dungeon

Solution by Gaelan McMillan

Problem:
    Find the length of the shortest path
    from some starting point to some ending point
    in a three-dimensional grid

Solution:
    1. Store the grid from input, 
       making note of 'S' and 'E' coordinates — O(LRC)

    2. Simple BFS with DP to find the cost of the shortest path — O(LRC*6)

Complexity: O(LRC)
"""

import fileinput
from collections import namedtuple, defaultdict, deque

if __name__ == "__main__":
    f = fileinput.input()
    def mapint(): return map(int, next(f).strip().split())

    while (True):
        L,R,C = mapint()
        if L==R==C==0: break

        S = None
        E = None

        cave = []
        floor = []

        # handle input
        for _ in range(L*(R+1)):
            line = next(f).strip()

            if line: # is not empty
                floor.append(line)
                for i, c in enumerate(line):
                    if c == 'S':
                        S = (len(cave), len(floor)-1, i)
                    elif c == 'E':
                        E = (len(cave), len(floor)-1, i)
            else:
                cave.append(floor[:])
                floor.clear()


        # helpers for dp
        def in_range(x, lim) -> bool:
            return (x >= 0 and x < lim)
        
        def passable(x, y, z) -> bool:
            if in_range(x,L) and in_range(y,R) and in_range(z,C):
                return cave[x][y][z] != '#'

            return False            

        # dp for min cost path
        seen = set()

        # initialize costs
        cost = defaultdict(lambda: float('inf'))
        
        dirs = [
            ( 1, 0, 0), # down
            (-1, 0, 0), # up
            ( 0, 1, 0), # south
            ( 0,-1, 0), # north
            ( 0, 0, 1), # east
            ( 0, 0,-1)  # west
        ]

        queue = deque()
        queue.append(S) # starting position
        cost[S] = 0 # cost of reaching S is 0

        while queue:
            x,y,z = queue.popleft()

            for dx,dy,dz in dirs:
                nc = (x+dx,y+dy,z+dz)

                if passable(*nc):
                    cost[nc] = min(cost[nc], cost[(x,y,z)]+1)

                    if nc not in seen:
                        seen.add(nc)
                        queue.append(nc)

        if E in seen:
            print(f"Escaped in {cost[E]} minute(s).")
        else:
            print("Trapped!")


        

