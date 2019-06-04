#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include "organize_text.cpp"
#include "trie.cpp"

namespace bio = boost::iostreams;
using namespace std;

bio::mapped_file_params params;
int number_of_pages = 1359146;

vector<string> file_names() {
  // William
  vector<string> files;
  string file;
  ifstream File("files_names.txt");
  if (File.is_open()) {
    while (getline(File, file))
      files.push_back("raw.en/" + file);
  };
  return files;
};

void save_text(PTT *text) {
  // Bruno
  ofstream sorted_titles;
	ofstream sorted_text;

	sorted_titles.open("sorted_titles.txt");
	sorted_text.open("sorted_text.txt");

	for (int i = 0; i <  number_of_pages; i++) {
		sorted_titles << text[i].titulo;
		sorted_titles << "\n";
		sorted_text << text[i].texto;
		sorted_text << "\n";
	};

	sorted_titles.close();
	sorted_text.close();
};

void read_and_insert (disk_trie *tree, int *counters, int *indexes, bool counter_or_index) {
  // Bruno
	vector <vector<int> > Line_words;
  vector <vector<int> > old_words;
	string line;
	ifstream File("sorted_text.txt");

	if (File.is_open()) {
    if (counter_or_index) {
      while (getline(File, line)) {
        old_words.clear();
        convert(line);
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
        convert(line);
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
  system("rm temporary & rm trie_structure & rm counters & rm indexes & rm sorted_titles.txt & rm sorted_text.txt");
  vector<string> files = file_names();

  params.path          = "temporary";
  params.new_file_size = 4000000000;
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink Text(params);

  PTT * text = (PTT *)Text.data();
  organize_text(text, files);
  save_text(text);

  Text.close();
  files.clear();

  system("rm temporary");

  params.path          = "trie_structure";
  params.new_file_size = number_of_tries*sizeof(disk_trie);
  params.flags         = bio::mapped_file::mapmode::readwrite;
  bio::mapped_file_sink Trie_structure(params);
  disk_trie * disk_tree = (disk_trie *)Trie_structure.data();

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
  int current, accumulated = 0;
  for(int i = 0; i < number_of_tries; i++) {
    current = counters[i];
    counters[i] = accumulated;
    accumulated += current + 1;
  };
  read_and_insert(disk_tree, counters, indexes, false);

  Trie_structure.close();
  Counters.close();
  Indexes.close();
};
