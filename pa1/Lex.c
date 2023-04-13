//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa1
// Lex.c
// Main program for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX 150

int main(int argc, char * argv[]){
	//delcare or initialize variables 
	int ctrLine = 0;
	FILE *in;
	FILE *out;
	char line[MAX];
	

	//check if there are the correct number of arguments (2)
	if(argc != 3){
		fprintf(stderr, "usage: Lex <input file> <output file>\n");
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
	
	while(fgets(line, MAX, in) != NULL){
		ctrLine +=1; //increase ctr for each line of file 
	} 

	rewind(in);

	//array the size of the number of lines in the file 
	char ** arr = malloc((ctrLine) * sizeof(char*));
	for(int i = 0; i < ctrLine; i++){
		//allocate space enough for each of the lines in the file
        arr[i] = malloc((MAX)*sizeof(line));
	}
	int temp = 0;
	while (fgets(line, sizeof(line), in) != NULL){
	 	strcpy(arr[temp],line);
	 	temp+=1;
	 }
    

	List copyL = newList();
	append(copyL, 0); //start off by appending 0 then seeing where to insert the rest 
	for(int j = 1; j < ctrLine; j++){ //start at 1 since 0 is already appended
		moveFront(copyL);
		int marker = j ; //marker to keep track of movement 
		while(marker > 0 && strcmp(arr[j], arr[get(copyL)]) >= 0){
			moveNext(copyL);
			marker -= 1;
		}
		if(index(copyL) >= 0){
			insertBefore(copyL, j);
		}
		else{
			append(copyL,j);
		}
	}
	moveFront(copyL); //after iteration move cursor to the front of the list and cont.

	while(index(copyL) != -1){ //while index is defined print into file 
		fprintf(out, "%s", arr[get(copyL)]);
		moveNext(copyL); //move onto the next string while the index is still defined
	}

	//close the files 
	fclose(in);
	fclose(out);

	//free the List
	freeList(&copyL); 
	//free the array
	for (int i = 0; i < ctrLine; i++)
    {
        free(arr[i]);
    }
    free(arr);

	return(0);
}