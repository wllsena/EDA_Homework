#include <chrono>
#include "gerate_trie.cpp"
//#include "word_suggestor.cpp"

using namespace std;

auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed;

void print_titles(const vector<int> *indexes, const vector<string> &titles) {
  if (indexes) {
    string answer = "";
    int k = 0;
    for (vector<int>::const_iterator index = indexes->begin(); index != indexes->end() and answer != "n"; k++) {
      cout << "[" << k+1 << "] " << titles[*index] << endl;
      ++index;
      if (index != indexes->end() and k % 20 == 19) {
        cout << "More results? (y, n): ";
        getline(cin >> ws, answer);
      };
    };
    cout << "Do you want to open any result [n or result number]? ";
    getline(cin >> ws, answer);
    // TO-DO
  };
};

vector<int> *intersect(const vector<vector<int>*> &indexes, const int &size) {
  auto inter = indexes[0];
  for (int k = 1; k < size; k++) {
    if (inter and indexes[k]) {
      for (int i = 0; i < inter->size(); i++) {
        if (find(indexes[k]->begin(), indexes[k]->end(), (*inter)[i]) == indexes[k]->end())
          (*inter)[i] = -1;
      };
    } else return NULL;
  };
  if (size != 1)
    inter->erase(remove(inter->begin(), inter->end(), -1), inter->end());
  return inter;
};


int main() {
  string word = "snull";
  vector<vector<int> > strings; vector<string> titles; vector<int> snull;
  int post; int size; vector<int> *inter = new vector<int> ();
  for (int i = 0; i < 36; i++) snull.push_back(i);

  trie *tree = new trie();
  read_and_insert(tree, titles);

  cout << titles.size() << " titles\n";
  while (true) {
    cout << "Type a word to perform a search or \"!q\" if you want to quit: ";
    getline(cin >> ws, word);
    if (word == "!q") return 0;

    convert(word);
    strings = word_breaker(word);
    vector<vector<int>*> indexes;
    size = strings.size();
    indexes.reserve(size);
    search(tree, snull);

    start = chrono::high_resolution_clock::now();
    for (post = 0; post < size; post++)
      indexes[post] = search(tree, strings[post]);
    finish = chrono::high_resolution_clock::now();
    elapsed = finish - start;

    inter = intersect(indexes, size);
    cout << "About " << (inter ? inter->size() : 0) << " results (" << 1000000*elapsed.count() << " microseconds)\n";
    print_titles(inter, titles);
  };
};
