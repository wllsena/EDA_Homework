#include <iostream>
#include <vector>

using namespace std;

struct trie {
  trie *children[36];
  vector<int> *indexes = NULL;
};

trie *branch;
int post;

vector<int> *search(trie *tree, const vector<int> &word) {
  branch = tree;
  for (post = 0; post != word.size(); post++) {
    branch = branch->children[word[post]];
    if (!branch)
      return NULL;
  };
  return branch->indexes;
};

void put_word (trie *tree, const vector<int> &word, const int &index) {
  branch = tree;
  for (post = 0; branch and post < word.size(); post++) {
    if (!branch->children[word[post]])
      branch->children[word[post]] = new trie();
    branch = branch->children[word[post]];
  };
  if (!branch->indexes)
    branch->indexes = new vector<int> ();
  if (find(branch->indexes->begin(), branch->indexes->end(), index) == branch->indexes->end())
    branch->indexes->push_back(index);
};
