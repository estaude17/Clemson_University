/*Elizabeth Stauder(estaude)
CPSC 2121 Lab 9
November 5, 2015
This is a program that, given amounts
A, B, and X, computes how to measure out exactly
X units of water using jugs that contain A units and B units.
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int a, b, x;// a = water in jug 1, b = water in jug 2, x = total water.
int c;//variable used to find amount of water left after pouring A/B->B/A.
//bool done = false;//variable will return true when solution found.

//visited states, initialized to 0 because we haven't visited any yet.
bool visited[1001][1001] = {0};

int previous[1001][1001];//these mark which steps we've already taken.
int previous2[1001][1001];//previous is for jug 1, previous2 for jug 2

int move_type[1001][1001];//stores type of move done.

int end1, end2;//final values of jug1 and jug2.

bool solve(int A, int B)
{
  visited[A][B] = true;
  if(A+B == x){ 
	end1 = A;
	end2 = B;
	return true;//return when done
	}
  
  //6 possible actions: try all until A+B = x.
  if(visited[a][B] == false){
	previous[a][B] = A;
	previous2[a][B] = B;
	move_type[a][B] = 0;
	if(solve(a, B)) return true;}//fill A

  if(visited[0][B] == false){
	previous[0][B] = A;
        previous2[0][B] = B;
        move_type[0][B] = 2;
  	if(solve(0, B)) return true;}//empty A
  
  if(visited[A][b] == false){
	previous[A][b] = A;
        previous2[A][b] = B;
        move_type[A][b] = 1;
  	if(solve(A, b)) return true;}//fill B

  if(visited[A][0] == false){
 	previous[A][0] = A;
        previous2[A][0] = B;
        move_type[A][0] = 3;
   	if(solve(A, 0)) return true;}//empty B

  c = min(A, b-B);
  if(visited[A-c][B+c] == false){
        previous[A-c][B+c] = A;
        previous2[A-c][B+c] = B;
        move_type[A-c][B+c] = 4;
        if(solve(A-c, B+c)) return true;} //from A->B

  c = min(B, a-A);
  if(visited[A+c][B-c] == false){
        previous[A+c][B-c] = A;
        previous2[A+c][B-c] = B;
        move_type[A+c][B-c] = 5;
        if(solve(A+c, B-c)) return true;}//from B->A

  return false;//if nothing works, return false.
}

void print_soln(int x, int y)
{
  string name[6] = { "Fill jug 1", "Fill jug 2", "Empty jug 1", "Empty jug 2", 
			"Pour 1->2", "Pour 2->1" };
  if(x == 0 && y == 0) return;
  print_soln(previous[x][y], previous2[x][y]);
  cout << name[move_type[x][y]] << " " << "[a= " << x << "] " 
		"[b= " << y << "]" << endl;
}

int main()
{
  cout << "Enter A, B, and X:" << endl;
  cin >> a;
  cin >> b;
  cin >> x;
  if(a > 1000 || b > 1000)
	{
	cout << "Too large! Needs to be under 1000! Try again!" << endl;
	return -1;
	}

  //solve(0, 0);//jug amounts always initialized to zero.

  if (solve(0,0)){//jug amounts always initialized to zero.
	cout << "Solved!" << endl;
	print_soln(end1, end2);}
  else cout << "Impossible!" << endl;

  return 0;
}
