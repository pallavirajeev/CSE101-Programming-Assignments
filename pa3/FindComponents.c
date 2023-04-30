//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa3
// FindComponents.c
// Client Program for Graph ADT
//-----------------------------------------------------------------------------

#include "Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
	FILE *in;
	FILE *out;

	//check if there are the right number of arguments
	if(argc != 3){
		fprintf(stderr, "usage: FindComponents <input file> <output file>\n");
		exit(EXIT_FAILURE);
	}
	in = fopen(argv[1], "r"); //open input file for reading 
	if(in==NULL){
		printf("Error: File cannot be opened for reading");
	}
	out = fopen(argv[2], "w"); //open output file for writing
	if(out==NULL){
		printf("Error: File cannot be opened for writing");
	}

	//declare and initialize variables needed
	int n;
	fscanf(in, " %d", &n);
	Graph G = newGraph(n);
	List L = newList();
	List S = newList();
	int u = 0;
	int v = 0;

	//first fill in the graph 

	bool temp = true;
    while(temp == true){
        fscanf(in, "%d %d", &u, &v);
        if(u == 0 && v == 0){
            temp = false;
            break;
        }
        addArc(G,u,v);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    //then put vertices into the list
    for (int i = 1; i <= n; i++) 
    {
        append(L, i);
    }

    //call DFS on G
    DFS(G, L);

    //compute transpose of G and run DFS on G^T
    Graph T = transpose(G);
    DFS(T, L);

    //find the number of strongly connected components
    //create a ctr to keep track of the number of SCC
    //run through a for loop of the number of vertices of G^T and check if 
    //the parents are NIL(0) if so then increase the SCC ctr

    int ctr = 0;
    moveFront(L);
    for(int i = 1; i < getOrder(T) + 1; i++){
        if(getParent(T, get(L)) == NIL){
            ctr += 1;
        }
        moveNext(L);
    }

    fprintf(out, "G contains %d strongly connected components:\n", ctr);	
	
	//Find out which components are strongly connected and print them out 
	moveBack(L); //start at the back of the list
	int y = 1; //create a ctr for SCC (use this ctr to print out which component we are on)
	for(int i = 1; i < length(L) +1; i++){ //then run through a for loop as many times as the length of the list 
		int x = get(L);
		if(getParent(T, x) == NIL){ //check if the parent is NIL (0) 
			prepend(S, x); //if it is prepend it to to a new list ->these will be the strongly connected components 
			fprintf(out, "Component %d:", y);
			printList(out, S); //print to outfile
			fprintf(out, "%s","\n");
			clear(S); //clear S because this list will be added the next components strongly connected components
			y += 1; //increase the SCC ctr because we are now moving on to the next component 
		}
		else{ //if parent is not NIL then continue prepending the list S because not all strongly connected components
				//are added to be printed 
			prepend(S, x);
		}
		movePrev(L); //move backwards an element in list L which has all the vertices
	}
	fprintf(out, "%s","\n");


    //close files
    fclose(in);
    fclose(out);

    //free memory
    freeList(&L);
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
}








