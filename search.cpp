//William
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include "text_processing.cpp"
#include "print_results.cpp"
#include "trie.cpp"

using namespace std;
namespace bio = boost::iostreams;
vector<vector<int> > words; vector<int> wnull, intersect; int i, size, stance; string word;
auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed;
bio::mapped_file_params params;

int main () {
  // William
  // Part 1
  cout << "… Loading index done!" << endl;

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

	for (i = 0; i < 36; i++) wnull.push_back(i);

  // Part 2
	while (true) {
    cout << "Enter your query: ";
    getline(cin >> ws, word);

		convert(word);
		words = word_breaker(word);
		size = words.size();
		int results[size];
		search(tree, wnull);

    // SEARCH - START
		start = chrono::high_resolution_clock::now();
		for (stance = 0; stance < size; stance++)
			results[stance] = search(tree, words[stance]);
		finish = chrono::high_resolution_clock::now();
		elapsed = finish - start;
    // SEARCH - END

    intersect = intersection(results, counters, indexes, size);
    cout << ".. About " << intersect.size() << " results (" << elapsed.count() << " seconds or " << 1000000*elapsed.count() << " microseconds)\n";
    print_results(intersect);
  };

  Counters.close();
  Indexes.close();
  return 0;
};
