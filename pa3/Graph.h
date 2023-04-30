//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa3
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include "List.h"
#define INF ((int)-1) //INF should be any negative number
#define NIL ((int)0) //NIL should be any non positive number different than INF
#define UNDEF ((int)-2) 

/*** Exported types ***/
typedef struct GraphObj* Graph; 

/*** Constructors-Destructors ***/

//newGraph()
//returns a Graph pointing to a newly created GraphObj
//representing a graph having n vertices and no edges
Graph newGraph(int n);

//freeGraph()
//frees all heap memory associated with the Graph *pG,
//then sets the handle *pG to NULL
void freeGraph(Graph* pG);

/*** Access functions ***/

//getOrder()
//return the corresponding field values
int getOrder(Graph G);

//getSize()
//return the corresponding field values
int getSize(Graph G);

//getSource()
//returns the source vertex most recently used in function BFS()
//or NIL if BFS() has not yet been called
int getSource(Graph G);

//getParent()
//return the appropriate field values for the given vertex
//the parent of a vertex may be NIL
//Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u);

//getDist()
//returns distance from most recent BFS source to vertex u
//or INF if BFS() has not yet been called
//Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u);

//getPath()
//appends vertices of shortest path in G from source to u
//or appends value NIL if no such path exists
//Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺), getSource(G)!=NIL
void getPath(List L, Graph G, int u);

//getDiscover()
//return the appropriate field values for the given vertex
//the parent of a vertex may be NIL
//Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u); 

//getFinish
//return the appropriate field values for the given vertex
//the parent of a vertex may be NIL
//Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/

//makeNull()
//deletes all edges of G and restore to orignial state
void makeNull(Graph G);

//addEdge()
//inserts a new edge joining u to v
//Pre: two int arguments must lie in range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);

//addArc()
//inserts a new directed edge from u to v
//Pre: two int arguments must lie in range 1 to getOrder(G)
void addArc(Graph G, int u, int v);

//BFS()
//runs the BFS algorithm setting color, distance, 
//parent, and source fields
void BFS(Graph G, int s);

//DFS()
//performs the depth first search algorithm on G
//Pre: length(S)==getOrder(G)
void DFS(Graph G, List S);

/*** Other operations ***/

//transpose()
//returns a reference to a new graph object 
//representing the transpose of G
Graph transpose(Graph G);

//copyGraph()
//returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G);

//printGraph()
//prints the adjacency list representation
void printGraph(FILE* out, Graph G);

#endif