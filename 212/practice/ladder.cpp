#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string A, B;
vector<int> pred, dist;
vector<string> words;

void solve(void)
{
  
}

int main(void)
{
  ifstream fin("5words.txt");
  string s;
  while(fin >> s)
	{
	words.push_back(s);
	dist.push_back(99999999999999999);
 	pred.push_back(-1);
	}
  find.close();
  cout << words.size() << endl;

  cout << "Word A: ";
  cin >> A;
  cout << "Word B: ";
  cin >> B;
  
  source = -1;
  for(int i = 0; i < words.size(); i++)
	

  solve();
  return 0;
}
