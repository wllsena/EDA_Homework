#include <string>
#include <fstream>
#include "trie.cpp"
#include <algorithm>
#include <set>
#include <math.h>

using namespace std;

struct PTT {
	string titulo;
	string texto;
};

struct PTI {
	string titulo;
	int indice;
};

int compare_string(string p1, string p2) {
	for (int i = 0; i < min(p1.size(), p2.size()); i++)
	{
		if (int(p1[i]) < int(p2[i]))
		{
			return true;
		}
		else if (int(p1[i]) > int(p2[i]))
		{
			return false;
		}
	}
	return false;
}

void quickSort(vector<PTI*> &vetor, int began, int end)
{
	int i, j;
	PTI* aux = new PTI(), *pivo = vetor[floor( (began + end)/2 )];
	i = began;
	j = end - 1;
	while (i <= j)
	{

		while (compare_string(vetor[i]->titulo, pivo->titulo) && i < end)
		{
			i++;
		}

		while (compare_string(pivo->titulo, vetor[j]->titulo) && j > began)
		{
			j--;
		}
		if (i <= j)
		{
			aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
			i++;
			j--;
		}
	}
	if (j > began)
		quickSort(vetor, began, j + 1);
	if (i < end)
		quickSort(vetor, i, end);
}

void convert(string& s) {
	//Essa funcao converte todo o texto em minusculo, tira a pontuacao e divide palavras por '*'
	string dicionario = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy"; //todas os caracteres acentuados, so que desacentuados
	int k;

	s.push_back(' '); //acrescentando um espaco no final do texto
	for (int i = 0; i < s.length(); i++) {
		if (int(s[i]) <= -1 && int(s[i]) >= -64) {
			s[i] = dicionario[int(s[i]) + 64]; //se tiver acento, tira o acento
		}
		s[i] = tolower(s[i]);

		if (int(s[i]) >= 0 && (ispunct(s[i]) || s[i] == ' ')) { //se for pontuacao ou espaco substitui por '*'
			s[i] = '*';
		}
		else if (int(s[i]) < 48 || (int(s[i]) > 57 && int(s[i]) < 97) || (int(s[i]) > 122)) {//se nao for um dos caracteres aceitos, apague
			s.erase(i, 1);
			i--;
		}
	}
}


vector < vector <int> > word_breaker(string& s) {
	//Essa funcao pega o resultado da funcao 'convert' e retorna um vetor com todas as palavras
	//do texto
	vector < vector <int> > Palavras;
	vector <int> palavra;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '*') {//se chegou no fim da palavra, adicione-a ao vetor e delete o conteudo atual
			Palavras.push_back(palavra);
			palavra.clear();
		}
		else {
			palavra.push_back(int(s[i]) - (int(s[i]) > 57 ? 87 : 48));//c.c. adicione o codigo de outra letra na palavra
		}
	}
	return Palavras;
}

vector <string> word_breaker2(string& s) {
	//Essa funcao pega o resultado da funcao 'convert' e retorna um vetor com todas as palavras
	//do texto
	vector <string> Palavras;
	string palavra;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '*') {//se chegou no fim da palavra, adicione-a ao vetor e delete o conteudo atual
			Palavras.push_back(palavra);
			palavra.clear();
		}
		else {
			palavra.push_back(s[i]);//c.c. adicione outra letra na palavra
		}
	}
	return Palavras;
}



void read_and_insert(trie* tree, vector<PTI*>& Titulos) {
	vector < vector <int> > Palavras_da_linha;
	string titulo, line;
	int i = 0;
	size_t inicio_do_titulo, fim_do_titulo;
	PTI* novo_titulo;
	for (int page_index = 1; page_index < 2; page_index++) {
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
						Palavras_da_linha = word_breaker(line);
						for (vector < vector <int> >::iterator it = Palavras_da_linha.begin(); it != Palavras_da_linha.end(); it++) {
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


void organize_text(vector<PTT*>& Titulos,set<vector<int>>& word_dict) {
	string titulo, line, texto;
	PTT* novo_titulo;
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
