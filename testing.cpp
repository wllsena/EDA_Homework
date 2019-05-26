#include <iostream>
#include <vector>
#include <chrono>
#include "gerate_trie.cpp"

using namespace std;

void print_vector(vector<int> vec) {
  for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i)
    cout << *i << ' ';
  cout << endl;
};


int main() {
  trie *tree = new trie();
  vector<string> titles;
  read_and_insert(tree, titles);
  //
  string word;
  vector<int> indexes;
  auto start = chrono::high_resolution_clock::now();
  auto finish = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsed;

  while (true) {
    cin >> word;
    search(tree, "0");

    start = chrono::high_resolution_clock::now();
    indexes = search(tree, word);
    finish = chrono::high_resolution_clock::now();
    elapsed = finish - start;

    cout << "... Elapsed time: " << elapsed.count() << " seconds or " << 1000*elapsed.count() << " milliseconds or " << 1000000*elapsed.count() << " microseconds\nIndex: ";
    print_vector(indexes);
  };
  return 0;
};
