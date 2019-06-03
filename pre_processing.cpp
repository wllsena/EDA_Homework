#include "text_processing.cpp"
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <math.h>


using namespace std;
int COUNT = 0; // used to count how many pages I have read in "organize_text()"


void alphabetical_insert(PTT original, PTT* Titulos) {
	PTT to_insert = original;
	for (int i = 0; i < COUNT; i++) 
	{
		if ( compare_string(to_insert.titulo, Titulos[i].titulo) )
		{
			for (int k = COUNT - 1; k >= i; k--)
			{
				Titulos[k + 1] = Titulos[k];
			}
			Titulos[i] = to_insert;
			return;
		}
	}
	Titulos[COUNT] = to_insert;
	return;
}


void organize_text(PTT* Titulos) {
	bool got_to_the_end = false;
	int i = 0;
	string title, line, text;
	PTT* new_title = new PTT();
	size_t title_begin, title_end; // 155
	for (int page_index = 1; page_index < 2; page_index++)
	{
		ifstream File("wikiCorpus (" + to_string(page_index) + ")");
		//ifstream File("Corpus");
		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line == "ENDOFARTICLE." && !new_title->titulo.empty())
				{
					i = -1;
					new_title->texto = text;
					if (COUNT == 0) Titulos[0] = *new_title;
					else alphabetical_insert(*new_title, Titulos);
					text.clear();
					COUNT++;
					got_to_the_end = true;
				}
				else
				{
					i++;
					if (i < 2)
					{
						title_begin = line.find("title");
						if (title_begin != string::npos)
						{
							title_begin += 7;
							title_end = line.find(" non");
							title = line.substr(title_begin, title_end - title_begin - 1);
							new_title->titulo = title;
						}
					}
					else
					{
						text.append(line);
						text.append("物");
						got_to_the_end = false;
						//convert(line);
						//line_words = word_breaker(line);
						//for (int k = 0; k < line_words.size(); k++) 
						//{
						//	word_dict.insert(line_words[k]);
						//}

					}
				}
			}
			if (!got_to_the_end && !new_title->titulo.empty())
			{
				i = -1;
				new_title->texto = text;
				alphabetical_insert(*new_title, Titulos);
				text.clear();
				COUNT++;
				got_to_the_end = true;
			}
		}
	}
}

void organize_text2(vector<PTT*>& Titulos, set<vector<int>>& word_dict) {
	//string titulo, line, texto;
	string line;
	//PTT* novo_titulo;
	int i = 0;
	vector<vector<int>> line_words;
	size_t inicio_do_titulo, fim_do_titulo;
	for (int page_index = 1; page_index < 155; page_index++)
	{
		ifstream File("wikiCorpus (" + to_string(page_index) + ")");
		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line == "ENDOFARTICLE.")
				{
					i = -1;
					//Titulos.back()->texto = texto;
					//texto.clear();
				}
				else
				{
					i++;
					if (i < 2)
					{/*
						inicio_do_titulo = line.find("title");
						if (inicio_do_titulo != string::npos)
						{
							inicio_do_titulo += 7;
							fim_do_titulo = line.find(" non");
							titulo = line.substr(inicio_do_titulo, fim_do_titulo - inicio_do_titulo - 1);
							novo_titulo = new PTT();
							novo_titulo->titulo = titulo;
							Titulos.push_back(novo_titulo);
						}*/
					}
					else
					{
						//texto.append(line);
						//texto.append("物");
						convert(line);
						line_words = word_breaker(line);
						for (int k = 0; k < line_words.size(); k++)
						{
							word_dict.insert(line_words[k]);
						}

					}
				}
			}
			File.close();
		}
	}
	//quickSort(Titulos, 0, Titulos.size());
}

