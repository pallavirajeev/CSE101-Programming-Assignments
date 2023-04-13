//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa1
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   Node next;
   Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int cursorInd;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next, prev, and data fields.
Node newNode(int x){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = x;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Creates and returns a new empty List. 
List newList(void){
   List L = NULL;
   L = malloc(sizeof(ListObj));
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->cursorInd = -1;
   L->length = 0;
   return(L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL){
   if (pL != NULL && *pL!= NULL){ 
      while(length(*pL) > 0)
      {            
          deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L){
   if(L == NULL){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
   if(L==NULL){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor==NULL){
      return -1;
   }
   else{
      return L->cursorInd;
   }
}

// front()
// Returns front element of L. 
// Pre: length()>0
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data); 
}

// back()
// Returns back element of L. 
// Pre: length()>0
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data); 
}

// get()
// Returns cursor element of L. 
//Pre: length()>0, index()>=0
int get(List L){
   if(L==NULL){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L)<= 0 || index(L)<0){
      printf("List Error: calling get() on empty List reference or undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);
}

//equals()
// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B){
   if(A == NULL && B == NULL){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(A == NULL || B == NULL){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(A) == length(B)){
      Node tempA = A->front;
      Node tempB = B->front;
      for(int i = 1; i < length(A); i++){
         if(tempA->data == tempB->data){
            tempA = tempA->next; //move to the next item 
            tempB = tempB->next; //move to the next item
         }
         else{
            return false;
         }
      }
      return true;
   }
   else{
      return false;
   }

}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L){
   if(L==NULL){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   while(length(L)>0){ //while there are still elements to clear
      deleteFront(L);
   }
   //set everything back to NULL/starting values
   L->front = NULL;
   L->back = NULL;
   L-> cursor = NULL;
   L->length = 0;
   L->cursorInd = -1;
}

// set()
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x){
   if(L==NULL){
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L)<= 0 || index(L)<0){
      printf("List Error: calling set() on empty List reference or undefined cursor\n");
      exit(EXIT_FAILURE);   
   }
   L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
   if(L==NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0){
      printf("List Error: calling moveFront() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->front;
   L->cursorInd = 0;
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
   if(L==NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0){
      printf("List Error: calling moveBack() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->back;
   L->cursorInd = length(L)-1;
}

// If cursor is defined and not at front, move cursor one step toward the front of L; 
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
   if(L==NULL){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(index(L)==-1){ //if cursor is undefinded do nothing
   }
   else if(L->cursor != L -> front){
      L->cursor = L->cursor->prev;
      L->cursorInd -= 1;
   }
   else{
      L->cursor = NULL;
      L->cursorInd = -1;
   }
}

// If cursor is defined and not at back, move cursor one step toward the back of L; 
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    if(L==NULL){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(index(L)==-1){ //if cursor is undefinded do nothing
   }
   else if(L->cursor != L -> back){
      L->cursor = L->cursor->next;
      L->cursorInd += 1;
   }
   else{
      L->cursor = NULL;
      L->cursorInd = -1;
   }
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x){
   if(L==NULL){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node C = newNode(x);
   if(length(L)== 0){
      L->front = L->back = C;
   }
   else{
      C->next = L->front;
      L->front->prev = C;
      L->front = C;
      if(L->cursorInd != -1){
         L->cursorInd += 1;
      }
   }
   L->length +=1;
}

// append()
// Insert new element into L. If L is non-empty,insertion takes place after back element.
void append(List L, int x){
   if(L==NULL){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node C = newNode(x);
   if(length(L)== 0){
      L->front = L->back = C;
   }
   else{
      C->prev = L->back;
      L->back->next = C;
      L->back = C;
   }
   L->length +=1;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
   if(L==NULL){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0 || index(L) < 0){
      printf("List Error: calling insertBefore() on empty List of cursor is not defined\n");
      exit(EXIT_FAILURE);
   }
   Node D = newNode(x);
   if(L->cursor != NULL){
      D->prev = L->cursor->prev;
      D->next = L->cursor;
      L->cursor->prev = D;
      if(L->cursor == L->front){
         L->front = D;
      }
      else if(D->prev != NULL){
         D->prev->next = D;
      }
      L->cursorInd +=1; 
      L->length +=1;
   }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
   if(L==NULL){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0 || index(L) < 0){
      printf("List Error: calling insertAfter() on empty List of cursor is not defined\n");
      exit(EXIT_FAILURE);
   }
   Node D = newNode(x);
   if(L->cursor->next != NULL){
      D->next = L->cursor->next;
      L->cursor->next->prev = D;
      L->cursor->next = D;
      D->prev = L->cursor;
   }
   else{
      D->prev = L->back;
      L->back->next = D;
      L->back = D;
   }
   L->length+=1;
}

// deleteFront()
// Delete the front element. 
// Pre: length()>0
void deleteFront(List L){
   if(L==NULL){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0){
      printf("List Error: calling deleteFront() on empty List reference\n");
      exit(EXIT_FAILURE);
   }
   Node tempE = L->front;
   if(length(L) > 1){
      L->front = L->front->next;
      L->front->prev = NULL;
   }
   else{
      L->front = NULL;
      L->back = NULL;
   }
   freeNode(&tempE);
   if(index(L)==0){
      L->cursor = NULL;
      L->cursorInd = -1;
   }
   else if(L->cursor > 0){
      L->cursorInd -=1;
   }
   L->length -=1;
} 

// deleteBack()
// Delete the back element. 
// Pre: length()>0
void deleteBack(List L){
   if(L==NULL){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0){
      printf("List Error: calling deleteBack() on empty List reference\n");
      exit(EXIT_FAILURE);
   }

   else{
      if (L->length == 1){
         Node tempF = L->back;
         freeNode(&tempF);
         L->cursor = NULL;
         L->front = L->back = NULL;
         L->cursorInd = -1;
      }
      else
      {
         Node tempF = L->back;
         L->back = L->back->prev;
         L->back->next = NULL;
         if (L->cursorInd == L->length - 1){
            L->cursorInd = -1;
         }
         freeNode(&tempF);
      }
      L->length-=1;
   }
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
   if(L==NULL){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0 || index(L) < 0){
      printf("List Error: calling delete() on empty List of cursor is not defined\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == L->front){
      deleteFront(L);
   }
   else if(L->cursor == L->back){
      deleteBack(L);
   }
   else{
      Node tempG = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      freeNode(&tempG);
      L->cursorInd -= 1;
      L->length -=1;
   }

}


// Other Functions ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
   if(L == NULL){
      printf("List Error: printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node temp = L->front;
   while(temp != NULL){
      if(L->cursorInd == length(L)-1){
         fprintf(out, "%d", temp->data);
      }
      else{
         fprintf(out, "%d ", temp->data);
      }
      temp = temp->next;
   }
}

// copyList()
// Returns a new List representing the same integer sequence as L. The cursor in 
//the new list is undefined, regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
   List copy = newList();
   Node C = L->front;
   while(C!= NULL){
      append(copy, C->data);
      C = C->next;
   }
   return copy;
}

