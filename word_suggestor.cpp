#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int min_edit_distance (string& p1, string& p2) {
	int m = p1.size(), n = p2.size(), I = 1, R = 1, S = 1;
	vector <int> linha (n, 0);
	vector < vector <int> > table (m,linha);
	//Inserindo os valores iniciais na matriz/array bidimensional
	for (int i = 0; i < max(m, n); i++) {
		if (i < m) {
			table[i][0] = i;
		}
		if (i < n) {
			table[0][i] = i;
		}
	}
	//Itere por todas as colunas de todas as linhas seguindo a logica do algoritmo
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (p1[i-1] == p2[j-1]) {
				table[i][j] = table[i-1][j-1];
			}
			else {
				table[i][j] = min(table[i - 1][j] + I, min( table[i][j - 1] + R, table[i - 1][j - 1] + S) );
			}
		}
	}
	//O minimum edit distance esta no ultimo elemento da diagonal
	return table[m - 1][n - 1];
}
