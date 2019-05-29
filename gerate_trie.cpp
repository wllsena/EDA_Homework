#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "trie.cpp"

using namespace std;


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
		else if (int(s[i]) < 48 || (int(s[i]) > 57 && int(s[i]) < 97) || (int(s[i]) > 122)) {//se for traco ou apostrofo, apaga
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


void read_and_insert(trie* tree, vector<string>& Titulos) {
	vector < vector <int> > Palavras_da_linha;
	string titulo, line;
	int i = 0;
	size_t inicio_do_titulo, fim_do_titulo;
	for (int page_index = 1; page_index < 11; page_index++) {
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
							Titulos.push_back(titulo);
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
