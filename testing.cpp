#include <iostream>
#include <vector>
#include <chrono>
#include "gerate_trie.cpp"
#include "word_suggestor.cpp"

using namespace std;

void print_titles(set<int> *indexes, vector<string> titles) {
  if (indexes) {
    int k = 0;
	char answer = '0';
    for (set<int>::const_iterator index = indexes->begin(); index != indexes->end() and answer != 'n' ; ++index, k++) {
      cout << "[" << k+1 << "] " << titles[*index] << endl;
      if (k % 20 == 19) {
        cout << "More results? (y, n): ";
        cin >> answer;
      };
    };
    cout << "Do you want to open any result [n or result number]? ";
    // TO-DO
    cin >> answer;
  };
};


int main() {
  trie *tree = new trie();
  vector<string> titles;
  read_and_insert(tree, titles);

  string word = "snull";
  string snull = "snull";
  vector<vector<int> > strings;

  auto start = chrono::high_resolution_clock::now();
  auto finish = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed;

  cout << titles.size() << endl;
  while (true) {
    if (word.length() > 0)
      cout << "Type a word to perform a search or \"!q\" if you want to quit: ";

    getline(cin, word);
    if (word == "!q") return 0;

    if (word.length() > 0) {
      set<int> *indexes = new set<int> ();

      convert(word);
      strings = word_breaker(word);
      //search(tree, snull);

      start = chrono::high_resolution_clock::now();
      //for (int i = 0; i < strings.size(); i++)
      indexes = search(tree, strings[0]);
      finish = chrono::high_resolution_clock::now();
      elapsed = finish - start;

      cout << "About " << indexes->size() << " results (" << 1000000*elapsed.count() << " microseconds)\n";
      print_titles(indexes, titles);
    };
  };
};
