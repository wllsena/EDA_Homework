//William
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include "word_suggestor.cpp"
#include "print_results.cpp"

using namespace std;
namespace bio = boost::iostreams;
vector<vector<int> > words; vector<unsigned int> intersect; vector<int> wnull; int size, stance; string word = ""; bool suggest = false;
auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed;
bio::mapped_file_params params;

int main () {
  // Part 1
  cout << "… Loading index done!" << endl;

  params.path          = "tries";
  params.new_file_size = number_of_tries*sizeof(disk_trie);
  bio::mapped_file_source Tries(params);
  disk_trie * disk_tree = (disk_trie *)Tries.data();

  params.path          = "counters";
  params.new_file_size = number_of_tries*sizeof(unsigned int);
  bio::mapped_file_source Counters(params);
  unsigned int * counters = (unsigned int *)Counters.data();

  params.path          = "indexes";
  params.new_file_size = number_of_indexes*sizeof(unsigned int);
  bio::mapped_file_source Indexes(params);
  unsigned int * indexes = (unsigned int *)Indexes.data();

  trie *tree = load_trie(disk_tree);
  Tries.close();

	for (int i = 0; i != 36; i++) wnull.push_back(i);

  // Part 2
	while (true) {
    if (!suggest) {
      cout << "Enter your query: ";
      getline(cin >> ws, word);
      suggest = true;
    };

		convert(word);
		words = word_breaker(word);
		size = words.size();
		unsigned int results[size];
		search(tree, wnull);

    // SEARCH - START
		start = chrono::high_resolution_clock::now();
		for (stance = 0; stance != size; stance++)
			results[stance] = search(tree, words[stance]);
		finish = chrono::high_resolution_clock::now();
		elapsed = finish - start;
    // SEARCH - END

    intersect = intersection(results, counters, indexes, size);
    cout << ".. About " << intersect.size() << " results (" << elapsed.count() << " seconds or " << 1000000*elapsed.count() << " microseconds)\n";

    if (intersect.size()) {
      print_results(intersect);
      suggest = false;
    } else if (suggest) {
      word = suggestion(tree, word_breaker2(word), counters, indexes);
      suggest = word != "";
    };
  };

  Counters.close();
  Indexes.close();
  return 0;
};
