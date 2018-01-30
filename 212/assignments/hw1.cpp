#include <iostream>
#include <fstream>
#include "stringset.h"

using namespace std;

struct Elem {
  int val;
  Elem *next;
  Elem (int v, Elem *n) { val = v; next = n; }
};

struct Page {
  string url;
  int num_links;
  double weight;
  double new_weight;
  Elem *first_word;
  Elem *first_link;
};

struct Word {
  string name;
  Elem *first_page;
};

Stringset Phash, Whash;
Page *P;
Word *W;
int num_pages, num_words;

bool is_link(string s)
{
  return Phash.find(s) != -1;
}

void read_input(void)
{
  ifstream fin;
  string s;
  fin.open ("webpages.txt");
  while (fin >> s) {
    if (s == "NEWPAGE") {
      fin >> s;
      Phash.insert(s, Phash.get_size());
    }
    else
      if (Whash.find(s) == -1)
	Whash.insert(s, Whash.get_size());
  }
  fin.close();
  
  num_pages = Phash.get_size();
  num_words = Whash.get_size();

  P = new Page[num_pages];
  W = new Word[num_words];

  for (int i=0; i<num_pages; i++) {
    P[i].num_links = 0;
    P[i].first_word = P[i].first_link = NULL;
  }
  for (int i=0; i<num_words; i++)
    W[i].first_page = NULL;

  fin.open ("webpages.txt");
  int current_page = -1;
  while (fin >> s) {
    if (s == "NEWPAGE") {
      current_page++;
      fin >> P[current_page].url;
    } else {
      if (is_link(s)) {
	P[current_page].first_link =
	  new Elem(Phash.find(s), P[current_page].first_link);
	P[current_page].num_links++;
      }
      else {
	int index = Whash.find(s);
	W[index].name = s;
	P[current_page].first_word = 
	  new Elem(index, P[current_page].first_word);
	W[index].first_page = 
	  new Elem(current_page, W[index].first_page);
      }
    }
  }
  fin.close();
}

void run_pagerank(void)
{
  for (int i=0; i<num_pages; i++)
    P[i].weight = 1.0 / num_pages;
  for (int iter=0; iter<50; iter++) {
    cout << "Iteration " << iter << "\n";
    for (int i=0; i<num_pages; i++)
      P[i].new_weight = 0.1 / num_pages;
    for (int i=0; i<num_pages; i++)
      if (P[i].num_links > 0)
	for (Elem *nbr = P[i].first_link; nbr; nbr = nbr->next)
	  P[nbr->val].new_weight += 0.9 * P[i].weight / P[i].num_links;
    for (int i=0; i<num_pages; i++)
      P[i].weight = P[i].new_weight;
  }
}

void process_queries(void)
{
  string s;
  cout << "Please enter your queries...\n";
  while (cin >> s) {
    int index = Whash.find(s);
    if (index == -1)
      cout << "Not found!\n";
    else {
      Elem *temp = W[index].first_page;
      while (temp != NULL) {
	cout << (int)(P[temp->val].weight * num_pages * 100) << " " 
	     << P[temp->val].url << "\n";
	temp = temp->next;
      }
    }
  }
}

int main(void)
{
  read_input();
  run_pagerank();
  process_queries();
}
