#include <chrono>
#include "gerate_trie.cpp"

using namespace std;

auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed;

void print_titles(set<int> *indexes, vector<string> titles) {
  if (indexes) {
    string answer;
    int k = 0;
    for (set<int>::const_iterator index = indexes->begin(); index != indexes->end() and answer != "n"; ++index, k++) {
      cout << "[" << k+1 << "] " << titles[*index] << *index << endl;
      if (k % 20 == 19) {
        cout << "More results? (y, n): ";
        getline(cin >> ws, answer);
      };
    };
    cout << "Do you want to open any result [n or result number]? ";
    getline(cin >> ws, answer);
    // TO-DO
  };
};

/*
void intersection(vector<int> *indexes, vector<int> *vec) {
  int post = 0;
  vector<int>::const_iterator iter = indexes->begin();
  while (iter != indexes->end()) {
    if ((*vec)[post] > *iter) post++;
    else {
      indexes->insert(iter, (*vec)[post]);
      ++(++iter);
    };
  };
};
*/

int main() {
  string word = "snull";
  vector<vector<int> > strings; vector<string> titles; vector<int> snull;
  int post; int size; set<int> *inter;
  for (int i = 0; i < 36; i++) snull.push_back(i);

  trie *tree = new trie();
  read_and_insert(tree, titles);

  while (true) {
    cout << "\"!q\" if you want to quit or type a word to do a search: ";
    getline(cin >> ws, word);

    if (word == "!q") return 0;

    convert(word);
    strings = word_breaker(word);
    vector<set<int>*> indexes;
    size = strings.size();
    indexes.reserve(size);
    search(tree, snull);

    start = chrono::high_resolution_clock::now();
    for (post = 0; post < size; post++)
      indexes[post] = search(tree, strings[post]);
    finish = chrono::high_resolution_clock::now();
    elapsed = finish - start;

    cout << "About " << (indexes[0] ? indexes[0]->size() : 0) << " results (" << 1000000*elapsed.count() << " microseconds)\n";
    print_titles(indexes[0], titles);
  };
};
