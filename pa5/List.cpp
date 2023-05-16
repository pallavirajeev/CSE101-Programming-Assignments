//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa5
// List.cpp
// Implementation of List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Node constructor
List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List(){
    frontDummy = new Node(-1);
    backDummy = new Node(-2);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
   	beforeCursor = frontDummy;
   	afterCursor = backDummy;
   	pos_cursor = 0;
   	num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
	frontDummy = new Node(-1);
    backDummy = new Node(-2);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
   	beforeCursor = frontDummy;
   	afterCursor = backDummy;
   	pos_cursor = 0;
   	num_elements = 0;

   	Node* N = L.frontDummy->next;
   	while( N!=L.backDummy){
      this->insertBefore(N->data);
      N = N->next;
   	}
   moveFront();
}

// Destructor
List::~List(){
	//when destructing you want to clear then free all the memory
	clear();
	//instead of malloc/free we use new/delete
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if(num_elements==0 ){
      throw std::length_error("List: front(): empty List");
   	}
   	return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if(num_elements==0 ){
      throw std::length_error("List: back(): empty List");
   	}
   	return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	if(pos_cursor < 0 || pos_cursor > length()){
		std::cout << length() << std::endl;
		std::cout << pos_cursor << std::endl;
      throw std::range_error("List: position(): out of range ");
   	}
   	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	if(pos_cursor >= length()){
      throw std::range_error("List: peekNext(): out of range");
   	}
   	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if(pos_cursor <= 0){
      throw std::range_error("List: peekPrev(): out of range");
   	}
   	return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	moveFront();
	while(num_elements > 0){
		eraseAfter();
	}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
	afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = length();
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
	if(position() >= length()){
      throw std::range_error("List: moveNext(): out of range");
   	}
   	//set cursors to the next element and increase the position of the cursor by 1
   	beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;
    //this is the element passed over, return it
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if(position() <= 0){
    	throw std::range_error("List: movePrev(): out of range");
   	}
   	//set cursors to the prev element and decrease the position of the cursor by 1
   	beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    //this is the element passed over, return it
    return afterCursor->data;
}


// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
	//first create a temp node with x
	Node *temp = new Node(x);
	//make node's previous the beforeCursor
	//then the beforeCursors next can be the temp node
    temp->prev = beforeCursor;
    beforeCursor->next = temp;
    //do the vice versa with the node's next and 
    //afterCursor
    temp->next = afterCursor;
    afterCursor->prev = temp;
    //the afterCursor then becomes next because
    //you are inserting x after the cursor
    afterCursor = temp;
    //this increases the number of elements 
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	//first create a temp node with x
	Node *temp = new Node(x);
	//make node's previous the beforeCursor
	//then the beforeCursors next can be the temp node
    temp->prev = beforeCursor;
    beforeCursor->next = temp;
    //do the vice versa with the node's next and 
    //afterCursor
    temp->next = afterCursor;
    afterCursor->prev = temp;
    //the beforeCursor then becomes next because
    //you are inserting x before the cursor
    beforeCursor = temp;
    //this increases the number of elements 
    num_elements++;
    //the position also increases because
    //you are inserting before 
    pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if(position() >= length()){
    	throw std::range_error("List: setAfter(): out of range");
   	}
   	//this gets the element after the cursor, then sets it to x
   	afterCursor->next->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if(position() <= 0){
    	throw std::range_error("List: setBefore(): out of range");
   	}
   	//this gets the element before the cursor, then sets it to x
   	beforeCursor->prev->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if(position() >= length()){
    	throw std::range_error("List: eraseAfter(): out of range");
   	}
   	//create a temp node for element after the cursor
   	//this is what you will end up deleteting 
   	Node *temp = afterCursor;
   	beforeCursor->next = afterCursor->next;
   	temp->next->prev = beforeCursor;
   	//set the after cursor to the next of the temp node 
   	//because temp will be deleted and it's next is the new after
   	afterCursor = temp->next;
   	//then delete temp
   	delete temp;
   	//and decrease the number of elements
   	num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if(position() <= 0){
    	throw std::range_error("List: eraseBefore(): out of range");
   	}
   	//create a temp node for element after the cursor
   	//this is what you will end up deleteting 
   	Node *temp = beforeCursor;
   	//set the beforeCursor as its previous 
   	beforeCursor = beforeCursor->prev;
   	afterCursor->prev = beforeCursor;
   	//set the before cursor's next to be after cursor because 
   	//the afterCursor is not the next beforeCursor's elm
   	beforeCursor->next = afterCursor;
   	//then delete temp
   	delete temp;
   	//and decrease the number of elements
   	num_elements--;
   	//and decrease the pos_cursor because we are erasing before the cursor
   	pos_cursor--;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
	//create a boolean to keep track of if you found elm
	bool flag = false;
	//create a temp node which is the afterCursor because you 
	//are searching from the cursor from the front to back
    Node *temp = afterCursor;
    //next run a loop while item is still not found and the
    //temp node is not the backDummy
    while(flag == false && temp != backDummy){
    	//update the boolean depending on if the element is equat to the
    	//element you are searching for, x
        flag = (temp->data == x);
        //if the bool is still false then you want to 
        //move onto the next element
        if(flag == false) {
            temp = temp->next;
        }
        //increase the position of the cursor 
        pos_cursor++;
    }
    //whatever temp is now, the afterCursor becomes the next of temp
    afterCursor = temp->next;
    //and the before cursor becomes temp
    beforeCursor = temp;
    //make sure to return the position of where x was found, if found
    if(flag == true){
        return pos_cursor;
    }
    //if the element x is nowhere to be found, -1 is returned
    else{
        return -1;
    }
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
//at position 0, and returns -1. 
int List::findPrev(ListElement x){
	//move cursor to previous element and compare it with 'x'.
    //and if the element is found or the pos_cursor becomes 0, the loop will exit
    while (pos_cursor > 0 && movePrev() != x) {

    }
    //check if the element was found or not,
    //if it wasn't found pos_cursor would be 0 and not
    //enter this if statment 
    if (pos_cursor > 0) {
        //if element found return pos_cursor
        return pos_cursor;
    } else {
    	//place cursor at pos 0 
    	moveFront();
        //and return -1 if not found
        return -1;
    }

}



// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
	//create temp nodes
    Node *temp1 = nullptr;
    Node *temp2 = nullptr;
    Node *tempCur = frontDummy->next;
	//run a while loop while the current node elm doesn't reach 
	//the end (backDummy)
	//variable for pos for the outer loop
	int pos = 1;

    while(tempCur != backDummy){
    	//set one of the temp nodes to the current node elm
        temp1 = tempCur;
        //and the other to the next of that node
        temp2 = tempCur->next;
        //then have a nested loop while the next of the node doesn't 
        //reach the end (backDummy)
        //another var for pos but for the inner loop
        int tempPos = pos + 1;
        while(temp2 != backDummy){
        	//check if the current node elm's data is the same
        	//as the other next elms data
            if(tempCur->data == temp2->data){
                //if they are equivalent then you need 
                //get rid of it to cleanup code
                //first make the tempCur stored in temp1's next and 
                //set it equal to the tempCur's nexts next
                temp1->next = temp2->next;
                //then set temp cur's nexts next prev to temp1
                temp2->next->prev = temp1;
                // Check if beforeCursor needs to be updated
                if(beforeCursor == temp2){
                    beforeCursor = temp1;
                }
                // Check if afterCursor needs to be updated
                if(afterCursor == temp2){
                    afterCursor = temp2->next;
                }
                //then you can delete temp2 which is the repeat elm
                delete temp2;
                //then temp2 becomes the next of temp1 because temp2 is deleted 
                //since it was a repeat so you need to move on to the next elm
                temp2 = temp1->next;
                //since you deleted a repeat elm the number of elements must 
                //be decreased
                num_elements--;
                //then check from where exactly the elm was deleted 
                //this is why we have a tempPos variable to know 
                //where in the list we deleted an elm, relative to the 
                //position of the cursor 
                if(pos_cursor >= tempPos){
                	pos_cursor--;
                }
            }
            //if the elm data is not the same and you haven't found a repeat yet
            else {
            	//temp1 becomes temp2
                temp1 = temp2;
                //and temp2 becomes the next of temp1
                temp2 = temp1->next;
                //increase the inner loop temp pos var
                tempPos++;                
            }
        }
        //if you reach the end with temp2
        //then move to the next elm of tempCur and 
        //continue cleaning up the code
        tempCur = tempCur->next;
        //increase the outer loop temp pos var
        pos++;
    }
}


// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
	List J;
   	Node* N = this->frontDummy->next;
   	Node* M = L.frontDummy->next;
   	while(N->data >= 0){
    	J.insertBefore(N->data);
    	N = N->next;
    }
    while(M->data >= 0){
    	J.insertBefore(M->data);
    	M = M->next;
    }
    J.moveFront();
    return J;
} 

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	Node* N = nullptr;
    std::string s = "(";
    for(N=frontDummy->next; N!= backDummy->prev; N=N->next){
    	s += std::to_string(N->data)+ ", ";
   	}
   	s+= std::to_string(N->data);
   	s+= ")";
   return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;
    eq = ( this->num_elements == R.num_elements);
    N = this->frontDummy;
    M = R.frontDummy;
    while(eq && N!=nullptr){
    	eq = (N->data==M->data);
    	N = N->next;
    	M = M->next;
   	}
   	return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
	 return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	if(this != &L ){ // not self assignment
    	// make a copy of L
      	List temp = L;

      	// then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
   	}

   	// return this with the new data installed
   	return *this;
   	// the copy, if there is one, is deleted upon return
}



