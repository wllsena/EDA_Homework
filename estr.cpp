#include <iostream>
#include <vector>

using namespace std;

struct trie {
  trie *children[4];
  vector<int> links;

  trie(vector<int> nums): links(nums) {};
};


void put_word(trie words, string word) {
  int i = 0;
  
  while (true) {
    //if (word[i] != '\0') {
    //pBranch->indexes = indexes;
    //return;
    //};
    //if (pBranch->children[int(word[i]-96)])
       //  pBranch = &(pBranch->children[int(word[i]-96)]);
    i ++;
  }
};

int main() {
  vector<int> vec1, vec2;
  vec1.push_back(1);
  vec1.push_back(2);
  vec1.push_back(3);

  trie *a = new trie(vec1);
  trie *b = new trie(vec1);
  trie *c = new trie(vec2);

  a->children[0] = NULL;
  a->children[2] = NULL;
  a->children[3] = NULL;
  a->children[1] = b;
  c->children[0] = a;

  for (int i = 0; i < 4; i++) {
    if ((c->children[0])->children[i])
      cout << i << "\n";
    else
      cout << "--" << i << "\n";
	}
}
