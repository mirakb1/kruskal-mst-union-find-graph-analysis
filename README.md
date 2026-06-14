# kruskal-mst-union-find-graph-analysis
Implementation of Kruskal’s algorithm using Disjoint Set Union (Union-Find) with path compression and union by rank, including MST construction, connectivity analysis, cycle detection, and graph path queries.
In this homework, you are required to implement Kruskal’s algorithm using the Disjoint 
Sets (Union-Find) data structure, along with additional graph functionalities. 
The input: Undirected connected weighted graph. 
The output: 
1- Is the graph connected? If the graph is not connected, display the message: “The 
graph does not have a spanning tree because it is not connected” and display the 
number of connected components of the graph. 
Hint: Use Union and Find data structure to perform this task. Another way to solve it is 
using Kruskal’s algorithm.  
2- The MST (Minimum spanning tree) created by Kruskal’s algorithm. 
3- The sets that are created in each step of executing the algorithm until they become 
one single set. 
4- The parent array created during the process of finding the MST. 
5- The weight of the MST. 
6- Does the graph have any cycles? Or is it acyclic (has no cycles)? 
7- Display a path between 2 nodes entered by the user (any path if it exists). 
Notes: 
1- Use Union and Find (version 3): Union by rank and FindSet with path compression. 
2- The following graphs are just examples, your code must be able to work on any 
graph with any number of nodes.
