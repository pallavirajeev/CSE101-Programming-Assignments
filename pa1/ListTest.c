//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa1
// ListTest.c
// Tests for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"


int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   List D = newList();
   int i;

   printf("%s\n", isEmpty(A)?"true":"false"); //true

   for(i=1; i<=40; i+=2){
      append(A,i);
      prepend(B,i);
   }

   for(i = 50; i <=70; i++){
      append(D,i);
   }
   printList(stdout,D);  //list with numbers -20 to 0 incremented by 1
   printf("\n");
   
   printf("%s\n", isEmpty(B)?"true":"false"); //false

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   printf("%d\n", front(A)); //1
   printf("%d\n", front(B)); //39
   printf("%d\n", back(D)); //70


   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));

   deleteFront(A);
   printList(stdout,A); //list without the 1 in the front(and one less element)
   printf("\n");

   deleteBack(B);
   printList(stdout,B); //list without the 1 in the back (and one less element)
   printf("\n");

   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);


   return(0);
}

/*
Output of this program:
true
50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 
false
1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 
39 37 35 33 31 29 27 25 23 21 19 17 15 13 11 9 7 5 3 1 
1
39
70
1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 
1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 
false
false
true
1 3 5 7 9 -1 11 13 15 17 21 23 25 27 29 -2 31 33 35 37 39 
21
3 5 7 9 -1 11 13 15 17 21 23 25 27 29 -2 31 33 35 37 39 
39 37 35 33 31 29 27 25 23 21 19 17 15 13 11 9 7 5 3 
0
*/