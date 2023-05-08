//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa4
// Sparse.c
// Client Program for Matrix ADT
//-----------------------------------------------------------------------------
#include "Matrix.h"
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

	//create a variable for the size and scan it in
    int n = 0;
    fscanf(in, " %d", &n);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // scan first to skip 0 0
    int a, b;
    fscanf(in, " %d", &a);
    fscanf(in, " %d", &b);

    //create variables for row, column, and value and scan those in
    int r, c;
    double v;
    //now fill in the matrices with the respective values 
	//run a loop the size of the the number of nnz of A
    for(int i = 1; i < a+1; i++){
        fscanf(in, " %d", &r); 
        fscanf(in, " %d", &c);
        fscanf(in, " %lf", &v);
        changeEntry(A, r, c, v);
    }
    //now fill in the matrices with the respective values 
	//run a loop the size of the the number of nnz of B
    for(int i = 1; i < b+1; i++){
        fscanf(in, " %d", &r); 
        fscanf(in, " %d", &c);
        fscanf(in, " %lf", &v);
        changeEntry(B, r, c, v);
    }
	//now calculate and print the following matrices to the output file: 𝐴, 𝐵, (1.5)𝐴, 𝐴 + 𝐵, 
	//𝐴 + 𝐴, 𝐵 − 𝐴, 𝐴 − 𝐴, 𝐴^T, 𝐴𝐵 and 𝐵^2

	fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out, A);

	fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
	printMatrix(out, B);

	fprintf(out, "\n(1.5)*A =\n");
	Matrix C = scalarMult(1.5, A);
	printMatrix(out, C);

	fprintf(out, "\nA+B =\n");
	Matrix D = sum(A, B);
	printMatrix(out, D);

	fprintf(out, "\nA+A =\n");
	Matrix E = sum(A, A);
	printMatrix(out, E);

	fprintf(out, "\nB-A =\n");
	Matrix F = diff(B, A);
	printMatrix(out, F);

	fprintf(out, "\nA-A =\n");
	Matrix G = diff(A, A);
	printMatrix(out, G);

	fprintf(out, "\nTranspose(A) =\n");
	Matrix H = transpose(A);
	printMatrix(out, H);

	fprintf(out, "\nA*B =\n");
	Matrix I = product(A, B);
	printMatrix(out, I);

	fprintf(out, "\nB*B =\n");
	Matrix J = product(B, B);
	printMatrix(out, J);

	//close files
    fclose(in);
    fclose(out);

    //free memory
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

    return 0;

}



