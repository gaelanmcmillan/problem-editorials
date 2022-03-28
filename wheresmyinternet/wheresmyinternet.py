"""
"Where's My Internet??" by Bjarki Ágúst Guðmundsson
https://open.kattis.com/problems/wheresmyinternet

Solution by Gaelan McMillan

Problem:
    Find all the nodes in a graph
    that are not reachable from node "1"

Solution:
    1. Link up the graph from input — O(m)
    2. Traverse graph from node "1" — O(n * adjacencies)
    3. Print all disconnected nodes — O(n)
"""
import fileinput
from collections import defaultdict, deque

if __name__ == "__main__":
    f = fileinput.input()
    def mapint(): return map(int, next(f).strip().split())

    n, m = mapint()

    # linking
    adj = defaultdict(set)

    for _ in range(m):
        a,b = mapint()
        adj[a-1].add(b-1)
        adj[b-1].add(a-1)

    # traversing
    connected = [False for _ in range(n)]
    queue = deque()

    queue.append(0) # add node 1
    connected[0] = True # it is connected by default

    # typical breadth first search with queue
    while queue:
        curr = queue.popleft() # grab the next node in line

        for node in adj[curr]: # search its disconnected neighbours 
            if not connected[node]:
                connected[node] = True
                queue.append(node)
    
    # printing
    disconnected_nodes = [str(i+1) for i,b in enumerate(connected) if not b]

    if disconnected_nodes:
        print('\n'.join(disconnected_nodes))
    else:
        print("Connected")



