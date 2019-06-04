#include <vector>

using namespace std;

struct disk_trie {
  int children[36];
  int kinship[2];
};

struct trie {
  trie *children[36];
  int index;
};

int disk_branch, position, counter;
int trie_position = 1;
int number_of_tries = 8233674;
int number_of_indexes = 0 + number_of_tries; // mudar
unsigned int global_counter = 0; // remover
trie *branch;

void put_word_and_counter (disk_trie *tree, int *counters, const vector<int> &word) {
  disk_branch = 0;
  for (position = 0; position != word.size(); position++) {
    if (!tree[disk_branch].children[word[position]]) {
      tree[disk_branch].children[word[position]] = trie_position;
      tree[trie_position].kinship[0] = disk_branch;
      tree[trie_position].kinship[1] = word[position];
      trie_position++;
    };
    disk_branch = tree[disk_branch].children[word[position]];
  };
  counters[disk_branch]++;
  global_counter++; // remover
};

int disk_search(const disk_trie *tree, const vector<int> &word) {
  disk_branch = 0;
  for (position = 0; position != word.size(); position++) {
    disk_branch = tree[disk_branch].children[word[position]];
    if (!disk_branch)
      return 0;
  };
  return disk_branch;
};

void put_index (int *indexes, const disk_trie *tree, const int *counters, const vector<int> &word, const int &index) {
  counter = counters[disk_search(tree, word)];
  indexes[counter]++;
  indexes[counter + indexes[counter]] = index;
};

int search(trie *tree, const vector<int> &word) {
  branch = tree;
  for (position = 0; position != word.size(); position++) {
    branch = branch->children[word[position]];
    if (!branch)
      return 0;
  };
  return branch->index;
};

trie *load_trie (const disk_trie *disk_tree) {
  vector<trie *> pointers(number_of_tries);
  pointers[0] = new trie();
  for (position = 1; position < number_of_tries; position++) {
    pointers[position] = new trie();
    pointers[position]->index = position;
    pointers[disk_tree[position].kinship[0]]->children[disk_tree[position].kinship[1]] = pointers[position];
  };
  return pointers[0];
};
