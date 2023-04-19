//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa2
// GraphTest.c
// Testing File for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   //added tests

   int j, m = 50;
   Graph A = NULL;
   A = newGraph(m);
   for(j=1; m<n; j++){
      if( j%5!=0 ) addEdge(A, j, j+1);
      if( j<=20  ) addEdge(A, j, j+5);
   }
   addArc(A, 7,17);
   addArc(A, 9, 49);

   printGraph(stdout, A);

   addEdge(A, 2, 4);
   addEdge(A, 1, 3);

   printf("\n");
   printGraph(stdout, A);

   List temp = newList();

    BFS(A, 49);
    printf("\nThe distance from 1 to 49 is %d\n", getDist(A, 1));
    printf("The shortest path from 1 to 49 is: ");
    getPath(temp,A, 1);
    printList(stdout, temp);
    printf("\n");
    clear(temp);

    freeList(&temp);
    freeGraph(&A);

    for(int i = 1; i < 11; i++){
      G = newGraph(i);
      if(getSource(G) != NIL) {
         printf("\nfalse\n");
      }
      freeGraph(&G);
   }
   printf("\ntrue\n");
   
   for(int i = 1; i < 11; i++){
      A = newGraph(i);
      for(int j = 1; j <= getOrder(A); j++){
         if(getParent(A, j) != NIL){
            printf("\nfalse\n");
         }
      }
      freeGraph(&A);
   }
   printf("\ntrue\n");


   return(0);
}
