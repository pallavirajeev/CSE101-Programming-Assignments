//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa5
// Shuffle.cpp
// Client of List ADT
//-----------------------------------------------------------------------------

#include "List.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

void shuffle(List& D){
    //declare variables
    List A, B;
    int n = D.length();

    //start at the front of D and then split D into its two halves 
    D.moveFront();
    for(int i = 0; i < n / 2; i++){
        int x = D.moveNext();
        A.insertBefore(x);
    }

    while(D.position() < n){
        int y = D.moveNext();
        B.insertBefore(y);
    }

    //clear D then move to the front of A and B (the two halves)
    D.clear();
    A.moveFront();
    B.moveFront();

    //add the shuffled A and B into D
    while(B.position() < B.length()){
        int x = B.moveNext();
        D.insertBefore(x);

        if(A.position() < A.length()){
            int y = A.moveNext();
            D.insertBefore(y);
        }
    }
}

int main(int argc, char* argv[]){
    //if there are not two arguments then throw an error
    if(argc != 2){
        throw std::invalid_argument("Incorrect number of arguments. Usage: Shuffle <max>");
    }

    //throw an error if you don't have a positive number of cards
    int max = std::stoi(argv[1]);
    if(max <= 0){
        throw std::invalid_argument("Invalid argument. Maximum number of cards must be a positive integer.");
    }

    //this prints out the header how the documentation wants us to 
    std::cout << "deck size\tshuffle count" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    //run a loop for the max number of cards 
    for(int n = 1; n <= max; n++){
        List deck;
        int count = 0;

        deck.moveBack();
        for(int i = 0; i < n; i++){
            deck.insertBefore(i);
        }

        List original = deck;

        //call shuffle while the two decks are not equal
        //you want to bring the list back to the original order
        do{
            shuffle(deck);
            //count the number of shuffles as you go 
            count++;
        }while(!(deck == original));


        //print a table to standard output giving this count, for each
        //value of n 
        std::cout << std::setw(10) << std::left << n << count << std::endl;
    }

    return 0;
}
