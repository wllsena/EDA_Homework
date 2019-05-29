#include <iostream>
#include <vector>
#include <chrono>
#include "gerate_trie.cpp"

using namespace std;

void print_titles(vector<int> *indexes, vector<string> titles) {
  if (indexes) {
    char answer;
    int k = 0;
    for (vector<int>::const_iterator index = indexes->begin(); index != indexes->end() and answer != 'n'; ++index, k++) {
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
  vector<string> strings;

  auto start = chrono::high_resolution_clock::now();
  auto finish = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed;

  while (true) {
    if (word.length() > 0)
      cout << "\"!q\" if you want to quit or type a word to do a search: ";

    getline(cin, word);
    if (word == "!q") return 0;

    if (word.length() > 0) {
      vector<vector<int>*> *indexes = new vector<vector<int>*>;

      convert(word);
      strings = word_breaker(word);
      search(tree, snull);

      start = chrono::high_resolution_clock::now();
      for (int i = 0; i < strings.size(); i++)
        indexes->push_back(search(tree, strings[i]));
      finish = chrono::high_resolution_clock::now();
      elapsed = finish - start;

      cout << "About " << (*indexes)[0]->size() << " results (" << 1000000*elapsed.count() << " microseconds)\n";

      print_titles((*indexes)[0], titles);
    };
  };
};
