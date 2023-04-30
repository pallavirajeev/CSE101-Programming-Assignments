//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa3
// GraphTest.c
// Testing File for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }

   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);

   Graph A = newGraph(5);
    addEdge(A, 1, 4);
    addEdge(A, 1, 2);
    addEdge(A, 2, 5);
    addEdge(A, 2, 3);
    addEdge(A, 3, 4);
    addEdge(A, 4, 5);
    printGraph(stdout, A);
    printf("\n");
    printf("Order of A: %d\n", getOrder(A));
    printf("Size of A: %d\n", getSize(A));
    printf("\n");

   List B = newList();
   for(int i = 1; i <= 5; i++){
   		append(B,i);
   }
    DFS(A,B);
	printf("%s", "\n");
	printf("%d", getParent(A,4)); //3
 	printf("%s", "\n");
	printf("%d", getFinish(A,1)); //10
	printf("%s", "\n");
	printf("%d", getDiscover(A,3)); //3
	printf("%s", "\n");

    Graph D = newGraph(4);
	addArc(D,1,3);
	addArc(D,2,4);
	addArc(D,1,2);
	addEdge(D,3,4);
	printGraph(stdout,D);
	printf("Order of D: %d\n", getOrder(D));
    printf("Size of D: %d\n", getSize(D));
    printf("\n");

    freeList(&B);
    freeGraph(&A);
    freeGraph(&D);

   return(0);
}
