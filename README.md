# Maximum agreement subtree problem solver
A C program which loads n rooted trees and then for each pair it calculates a minimum amount of leaves which removal would make both trees isomorphic.
## Synopsis
One of the projects I made for Algorithms and Data Structures classes. A graph theory problem, known as the [maximum agreement subtree problem](https://en.wikipedia.org/wiki/Maximum_agreement_subtree_problem) (in short, MAST).
## How does it work?
At first, a user has to enter n trees written in [Newick notation](https://en.wikipedia.org/wiki/Newick_format). After that, each pair of trees gets compared and program returns a result integer. A result is a minimum amount of leaves which removal would make both trees **isomorphic** (in short: isomorphic graphs have the same amount of vertices and exactly the same connections. That means they both can be drawn in the same way).
## Complexity
Approximated complexity of the algorithm is O(n^2). It may be slightly improved in the future.
## Example input and output
### Input:
```
2
(4,(8,1,(5,3)),(9,2,(10,(7,6))));
(10,(8,(9,(5,4)),(6,2,3)),(7,1));
```
### Output:
```
6
```