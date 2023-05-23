//-----------------------------------------------------------------------------
//  Pallavi Rajeev
//  prajeev
//  pa6
//  BigIntegerTest.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "91287346670000043892345634563400005619187236478";
   string s2 = "-330293847502398475";
   string s3 = "9876545439000000345634560000000002000034565430000000006543654365346534";
   string s4 = "9876545439000000000000000100000000000006543654365346534";
   string s5 = "98765454390000034563456191872363456345619187236000456456345756780000065436543";
   string s6 = "9876545439000000000000000000000000000006543";

   //BigInteger N;
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);
   BigInteger C = BigInteger(s5);

   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   BigInteger D = A+B;
   BigInteger E = B+A;
   BigInteger F = D-E;
   BigInteger G = 53234*A + 29384747*B + 928374*C;
   BigInteger H = A*B;
   BigInteger I = B*A;
   BigInteger J = G*H*I;

   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "(D==E) = " << ((D==E)?"True":"False") << endl;
   cout << "F = " << F << endl;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   cout << "I = " << I << endl;
   cout << "(H==I) = " << ((H==I)?"True":"False") << endl;
   cout << "J = " << J << endl << endl;

   cout << endl;

   A += B;
   B -= C;
   C *= J;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << A*B*C*D*E*G*H*I*J << endl << endl;

   cout << endl;

   // test exceptions
   try{
      BigInteger J = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("+");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   //more tests to test all functions

   //BigInt from string
   string a = "882133";
   string b = "659179";
   BigInteger tempA = BigInteger(a);
   BigInteger tempB = BigInteger(b);
   cout << "Add: " << tempA + tempB << endl;
   cout << "Sub: " << tempA - tempB << endl;
   cout << "Mult: " << tempA * tempB << endl;


   int comp1 = tempA.compare(tempB);
   cout << "compare: " << comp1 << endl;

   cout << "(tempA==tempB) = " << ((tempA==tempB)?"True":"False") << endl;
   cout << "(tempA<tempB)  = " << ((tempA<tempB)? "True":"False") << endl;
   cout << "(tempA<=tempB) = " << ((tempA<=tempB)?"True":"False") << endl;
   cout << "(tempA>tempB)  = " << ((tempA>tempB)? "True":"False") << endl;
   cout << "(tempA>=tempB) = " << ((tempA>=tempB)?"True":"False") << endl << endl;

   BigInteger X = BigInteger("1234");
   BigInteger Y = BigInteger("5678");
   cout << "Add: " << X + Y << endl;
   cout << "Sub: " << X - Y << endl;
   cout << "Mult: " << X * Y << endl;

   int comp2 = X.compare(Y);
   cout << "compare: " << comp2 << endl;

   cout << "(X==Y) = " << ((X==Y)?"True":"False") << endl;
   cout << "(X<Y)  = " << ((X<Y)? "True":"False") << endl;
   cout << "(X<=Y) = " << ((X<=Y)?"True":"False") << endl;
   cout << "(X>Y)  = " << ((X>Y)? "True":"False") << endl;
   cout << "(X>=Y) = " << ((X>=Y)?"True":"False") << endl << endl;

   //BigInt from long
   BigInteger R = BigInteger("+111122223333");

   R.makeZero();
   cout << "R: " << R << endl;

   BigInteger S;
   BigInteger T;

   R = BigInteger("101122223333");
   S+=R;
   S = BigInteger("101122223333");
   S-=R;
   S = BigInteger("101122223333");
   S*=R;
   cout << "Add eq: " << S << endl;
   cout << "Sub eq: " << S << endl;
   cout << "Mult eq: " << S << endl;

   cout << "bef R: " << R << endl;
   cout << "bef R sign: " << R.sign() << endl;

   R.negate();

   cout << "after R: " << R << endl;
   cout << "after R sign: " << R.sign() << endl;

   cout << R.to_string() << endl;

   T = BigInteger("212244446666");

   
   T.negate();
   cout << "after T sign: " << T.sign() << endl;

   T.makeZero();
   cout << "T: " << T << endl;


   BigInteger L = BigInteger("+123456789876");
   cout << "L: " << L << endl;
   BigInteger M = BigInteger("-123456789876");
   cout<< "M sign: " << M.sign() << endl;
   cout << "M: " << M << endl;
   
   L+=M;
   L = BigInteger("+123456789876");
   L-=M;
   L = BigInteger("+123456789876");
   L*=M;
   cout << "Add eq: " << L << endl;
   cout << "Sub eq: " << L << endl;
   cout << "Mult eq: " << L << endl;

   cout << L.to_string() << endl;

   cout << "Tests complete!" << endl;


   return EXIT_SUCCESS;


}
