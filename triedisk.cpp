#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>
#include <vector>

using namespace std;
namespace bio = boost::iostreams;

bio::mapped_file_params params;
auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed;

struct trie {
  char children[36];
};

struct data {
  bool indexes[1359146];
};

short branch, posit;
int positTrie = 1;

void put_word (trie *wiki, data *indexes, const vector<char> &word, int &index) {
  branch = 0;
  for (posit = 0; posit != word.size(); posit++) {
    if (!wiki[branch].children[word[posit]]) {
      wiki[branch].children[word[posit]] = positTrie;
      positTrie++;
    };
    branch = wiki[branch].children[word[posit]];
  };
  indexes[branch].indexes[index] = true;
};

int search(const trie *wiki, const vector<char> &word) {
  branch = 0;
  for (posit = 0; posit != word.size(); posit++) {
    branch = wiki[branch].children[word[posit]];
    if (!branch)
      return 0;
  };
  return branch;
};

int main () {
  int numberOfTries = 100;

  params.path          = "wiki.trie";
  params.new_file_size = numberOfTries*sizeof(trie);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink triedisk(params);

  params.path          = "wiki.indexes";
  params.new_file_size = numberOfTries*sizeof(data);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink indexes(params);

  trie * wiki = (trie *)triedisk.data();
  data * indexs = (data *)indexes.data();

  int index = 1;
  put_word(wiki, indexs, {0, 1, 2, 3}, index);
  put_word(wiki, indexs, {0, 1, 2, 4}, index);

  start = chrono::high_resolution_clock::now();
  cout << search(wiki, {0, 1, 2, 4}) << endl;
  finish = chrono::high_resolution_clock::now();
  elapsed = finish - start;

  cout << "About " << 0 << " results (" << 1000000*elapsed.count() << " microseconds)\n";
};
