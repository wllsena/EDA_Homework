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
int num;

set<int> *search2(trie *tree, string &word) {
  branch = tree;
  for (post = 0; branch and word[post] != '\0'; post++) {
    num = int(word[post]);
    branch = branch->children[num - (num > 57 ? 87 : 48)];
  };
  return branch->indexes;
};


void put_word2 (trie *tree, string word, int index) {
  branch = tree;
  for (post = 0; word[post] != '\0'; post++) {
    num = int(word[post]) - (int(word[post]) > 57 ? 87 : 48);
    if (!branch->children[num])
      branch->children[num] = new trie();
    branch = branch->children[num];
  };
  if (!branch->indexes)
    branch->indexes = new set<int> ();
  branch->indexes->insert(index);
};

set<int> *search(trie *tree, vector<int> &word) {
  branch = tree;
  for (post = 0; branch and post < word.size(); post++) {
    branch = branch->children[word[post]];
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
