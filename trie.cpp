#include <iostream>
#include <vector>

using namespace std;

struct trie {
  trie *children[36];
  vector<int> indexes;
};

trie *branch;
int post;
int num;

vector<int> search(trie *tree, string &word) {
  branch = tree;
  post = 0;
  while (true) {
    if (word[post] == '\0')
      return branch->indexes;
    else {
      num = int(word[post]);
      branch = branch->children[num - (num > 57 ? 87 : 48)];
      if (branch)
        post++;
      else
        return vector<int> ();
    };
  };
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
    num = int(word[i]) - (int(word[i]) > 57 ? 87 : 48);
    if (branch->children[num]) {
      branch = branch->children[num];
      i++;
    } else {
      branch->children[num] = new trie();
    };
  };
};
