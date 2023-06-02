//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa7
// Dictionary.cpp
// Function Definitions
//-----------------------------------------------------------------------------
#include "Dictionary.h"
#include<iostream>
#include<string>


// Class Constructors & Destructors ----------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

Dictionary::Dictionary(){
	nil = new Node("\0", -1);
    root = nil;
   	current = nil;
   	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("\0", -1);
    root = nil;
   	current = nil;
   	num_pairs = 0;
   	preOrderCopy(D.root, D.nil);

}

// Destructor
Dictionary::~Dictionary(){
	//clear then delete
	clear();
	delete nil;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if(R != nil){
		inOrderString(s,R->left);
    	s.append(R->key);
    	s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
    	inOrderString(s,R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
    	s.append(R->key);
    	s.append("\n");
    	preOrderString(s, R->left);
    	preOrderString(s, R->right);
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
		if(R != N){
    	setValue(R->key, R->val);
    	preOrderCopy(R->left, N);
    	preOrderCopy(R->right, N);
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
		if(R != nil){
    	postOrderDelete(R->left);
    	postOrderDelete(R->right);
    	R->parent = nullptr;
    	R->left = nullptr;
    	R->right = nullptr;
    	delete R;
    	num_pairs -= 1;
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if(R == nil || k == R->key){
		return R;
	}
   	else if(k < R->key){
   		return search(R->left, k);
   	}
   	else{ // k > x.key
      return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if(R == nil){
        throw std::logic_error("Dictionary: findMin(): subtree given is rooted at nil");
    }

	while(R->left != nil){
    	R = R->left;
	}
   return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if(R == nil){
        throw std::logic_error("Dictionary: findMax(): subtree given is rooted at nil");
    }
	while(R->right != nil){
    	R = R->right;
	}
   return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	if(N->right != nil){
		return findMin(N->right); // case 1
   	}
   	Node * y = N->parent;                   
   	while(y != nil && N == y->right){ // case 2
   		N = y;
      	y = y->parent;
   	}
   	return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	if(N->left != nil){
		return findMax(N->left); // case 1
   	}
   	Node * y = N->parent;                   
   	while(y != nil && N == y->left){ // case 2
   		N = y;
      	y = y->parent;
   	}
   	return y;
}

void Dictionary::transplant(Node* u, Node* v){
   	if(u->parent == nil){
    	root = v;
   	}
   	else if(u == u->parent->left){
    	u->parent->left = v;
   	}
   	else{  
    	u->parent->right = v;
    }
   	if(v != nil){
    	v->parent = u->parent;
   	}
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
	if(search(root, k) == nil){
		return false;
	}
	return true;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    Node *N = search(root, k);
    if(N == nil){ //pre of containing k not met 
		throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
	return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
	if(current == nil || current == nullptr){
		return false;
		//undefined
	}
	return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(hasCurrent() == false) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(hasCurrent() == false) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }

	return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
	//set everything to nil/0
   	postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
	Node* a = root;
	Node* b = nil;
	while(a != nil){
    	if(k == a->key){
        	// Key already exists, update the value and return
        	a->val = v;
        	return;
    	}
    	b = a;
    	if(k < a->key){
        	a = a->left;
    	}
    	else{
        	a = a->right;
    	}
	}
	// Create a new node since the key doesn't exist
	Node* c = new Node(k, v);
	c->left = nil;
	c->right = nil;
	c->parent = b;
	if(b == nil){
    	root = c;
	} 
	else if(k < b->key){
    	b->left = c;
	} 
	else{
    	b->right = c;
	}
	num_pairs++; 
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if(contains(k) == false){
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }

    Node* N = search(root, k);

    if(N == current){
        current = nil;
    }

	if(N->left == nil){               	// case 1  or case 2.1 (right only)
      transplant(N, N->right);
    }
   	else if(N->right == nil){         	// case 2.2 (left only)
      transplant(N, N->left);
    }
   	else{                          		// case 3
      	Node *y = findMin(N->right);
      	if(y->parent != N){
        	transplant(y, y->right);
        	y->right = N->right;
        	y->right->parent = y;
        }
      	transplant(N, y);
      	y->left = N->left;
      	y->left->parent = y;
    }
    num_pairs--;
    delete N;
}	

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
	//make sure non-empty
	if(num_pairs > 0){
		current = findMin(root);
	}
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
	//make sure non-empty
	if(num_pairs > 0){
		current = findMax(root);
	}
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: next(): current not defined");
    }
    // Check if not at the last pair
    if (findNext(current) != nil) {
        // Advance to next pair
        Node* N = findNext(current);
        current = N;
    } 
    else{
        // Current is already at the last pair, make it undefined
        current = nil;
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(hasCurrent() == false){
        throw std::logic_error("Dictionary: prev(): current not defined");
    }
    // Check if not at the first pair
    if(findPrev(current) != nil){
        // Advance to previous pair
        Node* N = findPrev(current);
        current = N;
    } 
    else{
        // Current is already at the first pair, make it undefined
        current = nil;
    }
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
	//use helper function
	std::string res = "";
	this->inOrderString(res,this->root);
	return res;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
	//use helper function
	std::string res = "";
	this->preOrderString(res,this->root);
	return res;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
	//if not the same size, cannot be equal 
	if(this->num_pairs != D.num_pairs){
		return false;
	}
	std::string tempA, tempB;
    tempA = this->to_string();
    tempB = D.to_string();
    if(tempA == tempB){
        return true;
    }
    return false;
	//FIX MAYBE??
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
	if(this != &D ){ // not self assignment
    	// make a copy of L
      	Dictionary temp = D;
      	// then swap the copy's fields with fields of this
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
   	}
   	// return this with the new data installed
   	return *this;
   	// the copy, if there is one, is deleted upon return
}



