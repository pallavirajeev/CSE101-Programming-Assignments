//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa2
// Graph.c
// Implementation File for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"

#define WHITE ((int)0)
#define GRAY  ((int)1)
#define BLACK ((int)2)

/*** Structs ***/
typedef struct GraphObj{
	List * neighbors;
	int * color;
	int * parent;
	int * distance;
	int order;
	int size;
	int source;
}GraphObj;

/*** Constructors-Destructors ***/

//newGraph()
//returns a Graph pointing to a newly created GraphObj
//representing a graph having n vertices and no edges
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = malloc(sizeof(List*)*(n+1));
	G->color = malloc(sizeof(int*)*(n+1));
	G->parent = malloc(sizeof(int*)*(n+1));
	G->distance = malloc(sizeof(int*)*(n+1));
	G->order= n;
	G->size=0;
	G->source=NIL;
	for(int i = 1; i < n+1; i++){
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF; 
	}
	return(G);
}

//freeGraph()
//frees all heap memory associated with the Graph *pG,
//then sets the handle *pG to NULL
void freeGraph(Graph* pG){
	for(int i = 1; i < (*pG)->order+1; i++){
		freeList(&(*pG)->neighbors[i]);	
	}
	free((*pG)->neighbors);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/

//getOrder()
//return the corresponding field values(vertices)
int getOrder(Graph G){
	//do we need to check if G is NULL list we did with the List
	return G->order;
}

//getSize()
//return the corresponding field values (edges)
int getSize(Graph G){
	return G->size;
}

//getSource()
//returns the source vertex most recently used in function BFS()
//or NIL if BFS() has not yet been called
int getSource(Graph G){
	return G->source;
}

//getParent()
//return parent of vertex u in the BFS tree created by BFS()
//or NIL if BFS() has not yet been called
//Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getParent() out of bounds\n");
      	exit(EXIT_FAILURE);
    }
    if(G->source == NIL){
    	return NIL;
    }
    return G->parent[u];
}

//getDist()
//returns distance from most recent BFS source to vertex u
//or INF if BFS() has not yet been called
//Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getDist() out of bounds\n");
      	exit(EXIT_FAILURE);
    }
    if(G->source == INF){
     	return INF;
    }
    return G->distance[u];
}

//getPath()
//appends vertices of shortest path in G from source to u
//or appends value NIL if no such path exists
//Pre: 1 ≤ 𝑢 ≤ getOrder(𝐺), getSource(G)!=NIL
void getPath(List L, Graph G, int u){
	if(getSource(G) == NIL){
		printf("Graph Error: calling getPath() before Breadth Search called\n");
      	exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() out of bounds\n");
      	exit(EXIT_FAILURE);
	}
	if(G->source == u){
		append(L,u);
		return;
	}
	else if(G->parent[u] == NIL){ 
		append(L,NIL);
		return;
	}
	List tempL = newList();
  	int  tempInt = u;
  	while (tempInt != G->source){
    	prepend(tempL, tempInt);
    	tempInt = getParent(G, tempInt);
  	}
  	prepend(tempL, G->source);
  	moveFront(tempL);
  	while (index(tempL) >= 0){
    	tempInt = get(tempL);
    	append(L, tempInt);
    	moveNext(tempL);
  	}
  	freeList(&tempL);
}

/*** Manipulation procedures ***/

//makeNull()
//deletes all edges of G and restore to orignial state
void makeNull(Graph G){
	for(int i = 1; i < G->order+1; i++){
		clear(G->neighbors[i]);
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF; 
	}
	G->size = 0;
	G->source = NIL;
}

//addEdge()
//inserts a new edge joining u to v
//Pre: two int arguments must lie in range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling addEdge() out of bounds\n");
      	exit(EXIT_FAILURE);
	}
	if(v< 1 || v > getOrder(G)){
		printf("Graph Error: calling addEdge() out of bounds\n");
      	exit(EXIT_FAILURE);
	}
	addArc(G, u,v);
	addArc(G,v,u); 
	G->size -= 1;
}

//addArc()
//inserts a new directed edge from u to v
//Pre: two int arguments must lie in range 1 to getOrder(G)
void addArc(Graph G, int u, int v){
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling addEdge() out of bounds\n");
      	exit(EXIT_FAILURE);
	}
	if(v< 1 || v > getOrder(G)){
		printf("Graph Error: calling addEdge() out of bounds\n");
      	exit(EXIT_FAILURE);
	}
	
  	List copyL = G->neighbors[u];
	moveFront(copyL);
	 
	while(index(copyL) != -1 && v > get(copyL)){
		moveNext(copyL);
	}
	if(index(copyL) >= 0){
		insertBefore(copyL, v);
	}
	else{
		append(copyL,v);
	}
	G->size++;
}

//BFS()
//runs the BFS algorithm setting color, distance, 
//parent, and source fields
void BFS(Graph G, int s){
	if(s < 0 || s > getOrder(G)){
		printf("Graph Error: calling BFS() out of bounds\n");
      	exit(EXIT_FAILURE);
    }
    for(int i = 1; i < G->order+1; i++){
    	if(i != s){
    		G->color[i] = WHITE;
        	G->distance[i] = INF;
        	G->parent[i] = NIL;
    	}
    	else{
    		G->color[s] = GRAY;
    		G->distance[s] = 0;
    		G->parent[s] = NIL;
    	}
    }
    G->source = s;
    List temp = newList();
    append(temp, s);
    while (length(temp) != 0){
        int x = front(temp);
        deleteFront(temp);
        for(moveFront(G->neighbors[x]); index(G-> neighbors[x]) != -1; moveNext(G->neighbors[x])){
            if (G->color[get(G->neighbors[x])] == WHITE){
                G->color[get(G->neighbors[x])] = GRAY;
                G->distance[get(G->neighbors[x])] = G->distance[x] + 1;
                G->parent[get(G->neighbors[x])] = x;
                append(temp, get(G->neighbors[x]));
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&temp);
}   

/*** Other operations ***/

//printGraph()
//prints the adjacency list representation
void printGraph(FILE* out, Graph G){
	for(int i = 1; i < G->order+1;i++){
		fprintf(out, "%d: ",i);
		moveFront(G->neighbors[i]);
		while(index(G->neighbors[i]) >= 0){
      		fprintf(out, " %d", get(G->neighbors[i]));
      		moveNext(G->neighbors[i]);
    	}
    	fprintf(out, "\n");
	} 
}








