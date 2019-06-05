// Bruno
#include <string>
#include <vector>

using namespace std;

struct PTT {
	string titulo;
	string texto;
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

string dicionario_acentuado = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"; //todos os caracteres acentuados
string dicionario = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy"; //todas os caracteres acentuados, so que desacentuados
size_t found;
void convert(string& s) {
	//Essa funcao converte todo o texto em minusculo, tira a pontuacao e divide palavras por '*'
	s.push_back(' '); //acrescentando um espaco no final do texto
	for (int i = 0; i < s.length(); i++) {
		found = dicionario_acentuado.find(s[i]);
		if (found != string::npos) {
			s[i] = dicionario[found];
		}
    if (isalnum(s[i]))
      s[i] = tolower(s[i]);
    else
      s[i] = '*';
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
