1. Graph Generation
Your program should take a single command line parameter indicating the number of vertices in
the graph. Because scale-free graphs tend to be sparse, you should use the adjacency list data
structure to represent the graph.

The network topology is constructed using a well-known principle called preferential attachment
[1]. The key idea behind preferential attachment is when a vertex is added to an existing
network, it is more likely to establish a link to another vertex that already has a high degree (a
large number of edges) compared to vertices with fewer edges. This construction mechanism is
also referred to as “the rich get richer.”
More precisely, when a new vertex is added to an existing network, it is attached via an edge to a
randomly selected vertex i with probability p(i). p(i) is defined as: d(i) / D where d(i) is the
degree of vertex i, and D is the sum of vertex degrees of all vertices in the existing network prior
to adding the new vertex.
The algorithm to generate the topology with N vertices is as follows:

1. Construct a fully connected topology containing n0 vertices, where n0 << N. A fully
connected network means there is a single edge between every pair of vertices (so a fully
connected network with n0 vertices has n0*(n0-1)/2 edges). For this assignment, assume
n0 is equal to 5 vertices.

2. Assuming the network now contains k vertices (labeled 0, 1, 2, … k-1) add one additional
vertex k and one edge between k and one randomly selected vertex j with probability p(j)
as defined above using the preferential attachment rule.

3. Repeat the previous step until the network contains N vertices.
To implement this program, implement a function called PickNode() that picks the vertex to
which a new link is to be added. The prototype is defined:
int PickNode (int *D, int N, int DTotal);
where N is the number of vertices in the existing network, D indicates the degree of vertices in
the network where D[i] is the degree of vertex i, (i = 0, 1, … N-1), and DTotal is the sum of
the vertex degrees over the entire network (i.e., the sum of all values in D[]). PickNode()
returns the number of the vertex to which a new edge is to be added.
Note that the construction described above guarantees the network consists of a single connected
component, i.e., there is a path between every pair of vertices in the graph.


2. Graph Analysis
To evaluate the resilience of the network, randomly remove vertices from the network until the
network is no longer connected (i.e., there are at least two vertices with no path between them).
Removal of a vertex of course removes all links attached to the vertex. The question to be
addressed is how many randomly selected vertices can be removed before the network becomes
disconnected.

To evaluate this question, you will need a program to check if the network is connected. For this
purpose, write a program that does a breadth-first-search (BFS) to traverse the network, and
determine the number of vertices in the network reachable from the source node. If the number
returned by the BFS program is equal to the number of vertices in the entire network, then the
network is connected.

Your program should repeatedly remove a randomly selected vertex (any vertex in the network is
equally likely to be selected) and check to see if the network is still connected. Continue this
process until the graph is no longer connected. This constitutes a single experiment that yields a
number indicating the number of vertices that had to be removed to make the network
disconnected. Call this value K.

Run your program many times using different initial random number seeds to complete many
experiments, as described above. From this data, generate a histogram indicating the number of
vertices that must be removed for the network to become disconnected. This should give you
some idea of the probability distribution of K. Use as large a network size as your programs can
process in a reasonable amount of time.
In addition to describing the results of your experiments and showing the histogram you
obtained, your report should also briefly describe at least one application where scale-free
networks arise in practice by specifying what the vertices and links represent, and what kinds of
questions a graph analysis might answer. Be specific, indicating what the vertices and links
represent in that application.
