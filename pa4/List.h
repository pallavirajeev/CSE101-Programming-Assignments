//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa4
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include<stdbool.h>
#include <stdio.h>


#define FORMAT "%d"  // format string 


// Exported types -------------------------------------------------------------
typedef struct ListObj* List; 


// Constructors-Destructors ---------------------------------------------------

// newList()
// Creates and returns a new empty List. 
List newList(void);

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L);

// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// front()
// Returns front element of L. 
// Pre: length()>0
void * front(List L);

// back()
// Returns back element of L. 
// Pre: length()>0
void * back(List L); 

// get()
// Returns cursor element of L. 
//Pre: length()>0, index()>=0
void * get(List L);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int *x);

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L);

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L);

// If cursor is defined and not at front, move cursor one step toward the front of L; 
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L);

// If cursor is defined and not at back, move cursor one step toward the back of L; 
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int *x); 

// append()
// Insert new element into L. If L is non-empty,insertion takes place after back element.
void append(List L, int *x); 

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int *x);

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int *x); 

// deleteFront()
// Delete the front element. 
// Pre: length()>0
void deleteFront(List L); 

// deleteBack()
// Delete the back element. 
// Pre: length()>0
void deleteBack(List L); 

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L); 


// Other Functions ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L); 


#endif