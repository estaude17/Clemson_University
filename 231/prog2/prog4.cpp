#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

void prt_bin(int, int);
void swapadd(int num2, int num1, int exp2, int exp){
  cout << "addition of the values:" << endl;
  cout << endl << "operands are swapped" << endl;
  cout << "internal rep of first value:   1.";
  prt_bin(num1, 4);
  if(exp >= 0) cout << " x 2^(+" << exp <<")" << endl;
  else cout << " x 2^(" << exp <<")" << endl;
  cout << "internal rep of second value:  1.";
  prt_bin(num2, 4);
  if(exp2 >= 0) cout << " x 2^(+" << exp2 <<")" << endl;
  else cout << " x 2^(" << exp2 <<")" << endl; 
}
void addition(int num1, int num2, int exp, int exp2){
  int sum, expsum;
  sum = num1 + num2;
  expsum = ((sum >> 4) & 7)-4;

  cout << "addition of the values:" << endl;
  cout << endl << "addition takes place" << endl;
  cout << "internal rep of first value:   1.";
  prt_bin(num1, 4);
  if(exp >= 0) cout << " x 2^(+" << exp <<")" << endl;
  else cout << " x 2^(" << exp <<")" << endl;
  cout << "internal rep of second value:  1.";
  prt_bin(num2, 4);
  if(exp2 >= 0) cout << " x 2^(+" << exp2 <<")" << endl;
  else cout << " x 2^(" << exp2 <<")" << endl;
  cout << "internal rep of sum: 1.";
  prt_bin(sum, 4);
  if(expsum >= 0) cout << " x 2^(+" << expsum <<")" << endl;
  else cout << " x 2^(" << expsum <<")" << endl;
  cout << "hidden bit---------------------^ ffff gr" << endl;
  cout << "4-bit fraction-------------------^^^^" << endl;
  cout << "encoding of returned value: " << endl;
}

//this function prints out the binary equivalent of the variable given.
void prt_bin(int value, int length ){
  int i;      
  for( i=(length-1); i>=0; i--){
	if((value>>i)&1) putchar('1');
      	else putchar('0');   
    	}           
 }

float shifter(int a){
  float b2, c2, d2, e2;
  int b = a >> 3;
  (b%2 == 0) ? b2 = 0 :  b2 = 0.5;
   
  int c = a >> 2;
  (c%2 == 0) ? c2 = 0 :  c2 = 0.25;
  
  int d = a >> 1;
  (d % 2 == 0) ? d2 = 0 : d2 = 0.125;
  
  int e = a;
  (e % 2 == 0) ? e2 = 0 : e2 = 0.0625;
  
  float f = b2 + c2 + d2 + e2;
  
  return f;
}

int main(void){
  int num1, num2, exp, exp2, sign1, sign2;
  float val1, val2, sum, sum2;
  cin >> num1 >> num2;
  sign1 = (num1 >> 7) & 1;
  sign2 = (num2 >> 7) & 1;
  
  int new1 = num1 & 0x0f;
  int new2 = num2 & 0x0f;
  
  float fnew = shifter(new1);
  float fnew2 = shifter(new2);
  
  cout << fixed;
  cout << setprecision(4);  

  cout << fnew << endl;
  cout << fnew2 << endl;

  exp = ((num1 >> 4) & 7)-4;
  exp2 = ((num2 >> 4) & 7)-4;
  
  cout << "first value: " << num1 << endl;
  cout << "second value: " << num2 << endl;	
  
  cout << endl << "encoding of first value:      ";
  prt_bin(num1, 8);
  cout << endl;
  
  cout << "encoding of second value:     ";
  prt_bin(num2, 8);
  cout << endl;
  
  cout << endl << "internal rep of first value:   1.";
  prt_bin(num1, 4);
 
  if(exp >= 0) cout << " x 2^(+" << exp <<")" << endl;
  else cout << " x 2^(" << exp <<")" << endl;
  
  cout << "internal rep of second value:  1.";
  prt_bin(num2, 4);
  
  if(exp2 >= 0) cout << " x 2^(+" << exp2 <<")" << endl;
  else cout << " x 2^(" << exp2 <<")" << endl;
  
  cout << "hidden bit---------------------^ ffff" << endl;
  cout << "4-bit fraction-------------------^^^^" << endl;
  
  val1 = 1 + fnew;
  val2 = 1 + fnew2;
  
  sum = val1 * pow(2, exp);
  sum2 = val2 * pow(2, exp2);
  
  //cout << endl << "first value is:  +" << val1 << " x 2^(";
	//cout << exp <<") = " << sum << endl;
  //cout << "second value is: +" << val2 << " x 2^("; 
	//cout << exp2 <<") = " << sum2 << endl;
  if(exp > exp2) swapadd(num1, num2, exp, exp2);
  else addition(num1, num2, exp, exp2);
}
