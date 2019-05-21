#include <iostream>
#include <string>
#include <vector>

using namespace std;


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

int main()
{
    string txt("Riot Games, Inc. is an American video game developer and esports tournament organizer based in West Los Angeles, California. The company was founded in August 2006 by University of Southern California roommates Brandon Beck and Marc Merrill, as they sought to create a company that continuously improves on an already released game, instead of commencing development on a new one. Riot Games was majority-acquired by Tencent in February 2011 and fully acquired in December 2015. As of May 2018, Riot Games operates 24 offices around the world, in which it employs 2,500 staff members.");
    convert(txt);
    cout << txt << endl;
    return 0;
}
