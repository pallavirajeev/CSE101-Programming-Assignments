//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa8
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string S[] =   { // words to insert
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };
   string T[] =   { // words to delete
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",      
                  };

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }
   
   // call operator=()
   B = A;

   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);

   // call copy constructor
   Dictionary C = B;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check copy constructor
   cout << "copy constructor creates identical trees: " << endl;
   cout << ((C.pre_string()==B.pre_string())?"true":"false") << endl;
   cout << endl; 


   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl;
   A.getValue("hemiolia") *= 10; // change the value associated with "hemiolia"
   cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // remove some pairs from A
   for(int i=0; i<13; i++){ 
      A.remove(T[i]);
   }

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // do forward iteration on B
   cout << "forward iteration on B, changing values:" << endl;
   for(B.begin(); B.hasCurrent(); B.next()){
      cout << "("+B.currentKey()+", " << B.currentVal() << ") ";
      B.currentVal()++;  // change value
      cout << "("+B.currentKey()+", " << B.currentVal() << ")\n";
   }
   cout << endl;

   // do reverse iteration on C
   cout << "reverse iteration on C, changing values" << endl;
   for(C.end(); C.hasCurrent(); C.prev()){
      cout << "("+C.currentKey()+", " << C.currentVal() << ") ";
      C.currentVal()++;  // change value
      cout << "("+C.currentKey()+", " << C.currentVal() << ")\n";
   }
   cout << endl;
   
   // check exceptions
   cout << "test pre-condition errors:" << endl;
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << endl;  

   //more tests (test each function at least twice)
    Dictionary dict1;
    Dictionary dict2;

    dict1.setValue("apple", 5);
    dict1.setValue("orange", 3);
    dict1.setValue("banana", 7);

    dict2.setValue("grape", 2);
    dict2.setValue("pear", 4);
    dict2.setValue("kiwi", 6);

    //size() 
    cout << "Size of dict1: " << dict1.size() << endl;
    cout << "Size of dict2: " << dict2.size() << endl;

    //contains() 
    cout << "Does dict1 contain 'apple'? " << (dict1.contains("apple") ? "Yes" : "No") << endl;
    cout << "Does dict2 contain 'banana'? " << (dict2.contains("banana") ? "Yes" : "No") << endl;

    //getValue() 
    if(dict1.contains("apple")){
        valType& value1 = dict1.getValue("apple");
        cout << "Value of 'apple' in dict1: " << value1 << endl;
    } 
    else{
        cout << "Key 'apple' not found in dict1." << endl;
    }

    if(dict2.contains("banana")){
        valType& value2 = dict2.getValue("banana");
        cout << "Value of 'banana' in dict2: " << value2 << endl;
    } 
    else{
        cout << "Key 'banana' not found in dict2." << endl;
    }

    //hasCurrent() 
    cout << "Is current iterator defined in dict1? " << (dict1.hasCurrent() ? "Yes" : "No") << endl;
    cout << "Is current iterator defined in dict2? " << (dict2.hasCurrent() ? "Yes" : "No") << endl;

    //currentKey() 
    if(dict1.hasCurrent()){
        keyType key1 = dict1.currentKey();
        cout << "Current key in dict1: " << key1 << endl;
    } 
    else{
        cout << "No current key in dict1." << endl;
    }

    if(dict2.hasCurrent()){
        keyType key2 = dict2.currentKey();
        cout << "Current key in dict2: " << key2 << endl;
    } 
    else{
        cout << "No current key in dict2." << endl;
    }

    //currentVal() function
    if(dict1.hasCurrent()){
        valType& value1 = dict1.currentVal();
        cout << "Current value in dict1: " << value1 << endl;
    } 
    else{
        cout << "No current value in dict1." << endl;
    }

    if(dict2.hasCurrent()){
        valType& value2 = dict2.currentVal();
        cout << "Current value in dict2: " << value2 << endl;
    } 
    else{
        cout << "No current value in dict2." << endl;
    }

    //clear()
    dict1.clear();
    dict2.clear();

    cout << "Size of dict1 after clear(): " << dict1.size() << endl;
    cout << "Size of dict2 after clear(): " << dict2.size() << endl;

   cout << "Test complete!" << endl;

   return( EXIT_SUCCESS );
}