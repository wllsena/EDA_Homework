#include <iostream>
#include <vector>

using namespace std;

struct trie {
  trie *children[26];
  vector<int> indexes;
};


void print(vector<int> vec) {
  for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i)
    cout << *i << ' ';
  cout << "\n";
};


void search(trie *tree, string word) {
  trie *branch = tree;
  int i = 0;
  while (true) {
    if (word[i] == '\0') {
      cout << "links :)\n";
      print(branch->indexes);
      return;
    };
    branch = branch->children[int(word[i])-97];
    if (branch)
      i++;
    else {
      cout << "no links :(\n";
      return;
    };
  };
};


trie* initialize_trie () {
  trie *tree = new trie();
  for (int i = 0; i < 26; i++) {
    tree->children[i] = NULL;
  };
  return tree;
};


void put_word (trie *tree, string word, int index) {
  trie *branch = tree;
  int i = 0;
  while (true) {
    if (word[i] == '\0') {
      branch->indexes.push_back(index);
      return;
    };
    if (branch->children[int(word[i])-97]) {
     branch = branch->children[int(word[i])-97];
     i++;
    } else {
      branch->children[int(word[i])-97] = initialize_trie();
    };
  };
};


int main() {
  trie *tree = initialize_trie();
  put_word(tree, "123", 1);
  put_word(tree, "abd", 2);
  put_word(tree, "abe", 3);

  string word;
  while (true) {
    cin >> word;
    search(tree, word);
  };
};
