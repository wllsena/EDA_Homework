#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct trie {
  vector<int> indexes;
  vector<trie> children;
};

void print(vector<int> const &input)
{
	for (int i = 0; i < input.size(); i++) {
		cout << input.at(i) << ' ';
	}
};

void put_word(vector<trie> &words, string word, vector<int> indexes) {
  trie* pBranch = &(words[int(word[0]-96)]);
  int i = 1;
  while (true) {
    if (word[i] != '\0') {
      pBranch->indexes = indexes;
      return;
    };
    //if ( != pBranch->children[int(word[i]-96)])
       // pBranch = &(pBranch->children[int(word[i]-96)]);
    i ++;
  }
};

int main() {
  vector<std::optional trie> child(4);
  vector<int> index;
  index.push_back(1);
  index.push_back(2);
  index.push_back(3);
  trie a, b, c;
  a.indexes = index;
  child[0] = a;
  child[1] = b;
  c.children = child;

  print(c.indexes);
  cout << "oi\n";
  print((c.children[0]).indexes);
  cout << "\n";


  int x = 0;
  char word[10];
  word[0] = 'a';
  word[2] = 'b';
  word[9] = 'c';
  while (word[x] != '\0')    // While the string isn't at the end...
    {
      cout << word[x] << "\n";    // Transform the char to int
      x++;
    }

  // string word;
  // int x = 0;
  // cout << "Please enter the word (maximum 32 characters):\n";
  // cin >> word;
  // cout << "The ASCII for this word is:\n";
  // while (word[x] != '\0')    // While the string isn't at the end...
  //   {
  //     cout << int(word[x])-97 << "\n";    // Transform the char to int
  //     x++;
  //   }
  // cout << "\n";

}

