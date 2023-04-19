//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa2
// FindPath.c
// Client Program for Graph ADT
//-----------------------------------------------------------------------------

#include "Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
	FILE *in;
	FILE *out;

	if(argc != 3){
		fprintf(stderr, "usage: FindPath <input file> <output file>\n");
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
	int n;
	fscanf(in, " %d", &n);
	Graph G = newGraph(n);
	List L = newList();
	int u = 0;
	int v = 0;
	int dest = 0;
	int src = 0;

	//first fill in the graph 

	bool temp = true;
    while(temp == true){
        fscanf(in, "%d %d", &u, &v);
        if(u == 0 && v == 0){
            temp = false;
            break;
        }
        addEdge(G,u,v);
    }
    printGraph(out, G);

	//then perform BFS to find paths 
    while(true){
    	fscanf(in, " %d", &dest);
    	fscanf(in, " %d", &src);
    	
    	if(dest == 0 && src == 0){
            break;
        }

    	BFS(G, dest); 
		getPath(L, G, src);

		if(length(L) == 0 || getDist(G, src) < 0){
			fprintf(out, "The distance from %d to %d is infinity\n", dest, src);
        	fprintf(out, "No %d-%d path exists\n", dest, src);
        	fprintf(out, "\n");
		}
		else if(getDist(G, dest) != INF || getDist(G, dest) != 0){
        	fprintf(out,"\nThe distance from %d to %d is %d\n", dest, src, length(L)-1);
        	fprintf(out,"A shortest %d-%d path is: ", dest, src);
        	printList(out, L);
        	fprintf(out, "\n");
        	fprintf(out, "\n");
    	}
    	else if(src == dest){
        fprintf(out, "\nThe distance from %d to %d is\n", dest, src);
        fprintf(out, "A shortest path %d-%d is: %d\n", dest, src, dest);
        printList(out, L);
        fprintf(out, "\n");
        fprintf(out, "\n");
    	}
    	clear(L);
    }

    //close files
    fclose(in);
    fclose(out);

    //free memory
    freeList(&L);
    freeGraph(&G);
}