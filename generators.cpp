// William and Bruno
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <fstream>
#include "text_processing.cpp"
#include "trie.cpp"

namespace bio = boost::iostreams;

void read_and_insert_counter (disk_trie_wc *tree) {
  // Bruno
	vector <vector<int> > Line_words;
  vector <vector<int> > old_words;
	string line;
	ifstream File("sorted_words_to_insert.txt");
	if (File.is_open()) {
    while (getline(File, line)) {
      old_words.clear();
      Line_words = word_breaker(line);
      for (vector<int> word : Line_words) {
        if (!word.empty() and find(old_words.begin(), old_words.end(), word) == old_words.end()) {
          put_word_and_counter(tree, word);
          old_words.push_back(word);
        };
      };
    };
  };
  File.close();
};

void read_and_insert_index (const disk_trie *tree, const disk_trie_wc *tree_wc, int *indexes) {
  // Bruno
	vector <vector<int> > Line_words;
  vector <vector<int> > old_words;
	string line;
	ifstream File("sorted_words_to_insert.txt");
  if (File.is_open()) {
    int text_counter = 0;
    while (getline(File, line)) {
      old_words.clear();
      Line_words = word_breaker(line);
      for (vector<int> word : Line_words) {
        if (!word.empty() and find(old_words.begin(), old_words.end(), word) == old_words.end()) {
          put_index(indexes, tree, tree_wc, word, text_counter);
          old_words.push_back(word);
        };
      }
      text_counter++;
    };
  };
  File.close();
};

int main () {
  // William
  bio::mapped_file_params params;

  params.path          = "tries_wc";
  params.new_file_size = number_of_tries*sizeof(disk_trie_wc);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink Tries_wc(params);
  disk_trie_wc * disk_tree_wc = (disk_trie_wc *)Tries_wc.data();

  read_and_insert_counter(disk_tree_wc);

  params.path          = "tries";
  params.new_file_size = number_of_tries*sizeof(disk_trie);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink Tries(params);
  disk_trie * disk_tree = (disk_trie *)Tries.data();

  generate_tries(disk_tree, disk_tree_wc);

  params.path          = "indexes";
  params.new_file_size = number_of_indexes*sizeof(int);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink Indexes(params);
  int * indexes = (int *)Indexes.data();

  read_and_insert_index(disk_tree, disk_tree_wc, indexes);

  Tries_wc.close();
  Tries.close();
  Indexes.close();
};
