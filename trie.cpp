#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <math.h>
#include "text_processing.cpp"

using namespace std;

struct trie {
  trie *children[36];
  vector<int> *indexes = NULL;
};

trie *branch;
int post;

vector<int> *search(trie *tree, const vector<int> &word) {
  branch = tree;
  for (post = 0; post != word.size(); post++) {
    branch = branch->children[word[post]];
    if (!branch)
      return NULL;
  };
  return branch->indexes;
};

void put_word (trie *tree, const vector<int> &word, const int &index) {
  branch = tree;
  for (post = 0; branch and post < word.size(); post++) {
    if (!branch->children[word[post]])
      branch->children[word[post]] = new trie();
    branch = branch->children[word[post]];
  };
  if (!branch->indexes)
    branch->indexes = new vector<int> ();
  if (find(branch->indexes->begin(), branch->indexes->end(), index) == branch->indexes->end())
    branch->indexes->push_back(index);
};

void read_and_insert(trie* tree, vector<PTI*>& Titulos) {
	vector < vector <int> > Line_words;
	string titulo, line;
	int i = 0;
	size_t inicio_do_titulo, fim_do_titulo;
	PTI* novo_titulo;
	for (int page_index = 1; page_index < 16; page_index++) {
		ifstream File("wikiCorpus (" + to_string(page_index) + ")");
		if (File.is_open()) {
			while (getline(File, line)) {
				if (line == "ENDOFARTICLE.") {
					i = -1;
				}
				else {
					i++;
					if (i < 2) {
						inicio_do_titulo = line.find("title");
						if (inicio_do_titulo != string::npos) {
							inicio_do_titulo += 7;
							fim_do_titulo = line.find(" non");
							titulo = line.substr(inicio_do_titulo, fim_do_titulo - inicio_do_titulo - 1);
							novo_titulo = new PTI();
							novo_titulo->titulo = titulo;
							novo_titulo->indice = Titulos.size() + 1;
							Titulos.push_back(novo_titulo);
						}
					}
					else {
						convert(line);
						Line_words = word_breaker(line);
						for (vector < vector <int> >::iterator it = Line_words.begin(); it != Line_words.end(); it++) {
							if (!it->empty()) {
								put_word(tree, *it, Titulos.size());
							}
						}
					}
				}
			}
			File.close();
		}
	}
}

void read_and_insert2(trie* tree) {
	//variables used
	vector < vector <int> > Line_words;
	string line;
	int text_counter = 1;
	ifstream File("sorted_text.txt");

	if (File.is_open())
	{
		while (getline(File, line))
		{
			convert(line);
			Line_words = word_breaker(line);
			for (vector < vector <int> >::iterator it = Line_words.begin(); it != Line_words.end(); it++)
			{
				if (!it->empty())    put_word(tree, *it, text_counter);
			}
			text_counter++;
		}
		File.close();
	}
}
