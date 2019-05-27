#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "trie.cpp"

using namespace std;


void convert(string &s){
  //Essa funcao converte todo o texto em minusculo, tira a pontuacao e divide palavras por '*'
  string dicionario = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy"; //todas os caracteres acentuados, so que desacentuados

  s.push_back(' '); //acrescentando um espaco no final do texto
  for (int i = 0; i < s.length(); i++){
    if (int(s[i]) < 0) s[i] = dicionario[int(s[i]) + 64]; //se tiver acento, tira o acento

    if (s[i] == '-' || int(s[i]) == 39){
      s.erase(i,1);
      i-=1;
    }else if (ispunct(s[i]) || (s[i]==' ') ){ //se for pontuacao ou espaco substitui por '*'
      s[i] = '*';
    }else{ //c.c. so deixa minusculo
      s[i] = tolower(s[i]);
    }
  }
}


vector <string> word_breaker(string &s){
  //Essa funcao pega o resultado da funcao 'convert' e retorna um vetor com todas as palavras
  //do texto
  vector <string> Palavras;
  string palavra;
  for (int i=0; i < s.length(); i++){
    if (s[i]=='*'){//se chegou no fim da palavra, adicione-a ao vetor e deleta o conteudo atual
      Palavras.push_back(palavra);
      palavra.erase(0);
    }else{
      palavra.push_back(s[i]);//c.c. adicione outra letra na palavra
    }
  }
  return Palavras;
}


void read_and_insert (trie *tree, vector<string> &Titulos){
  ifstream File ("pagina (1)");
  vector <string> Palavras_da_linha;
  string titulo,line;
  int i = 0;
  size_t inicio_do_titulo, fim_do_titulo;

  if (File.is_open()){
    while (Titulos.size() < 51){
      getline(File,line);
      if (line == "ENDOFARTICLE."){
        i=-1;
      }else{
        i+=1;
        if (i<2){
          inicio_do_titulo = line.find("title");
          if (inicio_do_titulo != string::npos){
            inicio_do_titulo+=7;
            fim_do_titulo = line.find(" non");
            titulo = line.substr(inicio_do_titulo,fim_do_titulo-inicio_do_titulo-1);
            Titulos.push_back(titulo);
          }
        }else{
          convert(line);
          Palavras_da_linha = word_breaker(line);
          for (vector<string>::iterator it = Palavras_da_linha.begin(); it != Palavras_da_linha.end(); it++){
            if (*it!="")
              put_word(tree, *it, Titulos.size());
          }
        }
      }
    }
    File.close();
  }
}
