#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;



//COISAS DO WILLIAM
struct trie {
  trie *children[26];
  vector<int> indexes;
};


void print(vector<int> vec) {
  for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i)
    cout << *i << ' ';
  cout << "\n";
};


void search(trie *tree, string word) {
  trie *branch = tree;
  int i = 0;
  while (true) {
    if (word[i] == '\0') {
      cout << "links :)\n";
      print(branch->indexes);
      return;
    };
    branch = branch->children[int(word[i])-97];
    if (branch)
      i++;
    else {
      cout << "no links :(\n";
      return;
    };
  };
};


trie* initialize_trie () {
  trie *tree = new trie();
  for (int i = 0; i < 26; i++) {
    tree->children[i] = NULL;
  };
  return tree;
};


void put_word (trie *tree, string word, int index) {
  trie *branch = tree;
  int i = 0;
  while (true) {
    if (word[i] == '\0') {
      branch->indexes.push_back(index);
      return;
    };
    if (branch->children[int(word[i])-97]) {
     branch = branch->children[int(word[i])-97];
     i++;
    } else {
      branch->children[int(word[i])-97] = initialize_trie();
    };
  };
};
//ACABARAM AS COISAS DO WILLIAM



//Declarando variaveis globais
vector <string> Titulos;
trie *tree = initialize_trie();


void convert(string &s){
    //Essa funcao converte todo o texto em minusculo, tira a pontuacao e divide palavras por '*'

    s.push_back(' '); //acrescentando um espaco no final do texto
    for (int i = 0; i < s.length(); i++){
        if (s[i]=='-'){//no caso de ser um hifen, nao faca nada

        }else if (ispunct(s[i])){ //se for pontuacao, apaga
            s.erase(i,1);
            i-=1;
        }else if(s[i]==' '){ //se for espaco substitui por '*'
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
    for (int i=0; i< s.length(); i++){
        if (s[i]=='*'){//se chegou no fim da palavra, adicione-a ao vetor e deleta o conteudo atual
            Palavras.push_back(palavra);
            palavra.erase(0);
        }else{
            palavra.push_back(s[i]);//c.c. adicione outra letra na palavra
        }
    }
    return Palavras;
}


void read_and_insert(){
    ifstream File ("pagina (1)");
    vector <string> Palavras_da_linha;
    string titulo,line;
    int i = 0;
    size_t inicio_do_titulo, fim_do_titulo;

    if (File.is_open()){
        while (getline(File,line)){
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
                        put_word(tree, *it, Titulos.size());
                    }
                }
            }
        }
        File.close();
    }
}



int main()
{
    /*string txt("Riot Games, Inc. is an American video game developer and esports tournament organizer based in West Los Angeles, California. The company was founded in August 2006 by University of Southern California roommates Brandon Beck and Marc Merrill, as they sought to create a company that continuously improves on an already released game, instead of commencing development on a new one. Riot Games was majority-acquired by Tencent in February 2011 and fully acquired in December 2015. As of May 2018, Riot Games operates 24 offices around the world, in which it employs 2,500 staff members.");
    convert(txt);
    cout << txt << endl;
    for (vector<string>::iterator it = Titulos.begin(); it != Titulos.end(); it++){
        cout << *it << endl;
    } */
    read_and_insert();
    string word;
    while (true) {
        cin >> word;
        search(tree, word);
  }
    return 0;
}
