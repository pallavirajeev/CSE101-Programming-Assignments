//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa6
// ListTest.cpp
// Testing file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=10;
   List A, B, C, D;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B << endl;
   cout << B.position() << endl;
   cout << endl;
   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;
   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;

   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   //test for all functions in List.cpp

   A.clear();
   B.clear();   

   A.insertBefore(1);
   A.insertBefore(2);
   cout << "position()" << A.position() << endl;
   A.insertAfter(2);
   A.moveNext();
   cout << A << endl;
   cout << "position()" << A.position() << endl;
   A.insertBefore(2);
   A.insertAfter(4);
   A.eraseAfter();
   cout << "peekPrev: " << A.peekPrev() << endl;
   cout << "length(): " << A.length() << endl;
   A.front();
   cout << A << endl;

   B.insertBefore(1);
   B.insertBefore(2);
   B.insertBefore(2);
   B.movePrev();
   cout << "position()" << B.position() << endl;
   B.setAfter(2);
   B.insertBefore(1);
   B.insertBefore(2);
   cout << "position()" << B.position() << endl;
   B.insertAfter(3);
   cout << B << endl;
   B.eraseBefore();
   B.insertAfter(5);
   B.insertBefore(3);
   B.insertBefore(1);
   cout << "peekNext: " << B.peekNext() << endl;
   cout << B.findPrev(3) << endl;
   B.movePrev();
   B.cleanup();
   cout << "position()" << B.position() << endl;
   B.back();
   cout << B << endl;
   B = A;
   cout << "B==A is " << (B==A?"true":"false") << endl;
   B.concat(A);
   cout << B << endl;

   A.clear();
   A.insertBefore(3);
   A.insertBefore(7);
   A.insertAfter(4);
   cout << "position()" << A.position() << endl;
   A.insertBefore(6);
   cout << A << endl;
   A.moveNext();
   A.insertBefore(1);
   A.insertBefore(4);
   A.setBefore(11);
   cout << "position()" << A.position() << endl;
   A.insertBefore(2);
   A.insertAfter(4);
   A.insertBefore(5);
   A.movePrev();
   cout << "position()" << A.position() << endl;
   A.insertBefore(6);
   A.front();
   cout << A.findPrev(10) << endl;
   cout << "position()" << A.position() << endl;
   A.moveBack();
   cout << A.findPrev(7) << endl;
   cout << A.findPrev(6) << endl;
   cout << A.findPrev(2) << endl;
   A.moveBack();
   cout << "position()" << A.position() << endl;
   A.cleanup();
   cout << "position()" << A.position() << endl;
   A.back();
   cout << "position()" << A.position() << endl;
   cout << A.findPrev(1) << endl;
   cout << A.findPrev(1) << endl;
   cout << "peekNext: " << A.peekNext() << endl;
   cout << A << endl;
   cout << "My Tests Complete!" << endl;

   return( EXIT_SUCCESS );
}

