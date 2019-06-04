#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include "trie.cpp"
#include <iostream>

using namespace std;
namespace bio = boost::iostreams;

bio::mapped_file_params params;

int main () {
  params.path          = "trie_structure";
  params.new_file_size = number_of_tries*sizeof(disk_trie);
  bio::mapped_file_source Trie_structure(params);
  disk_trie * disk_tree = (disk_trie *)Trie_structure.data();

  params.path          = "counters";
  params.new_file_size = number_of_tries*sizeof(int);
  bio::mapped_file_source Counters(params);
  int * counters = (int *)Counters.data();

  params.path          = "indexes";
  params.new_file_size = number_of_indexes*sizeof(int);
  bio::mapped_file_source Indexes(params);
  int * indexes = (int *)Indexes.data();

  trie *tree = load_trie(disk_tree);
  Trie_structure.close();

  vector<int> fuck;
  fuck.push_back(1);
  cout << search(tree, fuck) << endl;;

  Counters.close();
  Indexes.close();
};
