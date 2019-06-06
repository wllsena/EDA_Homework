// Bruno
#include <string>
#include <vector>

using namespace std;

string dicionario_acentuado = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ"; //todos os caracteres acentuados
string dicionario = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo0uuuuypy"; //todas os caracteres acentuados, so que desacentuados
size_t found;
void convert(string& s) {
	//Essa funcao converte todo o texto em minusculo, tira a pontuacao e divide palavras por '*'
	for (int i = 0; i < s.length(); i++) {
		found = dicionario_acentuado.find(s[i]);
		if (found != string::npos) {
			s[i] = dicionario[found];
		}
    if (isalnum(s[i]))
      s[i] = tolower(s[i]);
    else if ((s[i] == '\'' or s[i] == '-') and i != 0 and i + 1 != s.length() and isalnum(s[i-1]) and isalnum(s[i+1])) {
      s.erase(i, 1);
      i--;
    } else if (i != 0 and s[i-1] != '*')
      s[i] = '*';
    else {
      s.erase(i, 1);
      i--;
    }
	}
  if (s.length() != 0 and s[s.length()-1] != '*')
    s.push_back('*'); //acrescentando um espaco no final do texto
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
