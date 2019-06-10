//Bruno
#include <unordered_set>
#include <iostream>
#include "text_processing.cpp"
#include "trie.cpp"

using namespace std;

int min_edit_distance (string& p1, string& p2) {
	int m = p1.size(), n = p2.size(), I = 1, R = 1, S = 1;
	vector <int> linha (n, 0);
	vector < vector <int> > table (m,linha);
	//Inserindo os valores iniciais na matriz/array bidimensional
	for (int i = 0; i < max(m, n); i++) {
		if (i < m) {
			table[i][0] = i;
		}
		if (i < n) {
			table[0][i] = i;
		}
	}
	//Itere por todas as colunas de todas as linhas seguindo a logica do algoritmo
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (p1[i-1] == p2[j-1]) {
				table[i][j] = table[i-1][j-1];
			}
			else {
				table[i][j] = min(table[i - 1][j] + I, min( table[i][j - 1] + R, table[i - 1][j - 1] + S) );
			}
		}
	}
	//O minimum edit distance esta no ultimo elemento da diagonal
	return table[m-1][n-1];
}
string alphabet = "abcdefghijklmnopqrstuvwxyz";

void edits1(const string& error, unordered_set<string>& wordSet)
{
	wordSet.clear();
	std::string word;
	int len = error.size();
	int len_alphabet = alphabet.size();
	//deletes
	for (int i = 0; i < len; ++i)
    {
      word = error;
      word.erase(i, 1);
      wordSet.insert(word);
    }
	//transposes
	for (int i = 0; i < len - 1; ++i)
    {
      word = error;
      std::swap(word[i], word[i+1]);
      wordSet.insert(word);
    }
	//replaces
	for (int i = 0; i < len; ++i)
    {
      for (int j = 0; j < len_alphabet; ++j)
        {
          word = error;
          word[i] = alphabet[j];
          wordSet.insert(word);
        }
    }
	//inserts
	for (int i = 0; i < len + 1; ++i)
    {
      for (int j = 0; j < len_alphabet; ++j)
        {
          word = error;
          word.insert(i, 1, alphabet[j]);
          wordSet.insert(word);
        }
    }
}

void edits2(const std::string& error, std::unordered_set<std::string>& words2)
{
	words2.clear();
	std::unordered_set<std::string> words1;
	edits1(error, words1);
	std::unordered_set<std::string> tmp_words2;
	for (const auto& word1 : words1)
    {
      edits1(word1, tmp_words2);
      for (const auto& word : tmp_words2)
        {
          words2.insert(word);
        }
    }
}

string MostFrequent(trie* tree, unordered_set<string>& candidates, const int *indexes)
{
	std::string answer;
	size_t max_count = 0;
	int found, length = 0;
	for (auto word : candidates)
    {
      convert(word);
      found = indexes[search(tree, word_breaker(word)[0])];

      if (length > max_count)
        {
          max_count = found;
          word.pop_back();
          answer = word;
        }
    }
	return answer;
}

string correct(trie* tree, string error, const int *indexes)
{
	string error1 = error;
	convert(error1);
	if (search(tree, word_breaker(error1)[0]))
		return error;
	std::unordered_set<std::string> candidates;
	error1.pop_back();
	edits1(error1, candidates);
	string answer = MostFrequent(tree, candidates, indexes);
	if (!answer.empty())
		return answer;
	edits2(error1, candidates);
	answer = MostFrequent(tree, candidates, indexes);
	if (!answer.empty())
		return answer;
	return error;
}

string suggestion(trie* tree, vector<string> query, const int *indexes) {
	bool not_found = false;
	string right_query;
	for (int i = 0; i < query.size(); i++)
    {
      right_query = correct(tree, query[i], indexes);
      if (right_query != query[i]) {
        not_found = true;
        query[i] = right_query;
      }
    }
	if (not_found)
    {
      string answer;
      cout << "Did you mean \"";
      for (auto word : query)
        {
          if (word != "*") cout << word << " ";
        }

      cout << "\" (y,n)? ";
      getline(cin >> ws, answer);
      if (answer == "y")
        {
          string word;
          for (auto w : query) word.append(w + " ");
          return word;
        }
    } else
    cout << "No word suggestions" << endl;
	return "";
};
