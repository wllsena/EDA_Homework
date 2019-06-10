//William
#include <vector>

using namespace std;

const int number_of_tries = 14175000;
const int number_of_indexes = 260490000;

struct disk_trie_wc { // wc -> with children
  int children[36];
  int kinship[2];
  int counter = 0;
};

struct disk_trie {
  int kinship[2];
  int index;
};

struct trie {
  trie *children[36];
  int index;
};

int branch_word, position_word, trie_position = 1;
void put_word_and_counter (disk_trie_wc *tree, const vector<int> &word) {
  branch_word = 0;
  for (position_word = 0; position_word != word.size(); position_word++) {
    if (!tree[branch_word].children[word[position_word]]) {
      tree[branch_word].children[word[position_word]] = trie_position;
      tree[trie_position].kinship[0] = branch_word;
      tree[trie_position].kinship[1] = word[position_word];
      trie_position++;
    };
    branch_word = tree[branch_word].children[word[position_word]];
  };
  tree[branch_word].counter++;
};

void generate_tries (disk_trie *tree, const disk_trie_wc *tree_wc) {
  int temp; // remover
  for(int i = 0, accumulated = 0; i != number_of_tries; i++) { // mudar
    tree[i].index = accumulated;
    tree[i].kinship[0] = tree_wc[i].kinship[0];
    tree[i].kinship[1] = tree_wc[i].kinship[1];
    accumulated += (tree_wc[i].counter + 1);
    temp = accumulated; // remover
  };
};

int branch_index, position_index, counter_index;
void put_index (int *indexes, const disk_trie *tree, const disk_trie_wc *tree_wc, const vector<int> &word, const int &index) {
  branch_index = 0;
  for (position_index = 0; position_index != word.size(); position_index++)
    branch_index = tree_wc[branch_index].children[word[position_index]];
  counter_index = tree[branch_index].index;
  indexes[counter_index]++;
  indexes[counter_index + indexes[counter_index]] = index;
};

trie *load_trie (const disk_trie *disk_tree) {
  vector<trie *> pointers(number_of_tries);
  pointers[0] = new trie();
  pointers[0]->index = 0;
  for (int position = 1; position != number_of_tries; position++) {
    pointers[position] = new trie();
    pointers[position]->index = disk_tree[position].index;
    pointers[disk_tree[position].kinship[0]]->children[disk_tree[position].kinship[1]] = pointers[position];
  };
  return pointers[0];
};

trie *branch_search; int position_search;
int search(trie *tree, const vector<int> &word) {
  branch_search = tree;
  for (position_search = 0; position_search != word.size(); position_search++) {
    branch_search = branch_search->children[word[position_search]];
    if (!branch_search)
      return 0;
  };
  return branch_search->index;
};
