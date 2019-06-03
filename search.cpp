#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include "trie.cpp"

using namespace std;
namespace bio = boost::iostreams;

bio::mapped_file_params params;

int main () {
  params.path          = "trie_structure";
  params.new_file_size = number_of_tries*sizeof(disk_trie);
  bio::mapped_file_source Trie_structure(params);

  params.path          = "counters";
  params.new_file_size = number_of_tries*sizeof(int);
  bio::mapped_file_source Counters(params);

  params.path          = "indexes";
  params.new_file_size = number_of_indexes*sizeof(int);
  bio::mapped_file_source Indexes(params);

  disk_trie * disk_tree = (disk_trie *)Trie_structure.data();
  int * counters = (int *)Counters.data();
  int * indexes = (int *)Indexes.data();

  trie *tree = load_trie(disk_tree);
  Trie_structure.close();

  vector<int> fuck;
  search(tree, fuck);
};
