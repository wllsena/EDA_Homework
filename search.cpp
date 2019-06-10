//William
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include "word_suggestor.cpp"
#include "print_results.cpp"

using namespace std;
namespace bio = boost::iostreams;
vector<vector<int> > words; vector<int> intersect; vector<int> wnull; int size, stance; string word = ""; bool suggest = false;
auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed;
bio::mapped_file_params params;

int main () {
  cout << "... Loading index done!\n";

  // LOADING - START
  start = chrono::high_resolution_clock::now();
  params.path          = "tries";
  params.new_file_size = number_of_tries*sizeof(disk_trie);
  bio::mapped_file_source Tries(params);
  disk_trie * disk_tree = (disk_trie *)Tries.data();

  params.path          = "indexes";
  params.new_file_size = number_of_indexes*sizeof(int);
  bio::mapped_file_source Indexes(params);
  int * indexes = (int *)Indexes.data();

  trie *tree = load_trie(disk_tree);

	for (int i = 10; i != 36; i++) wnull.push_back(i);
  finish = chrono::high_resolution_clock::now();
  // LOADING - END

  elapsed = finish - start;
  cout << "(" << elapsed.count() << " seconds)\n";
	while (true) {
    if (!suggest) {
      cout << "Enter your query: ";
      getline(cin >> ws, word);
      suggest = true;
    };

		convert(word);
		words = word_breaker(word);
		size = words.size();
		int results[size];
		search(tree, wnull);

    // SEARCH - START
    start = chrono::high_resolution_clock::now();
		for (stance = 0; stance != size; stance++)
			results[stance] = search(tree, words[stance]);
		finish = chrono::high_resolution_clock::now();
    // SEARCH - END

		elapsed = finish - start;
    intersect = intersection(results, indexes, size);
    cout << "... About " << intersect.size() << " results (" << elapsed.count() << " seconds or " << 1000000*elapsed.count() << " microseconds)\n";

    if (intersect.size()) {
      print_results(intersect);
      suggest = false;
    } else if (suggest) {
      word = suggestion(tree, word_breaker2(word), indexes);
      suggest = word != "";
    };
  };

  Tries.close();
  Indexes.close();
  return 0;
};
