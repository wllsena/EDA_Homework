#include <iostream>
#include <vector>

using namespace std;

struct trie {
  trie *children[26];
  vector<int> links;
};

trie* init_trie () {
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
      branch->links.push_back(index);
      return;
    };
    if (branch->children[int(word[i])-97]) {
     branch = branch->children[int(word[i])-97];
     i++;
    } else {
      trie *news = init_trie();
      branch->children[int(word[i])-97] = news;
    };
  };
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
      print(branch->links);
      return;
    };
    if (branch->children[int(word[i])-97]) {
      branch = branch->children[int(word[i])-97];
      i++;
    } else {
      cout << "no links :(\n";
      return;
    };
  };
};


int main() {
  trie *a = init_trie();
  put_word(a, "ab", 1);
  put_word(a, "fuck", 2);
  put_word(a, "oie", 3);

  string word;
  while (true) {
    cin >> word;
    search(a, word);
  };
};
