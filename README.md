# Solving a puzzle game: Rush Hour

I adress the problem with a Breadth-first search (BFS) approach.
To do so, I modelized a state of the game by a graph and its neighbors are states reached by moving ONE car/truck by one cell. I used a map container to keep track of the states already checked so I don't loop.
The algorithm stops when the red car reaches the end (and returns the fastest path) or when all states have been checked.

-------

A typical entry puzzle is the file "jam21.txt".
The entry must be a txt file containing something like this (always 6 6 atm):

6 6
t1 c1 c1 0 c2 0
t1 c3 c4 0 c2 t2
t1 c3 c4 g g t2
t3 t3 t3 c5 0 t2
0 0 c6 c5 c7 c7
c8 c8 c6 c9 c9 0
