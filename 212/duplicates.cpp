#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main(void)
{
  // read 10,000 files named /tmp/manyfiles/1.txt, /tmp/manyfiles/2.txt, etc.
  ifstream fin;
  char filename[100];

  for (int i=1; i<=10000; i++) {
    sprintf (filename, "/tmp/manyfiles/%d.txt", i);
    fin.open (filename);

    
    // ------
    // Now do whatever you want to each file; for example...
    int count = 0;
    string s;
    while (fin >> s) count++;
    cout << "File " << filename << " contains " << count << " strings\n";
    // ------
    
   
 
    fin.close();
  }
  return 0;
}
