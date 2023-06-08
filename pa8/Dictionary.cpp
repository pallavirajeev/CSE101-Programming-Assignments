//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa8
// Dictionary.cpp
// Function Definitions
//-----------------------------------------------------------------------------
#include "Dictionary.h"
#include<iostream>
#include<string>

#define RED -1
#define BLACK -2

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
	nil = new Node("\0", -1);
	nil->color = BLACK;
    root = nil;
   	current = nil;
   	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    //std::cout << "in copy " << std::endl;
	nil = new Node("\0", -1);
	nil->color = BLACK;
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
// string will consist of keys only, with the order determined by a pre-order
// tree walk. The keys stored in black Nodes will be appended as "key\n", and
// the keys stored in red Nodes will be appended as "key (RED)\n". The output 
// of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        if(R->color == BLACK){
            s.append(R->key);
            s.append("\n");
        } 
        else{
            s.append(R->key);
            s.append(" (RED)\n");
        }
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
} 

// BST_insert()
// Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
void Dictionary::BST_insert(Node* M){
    Node* a = root;
    Node* b = nil;
    while(a != nil){
        if(M->key == a->key){
            // Key already exists, update the value and return
            a->val = M->val;
            //delete M;
            return;
        }
        b = a;
        if(M->key < a->key){
            a = a->left;
        }
        else{
            a = a->right;
        }
    }
    M->parent = b;
    M->left = nil;
    M->right = nil;
    if(b == nil){
        root = M;
    } 
    else if(M->key < b->key){
        b->left = M;
    } 
    else{
        b->right = M;
    }
    num_pairs++;

}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R != N){
        Node * temp = new Node(R->key, R->val);
        temp->color = R->color;
        BST_insert(temp);
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

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
	// set y
  	Node* y = N->right;
   	// turn y's left subtree into x's right subtree
   	N->right = y->left;
   	if(y->left != nil){    // not necessary if using sentinal nil node
    	y->left->parent = N;
   	}
   	// link y's parent to x
   	y->parent = N->parent;
   	if(N->parent == nil){
    	root = y;
   	}
   	else if(N == N->parent->left){
    	N->parent->left = y;
   	}
   	else{ 
    	N->parent->right = y;
   	}
   	// put x on y's left
   	y->left = N;
   	N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
	// set y
	Node* y = N->left;
   	// turn y's right subtree into x's left subtree
   	N->left = y->right;
   	if(y->right != nil){  // not necessary if using sentinal nil node
    	y->right->parent = N;
   	}
   	// link y's parent to x
   	y->parent = N->parent;
   	if(N->parent == nil){
    	root = y;
   	}
   	else if(N == N->parent->right){
    	N->parent->right = y;
   	}
   	else{
    	N->parent->left = y;
   	}
   	// put x on y's right
   	y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
   	while(N->parent != nil && N->parent->color == RED){
      	if(N->parent == N->parent->parent->left){
        	Node* y = N->parent->parent->right;
        	if(y->color == RED){
            	N->parent->color = BLACK;              		// case 1
            	y->color = BLACK;                    		// case 1
            	N->parent->parent->color = RED;         	// case 1
            	N = N->parent->parent;                 		// case 1
            }

         	else{ 
            	if(N == N->parent->right){
               		N = N->parent;                     		// case 2
               		LeftRotate(N);                 			// case 2
               	}
            	N->parent->color = BLACK;              		// case 3
            	N->parent->parent->color = RED;         	// case 3
            	RightRotate(N->parent->parent);			    // case 3
            }
        }
      	else{
        	Node* y = N->parent->parent->left;
        	if(y->color == RED){
            	N->parent->color = BLACK;              		// case 4
            	y->color = BLACK;                     		// case 4
            	N->parent->parent->color = RED;         	// case 4
            	N = N->parent->parent;                 		// case 4
            }
         	else{
            	if(N == N->parent->left){
               		N = N->parent;                     		// case 5
               		RightRotate(N);                			// case 5
               	}
            	N->parent->color = BLACK;              		// case 6
            	N->parent->parent->color = RED;         	// case 6
            	LeftRotate(N->parent->parent);		      	// case 6
            }	
        }
    }
   	root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
	if(u->parent == nil){
    	root = v;
	}
   	else if(u == u->parent->left){
    	u->parent->left = v;
   	}
   	else{ 
    	u->parent->right = v;
    }
   	v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
   	while(N != root && N->color == BLACK){
    	if(N == N->parent->left){

        	Node* w = N->parent->right;
        	if(w->color == RED){

            	w->color = BLACK;                        				// case 1
            	N->parent->color = RED;                   				// case 1
            	LeftRotate(N->parent);                					// case 1
            	w = N->parent->right;                     				// case 1
            }
         	if(w->left->color == BLACK && w->right->color == BLACK){

            	w->color = RED;                          					// case 2
            	N = N->parent;                           					// case 2
            }

         	else{ 

            	if(w->right->color == BLACK){

               		w->left->color = BLACK;                			// case 3
               		w->color = RED;                       			// case 3
               		RightRotate(w);                   				// case 3
               		w = N->parent->right;                  			// case 3
               	}
            	w->color = N->parent->color;               				// case 4
            	N->parent->color = BLACK;                 				// case 4
            	w->right->color = BLACK;                			 	// case 4
            	LeftRotate(N->parent);                				// case 4
            	N = root;                             				// case 4
            }
      	}
      	else{ 

        	Node* w = N->parent->left;
        	if(w->color == RED){
            	w->color = BLACK;                        				// case 5
            	N->parent->color = RED;                   				// case 5
            	RightRotate(N->parent);               					// case 5
            	w = N->parent->left;                     				// case 5
            }
         	if(w->right->color == BLACK && w->left->color == BLACK){

            	w->color = RED;                          				// case 6
            	N = N->parent;                           				// case 6
            }
         	else{ 
            	if(w->left->color == BLACK){
               		w->right->color = BLACK;               			// case 7
               		w->color = RED;                       			// case 7
               		LeftRotate(w);                    				// case 7
               		w = N->parent->left;                   			// case 7
               	}
            	w->color = N->parent->color;               			// case 8
           		N->parent->color = BLACK;                			// case 8
            	w->left->color = BLACK;                   			// case 8
            	RightRotate(N->parent);               				// case 8
            	N = root;                             				// case 8
        	}
        }
    }
   	N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* X;
    Node* Y = N;
    int save = Y->color;
    if (N->left == nil) {
        X = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil) {
        X = N->left;
        RB_Transplant(N, N->left);
    }
    else {
        Y = findMin(N->right);
        save = Y->color;
        X = Y->right;
        if (Y->parent == N) {
            X->parent = Y;
        }
        else {
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }
    if (save == BLACK) {
        RB_DeleteFixUp(X);
    }
    delete N;
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
	//std::cout << "in sv" << std::endl;

	Node* a = root;
    Node* b = nil;
    // Search for the key in the tree
    while (a != nil && a->key != k) {
        b = a;
        if(k < a->key){
            a = a->left;
        } 
        else{
            a = a->right;
        }
    }
    // Key already exists, update the value
    if (a != nil) {
        a->val = v;
    }
    // Key doesn't exist, insert a new pair
    else {
        Node* c = new Node(k, v);
        c->left = nil;
        c->right = nil;
        c->color = RED;
        c->parent = b;
        // Set parent link for the new node
        if (b == nil) {
            root = c;
        } else if (k < b->key) {
            b->left = c;
        } else {
            b->right = c;
        }

        // Perform any necessary fix-ups after insertion
        RB_InsertFixUp(c);

        // Increase the size of the dictionary
        num_pairs++;
    }
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
    RB_Delete(N);
    num_pairs--;
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


