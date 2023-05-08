//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa4
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj* Entry;

typedef struct MatrixObj{
	List *rows; 
	int size;
	//another field for nnz
	int nnz;

} MatrixObj;

typedef struct EntryObj{
	double value;
	int column;
} EntryObj;

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	if(n < 0){
		printf("MatrixObj Error: calling newMatrix() when n is less than 0\n");
    	exit(EXIT_FAILURE);
	}
	Matrix M = malloc(sizeof(MatrixObj));
	M->rows = malloc(sizeof(List)*(n+1));
	M->size = n;
	M->nnz = 0;
	for(int i = 1; i < n+1; i++){
		M->rows[i] =newList();
	}
	return M;
}

//newEntry()
//Returns a reference to a new nXn Matrix object in the zero state.
Entry newEntry(int c, double v)
{
    if(c < 0){
    	printf("EntryObj Error: calling newEntry() on columns less than 0\n");
    	exit(EXIT_FAILURE);
    }
    Entry E = malloc(sizeof(EntryObj));
    E->value = v;
    E->column = c;
    return E;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if (*pM != NULL && pM != NULL) {
        makeZero(*pM);
        for (int i = 1; i <= (*pM)->size; i++) {
            freeList(&(*pM)->rows[i]);
            (*pM)->rows[i] = NULL;
        }
        free((*pM)->rows);
    }
    free(*pM);
    *pM = NULL;
}

//freeEntry()
//Frees heap memory associated with *pE, sets *pE to NULL.
void freeEntry(Entry* pE){
	if( pE!=NULL && *pE!=NULL ){
    	free(*pE);
		*pE = NULL;
   }
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if(M==NULL){
      printf("Matrix Error: calling size() on NULL\n");
      exit(EXIT_FAILURE);
   }
   return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if(M==NULL){
      printf("Matrix Error: calling NNZ() on NULL reference\n");
      exit(EXIT_FAILURE);
   }
   return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling equals() on NULL reference\n");
    	exit(EXIT_FAILURE);
	}
	//if sizes are different return false
	if(size(A) != size(B)){
		return 0;
	}
	//if sizes are the same and the matrices are not NULL, check if they are the same
	for(int i = 1; i < size(A) + 1; i++){
		//check if the length of the rows are the same
		if(length(A->rows[i]) != length(B->rows[i])){
			return 0;
		}
		//move cursor to the front of both lists (rows[i])
		moveFront(A->rows[i]); moveFront(B->rows[i]);
		//now compare the entries of the matrices 
		//run a loop while the index is not undefined
		while(index(A->rows[i]) >=0){
			//check if the columns of A and B are the same 
			//then check if the values of A and B are the same
			//to do so, make get(A->rows[i]) and get(B->rows[i]) an entry object because 
			//that is the only way to access columns and values 
			Entry cura = (Entry)get(A->rows[i]);
			Entry curb = (Entry)get(B->rows[i]);
			if(cura->column != curb->column){
				return 0;
			}
			if(cura->value != curb->value){
				return 0;
			}
			//finally move to the next element of the list (in the matrix)
			moveNext(A->rows[i]);
			moveNext(B->rows[i]);
		}
	}
	return 1;
}

// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	if(M==NULL){
      printf("Matrix Error: calling makeZero() on NULL reference\n");
      exit(EXIT_FAILURE);
   	}
   	Entry tempE = NULL;
   	//set the number of NNZ entries to zero
   	M->nnz = 0;
   	   	//then run through a loop the size of the matrix
   	for(int i = 1; i < size(M)+1; i ++){
   		//make a temp variable to store the list that is the first row of matrix
   		//moveFront on that temp var
   		//this will make the cursor go to the beginning so you can make 
   		//all the entries 0 from the start of the row
   		List tempL = M->rows[i];
   		moveFront(tempL);
   		//run a loop while the index of the list is not undefined
   		while(index(M->rows[i]) >= 0){
   			//make a temp variable for an entry object 
   			//set the entry back to 0 by casting to an entry object 
   			tempE = (Entry)get(tempL);
   			//free the memory 
   			freeEntry(&tempE);
   			//move to the next element of the list 
   			moveNext(tempL);
   		}
   		//clear tempL so that you can store the next row's data
   		clear(tempL);
   	}
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if( M==NULL ){
   		printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
   		exit(EXIT_FAILURE);
	}
	if(j > size(M) || j < 1){
   		printf("Matrix Error: calling changeEntry() on invalid column size\n");
      	exit(EXIT_FAILURE);
   	}
   	if(i > size(M) || i < 1){
   		printf("Matrix Error: calling changeEntry() on invalid row size\n");
      	exit(EXIT_FAILURE);
   	}
    if(size(M) == 0){
        printf("Matrix Error: calling changeEntry() on size 0\n");
      	exit(EXIT_FAILURE);
    }
    //make a temp list to hold the row at i of matrix M
    List tempL = M->rows[i];
    //create entry object 
    Entry tempE;
    //first check if value we are changing to is not 0
    if(x != 0){
    	//if the value is not 0 and the length of the row if 0
    	//all you need to do is prepend the entry with the value
        if (length(tempL) == 0) {
            prepend(tempL, newEntry(j, x));
            M->nnz+=1;
            //increase nnz because we already checked that x is not 0
        }
        else{
        	//if the length of row is not 0 then move cursor to start of row
            moveFront(tempL);
            //move next while the cursor is still defined and the column we are on
            //is less than the column we want to be on
            while (index(tempL) >= 0 && ((Entry)get(tempL))->column < j) {
                moveNext(tempL);
            }
            //if the cursor becomes undefined we just want to add 
            //a new entry to the end 
            if(index(tempL) == -1) {
                append(tempL, newEntry(j, x));
                M->nnz+=1;
                //increment nnz because we already checked that x is not 0
            }
            //if we are at the column we want to be at 
            else if(((Entry)get(tempL))->column == j){
            	//then simply swap the values 
                ((Entry)get(tempL))->value = x;
            }
            //otherwise we need to insert the new entry before where the cursor is 
            else{
                insertBefore(tempL, newEntry(j, x));
                M->nnz+=1;
                //and once again increment nnz
            }
        }
    }
    //if the entry is 0 
    else{
    	//move to the front ot the list
        moveFront(tempL);
        //continue to move next while the cursor is defined and we have yet to 
        //reach the jth column 
        while(index(tempL) >=0 && ((Entry)get(tempL))->column < j) {
            moveNext(tempL);
        }
        //if the cursor is defined then we simply delete the element 
        if(index(tempL) >= 0){
            tempE = (Entry)get(tempL);
            freeEntry(&tempE);
            delete(tempL);
            M->nnz-=1;
            //and decrease the nnz by 1 because we added a 0 so there is one 
            //less nnz entry
        }
    }
}  
    

// Matrix Arithmetic operations

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
   	if (A == NULL) {
        fprintf(stderr, "Matrix | copy() | Calling copy() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    //make another matrix which is what will contain the same entries as A
   	//this matrix must be the same size as the one to be copied
    Matrix B = newMatrix(size(A));
    //make a temp entry object
    Entry tempE;
    //run a for loop that iterates enough times that the size of the matrix is
    for (int i = 1; i < size(A) + 1; i++){
    	//create temp list to store the rows of matrices
        List tempA = A->rows[i];
        List tempB = B->rows[i];
       	//move curosor to begining of row of copy matrix
   		
   		//loop while the index is still defined
   		
   		//append a new entry to the copy Matrix that holds the same value and column as the 
   		//matrix we are copying (A)
   		//continue moving through the list 
        for (moveFront(tempA); index(tempA) >= 0; moveNext(tempA)){
        	//make a temp entry of the data of the temp list 
            tempE = (Entry)get(tempA);
            //append a new entry to the copy Matrix that holds the same value and column as the 
   			//matrix we are copying (A)
            append(tempB, newEntry(tempE->column, tempE->value));
        }
        //continue moving through the list
    }
    B->nnz = A->nnz;
    B->size = A->size;
    return B;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	if(A==NULL){
      printf("Matrix Error: calling transpose() on NULL reference\n");
      exit(EXIT_FAILURE);
   	}
   	Entry tempE = NULL;
   	//create another matrix that will store the transpose of matrix A
   	Matrix T = newMatrix(size(A));
   	//run through for loop that goes through the siz eof the matrix 
   	for(int i = 1; i < size(A) + 1; i ++){
   		//create temp list to store the row of the matrix at i
   		List tempL = A->rows[i];
   		//move cursor to the front of the list and another loop that 
   		//runs wile the cursor is defined and moveNext on list 
   		for(moveFront(tempL);index(tempL) >=0; moveNext(tempL)){
   			//create an entry for the value of the list at row[i]
   			tempE = (Entry)get(tempL);
   			//interchange the entry of the row with the corresponding column and append to 
   			//the list the new entry
        	append(T->rows[tempE->column], newEntry(i, tempE->value));
   		}
   	}
   	//set the number or nnz of the transpose to the same as matrix A
   	T->nnz = A->nnz;
   	return(T);
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if(A==NULL){
      printf("Matrix Error: calling scalarMult() on NULL reference\n");
      exit(EXIT_FAILURE);
   	}
   	//first make a new matrix object 
   	Matrix M = copy(A);
   	//check if you are multiplying by 0 
   	if(x == 0){
   		//if x does equal 0, make everything 0 becuase 0 times anything is 0
   		makeZero(M);
   	}
   	else{
   		//run through a loop the size of the matrix
   		for(int i = 1; i < size(A) + 1; i ++){
   			//create temp list to store the row of the matrix at i
   			List tempL = M->rows[i];
   			//move cursor to the front of the list and run a loop while the index is still defined
   			//cast the value of the row at i to an entry so you can get the value of it
   			for(moveFront(tempL); index(tempL) >= 0; moveNext(tempL)){
   				//then multiply the value by x 
   				Entry e = NULL;
   				e = ((Entry)get(tempL));
   				e->value *= x;
   			}
   		}
   	}
   	return(M);
}


// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling sum() on NULL reference\n");
    	exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling sum() on different sized matrices\n");
    	exit(EXIT_FAILURE);
	}
	//first check if the matrices are the same, then you can use scalar 
	//multiply and multiply one matrix by two to get the sum 
	//we have written the functions for this 
	if(equals(A, B) == 1){
		return(scalarMult(2, A));
	}
    //create a temp Matrix which will be the sum of A+B
	Matrix M = newMatrix(size(A));
	//create a temp List for the matrix we just created
    List tempM;
    //run a for loop that goes through the size of the matrices 
    for(int i = 1; i < size(A)+1; i++){
        tempM = M->rows[i];
        //create temp lists for matrices A and B
        List tempA = A->rows[i];
        List tempB = B->rows[i];
        //move front on the lists of matrices A and B to get the cursor to the beginning
        moveFront(tempA);
        moveFront(tempB);
        //run a loop as long as the indices of the rows are still defined
        while(index(tempA) >= 0 && index(tempB) >= 0){
        	//create temp entries for the rows of matricies A and B 
        	//to get the column and value numbers 
            Entry entA = (Entry)get(tempA);
            Entry entB = (Entry)get(tempB);
            //check if the column of A is less than column of B
            if(entA->column < entB->column){
            	//if so append the new entry with the values of only a's entry
                append(tempM, newEntry(entA->column, entA->value));
                M->nnz+=1;
                //increment the number of nnz entries
                //only move next on A's row
                moveNext(tempA);
            }
            //if it is the opposite then do the opposite
            else if(entA->column > entB->column){
            	//add B's values 
                append(tempM, newEntry(entB->column, entB->value));
                M->nnz+=1;
                //increment the number of nnz entries
                moveNext(tempB);
                //only move next on B's row
            }
            else{
            	//otherwise if the columns are the same them add the values 
            	//and add that as a new entry
                if(entA->value + entB->value != 0){
                    append(tempM, newEntry(entA->column, entA->value + entB->value));
                    M->nnz+=1;
                    //increment the number of nnz entries
                }
                //and move next on BOTH A and B
                moveNext(tempA);
                moveNext(tempB);
            }
        }
        //this is if the index of B is undefined but A is still defined
        while(index(tempA) >= 0){
            Entry entA = (Entry)get(tempA);
            append(tempM, newEntry(entA->column, entA->value));
            M->nnz+=1;
            moveNext(tempA);
            //same steps as before
        }
        //oppposite as above
        while(index(tempB) >= 0){ 
            Entry entB = (Entry)get(tempB);
            append(tempM, newEntry(entB->column, entB->value));
            M->nnz+=1;
            moveNext(tempB);
            //same steps as above
        }
    }
    return M;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling diff() on NULL reference\n");
    	exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling diff() on different sized matrices\n");
    	exit(EXIT_FAILURE);
	}
	//the difference of A-B is just the sum of A+(-B)
	//since we have a function for sum and a function for scalar multiply
	//we can just use these other functions to compute the difference 
    Matrix tempCopy;
    Matrix tempMult;
    Matrix res;
    tempCopy = copy(B);
    tempMult = scalarMult(-1, tempCopy);
    res = sum(A, tempMult);
    freeMatrix(&tempCopy);
    freeMatrix(&tempMult);
    return(res);
}

//vectorDot()
//Helper function for product()
double vectorDot(List P, List Q){
	//create a variable to keep track of the sum
	double finalSum = 0;
    //put cursor at the front of the lists 
    moveFront(P);
    moveFront(Q);
    //run a loop while the indices of the list are still defined 
    while(index(P) != -1 && index(Q) != -1){
    	//create entries of the lists 
    	Entry entP = ((Entry)get(P));
    	Entry entQ = ((Entry)get(Q));
        //if the columns are the same add the multiplication of the 
        //values to the sum total
        if (entP->column == entQ->column){
            finalSum += (entP->value * entQ->value);
            //moveNext on both lists to get to next value 
            moveNext(P); moveNext(Q);
        }
        //you must multiply the corresponding terms from each of the rows
        //so moveNext on the list Q if the column of P is greater than Q
        else if (entP->column > entQ->column){
            moveNext(Q);
        }
        //you must multiply the corresponding terms from each of the rows
        //so moveNext on the list P if the column of Q is greater than P
        else if (entP->column < entQ->column){
            moveNext(P);
        }
    }
    return finalSum;
}


// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling product() on NULL reference\n");
    	exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling product() on different sized matrices\n");
    	exit(EXIT_FAILURE);
	}
	//create a temp variable for the output of helper func vectorDot
	double ans = 0;
	//get the transpose of the Matrix 
	Matrix tempT = transpose(B);
	//create another temp matrix the same size as the matrices given
	Matrix tempM = newMatrix(size(A));
	//run a loop the size of the matrix
	for(int i = 1; i < size(A) + 1; i++){
		//create lists that store the rows of the matrices at i
		List listM = tempM->rows[i];
		List listA = A->rows[i]; 
		//created a nested loop running through the same size as well
		//make sure the list length is not 0, because the list needs to be of 
		//some length to be able to product the values 
		if(length(listA) != 0){
			for(int j = 1; j < size(A) + 1; j++){
			//create another temp list to store the rows of transpose matrix at j
				List listT = tempT->rows[j];
				if(length(listT) != 0){
					ans = vectorDot(listA, listT);
					//add an entry of the product of the rows to the new matrix created 
					//if the sum is not 0
					if(ans != 0){
						append(listM, newEntry(j, ans));
               			//increase the number of nnz because a new entry was created 
               			//which was not 0, since we checked that condition with if statement
               			tempM->nnz++;
					}
				}
			}
		}
	}
	freeMatrix(&tempT);
	return tempM;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if(M==NULL){
      printf("Matrix Error: calling printMatrix() on NULL reference\n");
      exit(EXIT_FAILURE);
   	}
   	//run a for loop that for the size of the matrix 
   	for(int i=1; i < size(M) + 1; i++){
   		//make sure the length of the row at i is not equal to 0
    	if(length(M->rows[i]) != 0){
        	fprintf(out, "%d:", i);
        	//move cursor to the front of the row
        	moveFront(M->rows[i]);
        	//run through a loop while the index is still defined and print out 
        	//the matrix column and value numbers
         	while(index(M->rows[i]) >= 0){
         		//when printing out the values format to one decimal point and cast 
         		//the value of the temp list to an Entry to be able to obtain the 
         		//value and column of it 
            	fprintf(out, " (%d, %0.1f)",
            	((Entry)get(M->rows[i]))->column, ((Entry)get(M->rows[i]))->value);
            	//continue moving through the list until the index becomes undefined (no more values to print)
            	moveNext(M->rows[i]);
         	}
         	fprintf(out, "\n");
      	}
   	}
}
