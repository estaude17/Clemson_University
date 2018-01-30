/*
Elizabeth Stauder (estaude)
09/03/15 CPSC 2121-001
This program, when accompanied by word.txt, sifts through the text file
and prints words that differ from the submitted word by a single character.
The spellcheck function is used for this, not test. 
*/
#include <string>
#include <fstream>
#include <iostream>
#include "stringset.h"

using namespace std;

void spellcheck(void)
{
  Stringset S;
  string word;

  ifstream wordfile("words.txt");
  while (wordfile >> word)
    S.insert(word);
  wordfile.close();

  cout << "Dictionary loaded.  Please enter words to spell check.\n";

  while (cin >> word) {
    cout << "Possible alternatives for word '" << word << "':\n";

    // TBD: print out all words that differ by exactly one character.
  for(int i = 0; i < word.length(); i++){
      for(int j = 'a'; j <= 'z'; j++)
	{
	char value = word[i];//character in given word that is altered.
	word[i] = j;
  	if(j != value){//the word is similar to given word aside from char j
	   if(S.find(word) == true){
		cout << word << endl;//prints out new, slightly different word
		}
	   }
	word[i] = value;    
  	}
    }
  }
}
void test(void)
{
  Stringset S;
  string key, command;

  while(cin >> command) {
    
    if (command == "insert") {
      
      cin >> key;
      if (S.find(key))
	cout << "Error!  Key " << key << " already in structure!\n";
      else
	S.insert(key);

    } else if (command == "remove") {
      
      cin >> key;
      if (!S.find(key)) 
	cout << "Error!  Key " << key << " not in structure!\n";
      else
	S.remove(key);

    } else if (command == "find") {

      cin >> key;
      if (S.find(key))
	cout << "Key " << key << " present.\n";
      else
	cout << "Key " << key << " absent.\n";

    } else if (command == "print") {

      cout << "Contents of structure:\n";
      S.print();

    } else if (command == "quit") {

      break;

    } else {

      cout << "Error!  Unknown command '" << command << "'!\n";

    }
  }
}

int main(void)
{
  //test();
  spellcheck();
  return 0;
}
