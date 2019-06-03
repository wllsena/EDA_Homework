#include <chrono>
#include "word_suggestor.cpp"

using namespace std;
bool no_suggestions = true;
vector<vector<int> > words; vector<PTI*> titles; vector<int> wnull; int position, williams_size, i, k; string word, answer, suggest;
vector<string> words_string_form;
auto inter = new vector<int> ();
auto start = chrono::high_resolution_clock::now();
auto finish = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed;

void print_titles(const vector<int> *indexes, const vector<PTI*> &titles) {
  if (indexes) {
    answer  = "";
    k = 0;
	vector<PTI*> searched_titles;
	for (vector<int>::const_iterator it = indexes->begin(); it != indexes->end(); it++) {
			searched_titles.push_back(titles[*it]);
	}
	cout << searched_titles.size() << endl;
    for (vector<PTI*>::const_iterator index = searched_titles.begin(); index != searched_titles.end() and answer != "n"; k++) {
      cout << "[" << k+1 << "] " << (*index)->titulo << endl;
      ++index;
      if (index != searched_titles.end() and k % 20 == 19) {
        cout << "More results? (y, n): ";
        getline(cin >> ws, answer);
      };
    };
    cout << "Do you want to open any result [n or result number]? ";
    getline(cin >> ws, answer);
    // TO-DO
  };
};

vector<int>* intersect(const vector<vector<int>*> &indexes, const int &size) {
  if (!indexes[0]) return NULL;
  inter = indexes[0];
  for (i = 1; i < size; i++) {
    if (!indexes[i]) return NULL;
    for (k = 0; k < inter->size(); k++) {
      if (find(indexes[i]->begin(), indexes[i]->end(), (*inter)[k]) == indexes[i]->end())
        (*inter)[k] = -1;
    };
  };
  if (size != 1)
    inter->erase(remove(inter->begin(), inter->end(), -1), inter->end());
  return inter;
};


int main() {
	for (i = 0; i < 36; i++) wnull.push_back(i);

	trie* tree = new trie();
	read_and_insert(tree, titles);

	cout << titles.size() << " titles\n";
	while (true) {
		vector<vector<int>*> indexes;
		if (no_suggestions)
		{
			cout << "Type a word to perform a search or \"!q\" if you want to quit: ";
			getline(cin >> ws, word);
		}
		if (word == "!q") return 0;
		convert(word);
		words = word_breaker(word);
		words_string_form = word_breaker2(word);
		williams_size = words.size();
		indexes.reserve(williams_size);
		search(tree, wnull);

		start = chrono::high_resolution_clock::now();
		for (position = 0; position < williams_size; position++)
			indexes[position] = search(tree, words[position]);
		finish = chrono::high_resolution_clock::now();
		elapsed = finish - start;


		inter = intersect(indexes, williams_size);
		cout << "About " << (inter ? inter->size() : 0) << " results (" << 1000000 * elapsed.count() << " microseconds)\n";
		print_titles(inter, titles);
		no_suggestions = true;

		suggest = suggestion(tree, words_string_form);

		if (suggest != "trabalhocustoso")
		{
			word = suggest;
			no_suggestions = false;
		}
		return 0;
	};
}