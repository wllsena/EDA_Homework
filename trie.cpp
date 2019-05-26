#include <iostream>
#include <vector>

using namespace std;

struct trie {
  trie *children[74];
  vector<int> indexes;
};


vector<int> search(trie *tree, string word) {
  trie *branch = tree;
  int i = 0;
  while (true) {
    if (word[i] == '\0')
      return branch->indexes;
    else {
      branch = branch->children[int(word[i])-48];
      if (branch)
        i++;
      else
        return vector<int> ();
    };
  };
};


trie* initialize_trie () {
  trie *tree = new trie();
  for (int i = 0; i < 74; i++) {
    tree->children[i] = NULL;
  };
  return tree;
};


void put_word (trie *tree, string word, int index) {
  trie *branch = tree;
  int i = 0;
  while (true) {
    if (word[i] == '\0') {
      if (find(branch->indexes.begin(), branch->indexes.end(), index) == branch->indexes.end())
        branch->indexes.push_back(index);
      return;
    };
    if (branch->children[int(word[i])-48]) {
      branch = branch->children[int(word[i])-48];
      i++;
    } else {
      branch->children[int(word[i])-48] = initialize_trie();
    };
  };
};
