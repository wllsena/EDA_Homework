#include <string>
#include <fstream>
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

void convert(string& s) {
	//Essa funcao converte todo o texto em minusculo, tira a pontuacao e divide palavras por '*'
	string dicionario = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy"; //todas os caracteres acentuados, so que desacentuados

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