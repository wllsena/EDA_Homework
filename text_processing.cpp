// Bruno
#include <string>
#include <vector>

using namespace std;

struct PTI {
	string titulo;
	int indice;
};

bool my_isalnum(const char& c) {
	int ascii_value = int(c);
	return (ascii_value >= 48 and ascii_value <= 57) or (ascii_value >= 65 and ascii_value <= 90) or (ascii_value >= 97 and ascii_value <= 122);
}

string dicionario = "aaaaaaeceeeeiiiidnooooox0uuuuypsaaaaaaeceeeeiiiionooooo0uuuuypy";
void convert(string& s) {
	//Essa funcao converte todo o texto em minusculo, tira a pontuacao e divide palavras por '*'
  s.push_back(' '); //acrescentando um espaco no final do texto
	for (int i = 0; i < s.length(); i++) {
    if (int(s[i]) == -61 and i + 1 != s.length()) {
      s[i+1] = dicionario[int(s[i+1]) + 128];
			s.erase(i, 1);
      i--;
    } else if (my_isalnum(s[i]))
			s[i] = tolower(s[i]);
		else if ((s[i] == '\'' or s[i] == '-') and i != 0 and i + 1 != s.length() and my_isalnum(s[i - 1]) and my_isalnum(s[i + 1])) {
			s.erase(i, 1);
			i--;
		}
		else if (int(s[i]) >= 0 and i != 0 and s[i - 1] != '*')
			s[i] = '*';
		else {
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
			if (!palavra.empty())
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
			if (palavra != "")
				Palavras.push_back(palavra);
			palavra.clear();
		}
		else {
			palavra.push_back(s[i]);//c.c. adicione outra letra na palavra
		}
	}
	return Palavras;
}
