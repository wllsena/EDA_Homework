#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct trie {
  trie *children[36];
  set<int> *indexes = NULL;
};

trie *branch;
int post;

set<int> *search(trie *tree, vector<int> &word) {
  branch = tree;
  for (post = 0; post < word.size(); post++) {
    branch = branch->children[word[post]];
    if (!branch)
      return NULL;
  };
  return branch->indexes;
};


void put_word (trie *tree, vector<int> &word, int index) {
  branch = tree;
  for (post = 0; branch and post < word.size(); post++) {
    if (!branch->children[word[post]])
      branch->children[word[post]] = new trie();
    branch = branch->children[word[post]];
  };
  if (!branch->indexes)
    branch->indexes = new set<int> ();
  branch->indexes->insert(index);
};
