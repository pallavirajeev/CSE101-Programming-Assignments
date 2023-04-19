//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa2
// Graph.h
// Header file for Grpaph ADT
//-----------------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include "List.h"
#define INF ((int)-1) //INF should be any negative number
#define NIL ((int)0) //NIL should be any non positive number different than INF

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
//return parent of vertex u in the BFS tree created by BFS()
//or NIL if BFS() has not yet been called
//Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
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

/*** Other operations ***/

//printGraph()
//prints the adjacency list representation
void printGraph(FILE* out, Graph G);

#endif