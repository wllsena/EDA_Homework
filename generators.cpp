// William and Bruno
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <fstream>
#include "text_processing.cpp"
#include "trie.cpp"

namespace bio = boost::iostreams;

//const int number_of_pages = 1359146;

void read_and_insert (disk_trie *tree, int *counters, int *indexes, const bool counter_or_index) {
  // Bruno
	vector <vector<int> > Line_words;
  vector <vector<int> > old_words;
	string line;
	ifstream File("words_to_insert.txt");

	if (File.is_open()) {
    if (counter_or_index) {
      while (getline(File, line)) {
        old_words.clear();
        Line_words = word_breaker(line);
        for (vector<int> word : Line_words) {
          if (!word.empty() and find(old_words.begin(), old_words.end(), word) == old_words.end()) {
            put_word_and_counter(tree, counters, word);
            old_words.push_back(word);
          };
        };
      };
    } else {
      int text_counter = 0;
      while (getline(File, line)) {
        old_words.clear();
        Line_words = word_breaker(line);
        for (vector<int> word : Line_words) {
          if (!word.empty() and find(old_words.begin(), old_words.end(), word) == old_words.end()) {
            put_index(indexes, tree, counters, word, text_counter);
            old_words.push_back(word);
          };
        }
        text_counter++;
      };
    };
    File.close();
  };
};

int main () {
  // William
  bio::mapped_file_params params;

  params.path          = "tries";
  params.new_file_size = number_of_tries*sizeof(disk_trie);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink Tries(params);
  disk_trie * disk_tree = (disk_trie *)Tries.data();

  params.path          = "counters";
  params.new_file_size = number_of_tries*sizeof(int);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink Counters(params);
  int * counters = (int *)Counters.data();

  params.path          = "indexes";
  params.new_file_size = number_of_indexes*sizeof(int);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink Indexes(params);
  int * indexes = (int *)Indexes.data();

  read_and_insert(disk_tree, counters, indexes, true);
  accumulate_counters(counters);
  read_and_insert(disk_tree, counters, indexes, false);

  Tries.close();
  Counters.close();
  Indexes.close();
};
