//-----------------------------------------------------------------------------
// Pallavi Rajeev
// prajeev
// pa6
// BigInteger.cpp
// Implementation of BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include<ctype.h>
#include"BigInteger.h"

#define BASE 1000000000
#define POWER 9
//these must be set to these values by the end but can be changed during testing

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;
	digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
	//check the sign on the number
	//you must check if it is 1, -1, or 0 and 0 is a special case so you
	//since the list digits is to be empty 
	if(x > 0){
		signum = 1;
	}
	else if(x < 0){
		signum = -1;
	}
	//else it is 0 so you make empty list 
	else{
		signum = 0;
		digits = List();
		digits.insertAfter(0);
		return;
	}

	//if it is not 0 then digits is not an empty list 
	digits = List();

	//then add to the list 
	while(x != 0){
		//remainder as a digit
		digits.insertAfter(x % BASE); 
		//divide x by base 
    	x /= BASE; 
	} 
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	if(s.length() <= 0){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	//check if there is a sign for the digit
	if(s[0] == '-'){
        signum = -1;
        //take out the sign
        s.erase(0,1);
    }
    else if(s[0] == '+'){
        signum = 1;
        //take out the sign
        s.erase(0,1);
    }
    else{
        signum = 1;
    } 
    //now check if the rest of the string is all digits
     for (size_t i = 0; i < s.length(); i++) {
        if (!std::isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    //if everything is a digit then add it to digits
    //first make sure digits is empty 
    int n = s.length();
    long temp;
    digits.clear();
    while(n > 0){
    	if(n > POWER){
    		//convert to a long
    		temp = std::stol(s.substr(n-POWER,POWER));
    	}
    	else{
    		temp = std::stol(s.substr(0,n));
    	}
    	//add this to digits
    	//123456
    	digits.insertAfter(temp);
    	n = n - POWER;
	}
	digits.moveFront();
	while(digits.position() < digits.length() && digits.peekNext() == 0){
    	digits.eraseAfter();
	}
}//IS THIS RIGHT??

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	signum = N.signum;
	digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	if(signum > N.signum){
		return 1;
	}
	else if(signum < N.signum){
		return -1;
	}
	else if(signum == 0 && N.signum == 0){
		return 0;
	}
	//logic for if they are equal, then you must compare the digits 
	//first create two temp lists
	List temp1 = digits;
	List temp2 = N.digits;

	//first case: both positive
	if(signum == 1 && N.signum == 1){
		//check if one is longer than the other because that means
		//the longer is automatically larger and you can stop checking
		if(temp1.length() > temp2.length()){
			return 1;
		}
		else if(temp1.length() < temp2.length()){
			return -1;
		}
		else{
			//otherwise they are not the same length and you have to start 
			//checking the digits
			for(temp1.moveFront(), temp2.moveFront(); temp1.position() < temp1.length(); temp1.moveNext(), temp2.moveNext()){
				//check if the digit of temp1 is greater than that of temp2
				if(temp1.peekNext() > temp2.peekNext()){
					return 1;
				}
				else if(temp1.peekNext() < temp2.peekNext()){
					return -1;
				}
			}
		}
		return 0;
	}
	//second case: both negative
	if(signum == -1 && N.signum == -1){
		//check if one is shorter than the other because that
		//means the shorter is automatically larger and you can stop checking
		if(temp1.length() > temp2.length()){
			return -1;
		}
		else if(temp1.length() < temp2.length()){
			return 1;
		}
		else{
			//otherwise they are not the same length and you have to start 
			//checking the digits
			for(temp1.moveFront(), temp2.moveFront(); temp1.position() < temp1.length(); temp1.moveNext(), temp2.moveNext()){
				//check if the digit of temp1 is greater than that of temp2
				if(temp1.peekNext() > temp2.peekNext()){
					return -1;
				}
				else if(temp1.peekNext() < temp2.peekNext()){
					return 1;
				}
			}
		}
		return 0;
	}
	return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	signum = 0;
	digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
	signum = signum * -1;
}

// Helper Functions --------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    L.moveBack();
    while (L.position() > 0) {
        int currentValue = L.peekPrev();
        //std::cout << "value before neg: " << currentValue << std::endl;
        L.eraseBefore();
        currentValue *= -1;
        //std::cout << "value after neg: " << currentValue << std::endl;
        L.insertBefore(currentValue);
        L.movePrev();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
	//since S is to hold values of A + sgn*B you can 
	//go through both the lists and compute what needs to be computed 
	//with the elements at A and B
	//start off at the back of both lists
	S.clear();
	A.moveBack(); B.moveBack();
	// std::cout << "in sL func call " << std::endl;
	// std::cout << "A: " << A << std::endl;
	// std::cout << "B: " << B << std::endl;
	//then run a loop while the positions don't pass 0 
	while(A.position() > 0 && B.position() > 0){
		//use peekPrev() to access the elements and insert them into S
		int temp = B.peekPrev();
		//std::cout << "temp bef: " << temp << std::endl;
		temp *= sgn;
		//std::cout << "temp aft: " << temp << std::endl;
		S.insertAfter(A.peekPrev() + temp);
		//then continue moving along the lists
		A.movePrev(); B.movePrev();
	}

	//then if A is longer than B, add the rest of A's elements to S
	//and vice versa with B
	while(A.position() > 0){
		S.insertAfter(A.peekPrev());
		A.movePrev();
	}
	while(B.position() > 0){
		S.insertAfter(sgn * B.peekPrev());
		B.movePrev();
	}
	//then make sure there aren't any leading 0s at the front of S
	S.moveFront();
	while(S.length() > 1 && S.front() == 0){
		//then delete the element 
		S.eraseAfter();
	}
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){

    long carry = 0;
    int sign;
	//check if the sign is 0, if so return 0 
	if(L.front() == 0){
		return 0;
	}
	else if(L.front() < 0){
		negateList(L);
		sign = -1;
	}
	else{
		sign = 1;
	}


    L.moveBack();

    //std::cout << "Before normalization: " << L << std::endl;

    while (L.position() > 0) {
        long digit = L.peekPrev() + carry;
        carry = digit / BASE;
        int newDigit = (int)(digit % BASE);
        if (newDigit < 0) {
            newDigit += BASE;
            carry -= 1;
        }
        L.insertAfter(newDigit);
        L.movePrev();
        L.eraseAfter();
        //std::cout << "Digit: " << newDigit << ", Carry: " << carry << std::endl;
    }
    //std::cout << L << std::endl;

    if (carry != 0) {
        L.moveFront();
        L.insertBefore((int)(carry * sign));
    }

    //std::cout << "Normalized List: " << L << std::endl;

    L.moveFront();
    while (L.position() < L.length() - 1 && L.front() == 0) {
        L.eraseAfter();
    }

    return sign;

}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
	//start at the back of the list
	L.moveBack();
	//run a loop until the power
    for (int i = 0; i < p; i++) {
        //insert 0 to prepend that many 0 digits to L
        L.insertAfter(0);
	}
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    List temp;
    L.moveBack();

    int carry = 0;

    while (L.position() > 0) {
        long long product = (long long)L.peekPrev() * m + carry;
        int newDigit = (int)(product % BASE);
        carry = (int)(product / BASE);
        temp.insertAfter(newDigit);
        L.movePrev();
    }

    if (carry != 0) {
        temp.insertAfter(carry);
    }

    L.clear();
    temp.moveBack();

    while (temp.position() > 0) {
        L.insertAfter(temp.peekPrev());
        temp.movePrev();
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger A;
	//create temp lists for the digits of List A and List B
	List tempA = this->digits;
	List tempB = N.digits;
	//then you want to check if the either of the list are 
	//negative, and if they are then negate them so they are no 
	//longer negative 
	if(this->signum < 0){
		negateList(tempA);
	}
	if(N.signum < 0){
		//std::cout << "in here " << std::endl;
		negateList(tempB);
	}
	//std::cout << "Negated: " << tempB << std::endl;
	//then you want to call sumList() to perform the addition 
	//create a temp list to store the sum of A+B
	List tempSum;
	//pass in all needed variables with sign 1 since
	//we negated any negative lists 
	sumList(tempSum, tempA, tempB, 1);
	//then normalize the tempSum list so you can get the sign 
	//of the list 
	//std::cout << "before: " << tempSum << std::endl;
	A.signum = normalizeList(tempSum);
	A.digits = tempSum;
	
	return A;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	//std::cout << "N: " << N << std::endl;
	BigInteger S;
	//for subtraction, you are just adding the negative version of the second 
	//list, so you can negate N's list and then use the sumList function 
	//create another temp BigInt var so you don't change the original 
	int comparison = compare(N);
	if(comparison == 0){
		S.makeZero();
		return S;
	}
	else{
		List tempA = this->digits;
		//std::cout << "tempA: " << tempA << std::endl;
		List tempB = N.digits;
		//std::cout << "tempB: " << tempB << std::endl;
		if(this->signum < 0){
		negateList(tempA);
		}
		if(N.signum < 0){
		negateList(tempB);
		}
		sumList(S.digits, tempA, tempB, -1);

		//std::cout << "S: " << S.digits << std::endl;
	}
	S.signum = normalizeList(S.digits);

  	return S;
  	
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger M;
    //first check if either of the lists have signum 0 
	//because 0 * anything is 0 so you can automatically return 0
    if (this->signum == 0 || N.signum == 0){
        return M;
    }

    //create variables to hold all the data
    List product;
    List tempA;
    List tempB = N.digits;

    //multiply the signums to get the results signum
    M.signum = signum * N.signum;

    //move to the back of the list
    tempB.moveBack();
    //ctr for the shift
    int shift = 0;
    //run a loop through all the elements
    while (tempB.position() > 0) {
        tempA = this->digits;
        //then run scalarMultList on tempA and one element of 
		//tempB by calling peekPrev to get that one element
        scalarMultList(tempA, tempB.peekPrev());
        //shift the list over before multiplying by the next element of tempB
        shiftList(tempA, shift);
        
        List productCopy = product;
        //add the lists together
        sumList(product, productCopy, tempA, 1);
        //then normalize
        normalizeList(product);

        tempB.movePrev();
        //increase the shift ctr
        shift++;
    }

    M.digits = product;


    return M;
}



// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	//declare empty string to store the result
	std::string res = "";
	//check if the BigInt is 0 
	if(signum == 0){
		//just return a string with '0'
		return "0";
	}
	//check if the BigInt is neg.
	else if(signum == -1){
		//res will being with neg. sign
		res+= "-";
	}
	//now time to fill in the digits
	//temp list for digits 
	List temp = digits;
	//move through the list and first get rid of 
	//all the unnecessary zeros 
	temp.moveFront();
	while(temp.position() < temp.length() && temp.peekNext() == 0){
    	temp.eraseAfter();
	}
	//once all 0s have been removed move back to the front of the list
	//then moveNext on the list while the position of the cursor is less than 
	//the length
	for(temp.moveFront(); temp.position() < temp.length(); temp.moveNext()){
		//
        std::string s1 = std::to_string(temp.peekNext());
        std::string s2 = "";
        //used to add 0s if length doesn't = the power
        while((s2.length() + s1.length()) < POWER && temp.position() < temp.length() && temp.position() > 0) {
            s2 += '0';
        }
        res += (s2 + s1);
    }
    return res;
} //DOES THIS WORK?


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	if(A.compare(B) == 0){
		return true;
	}
	return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	if(A.compare(B) == - 1){
		return true;
	}
	return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	if(A.compare(B) <= 0){
		return true;
	}
	return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	if(A.compare(B) == 1){
		return true;
	}
	return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	if(A.compare(B) >= 0){
		return true;
	}
	return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	A = A.BigInteger::add(B);
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.BigInteger::sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	A = A.BigInteger::mult(B);
	return A;
}






