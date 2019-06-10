//William
#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool number(string &answer) {
  for(char c : answer) {
    if (!isdigit(c))
      return false;
  }
  return true;
}

void print_results(const vector<int> &results) {
  string line_title, line_text, answer  = "y";
  string texts[20];
  int rest, k;
  for (int i = 0; i != results.size() and answer == "y";) {
    rest = (int)results[i]/10000;
    ifstream sorted_titles("sorted_titles/sorted_titles_" + to_string(rest));
    ifstream sorted_texts("sorted_texts/sorted_texts_" + to_string(rest));
    for (k = rest*10000; (int)results[i]/10000 == rest and i != results.size() and answer == "y"; i++) {
      while (results[i] >= k and getline(sorted_titles, line_title) and getline(sorted_texts, line_text))
        k++;
      cout << "[" << i + 1 << "] " << line_title << endl;
      texts[i%20] = line_text;
      if (i+1 != results.size() and i % 20 == 19) {
        cout << "More results? (y, n): ";
        getline(cin >> ws, answer);
      };
    };
    sorted_titles.close();
    sorted_texts.close();
  };
  cout << "Do you want to open any result [n or result number (in the last 20 prints)]? ";
  getline(cin >> ws, answer);
  if (number(answer))
    cout << boost::replace_all_copy(texts[(stoi(answer)-1)%20], "物", "\n");
};

vector<int> intersection(const int results[], const int * counters, const int * indexes, const int &size) {
  vector<int> intersect;
  int counter;
  bool common;
  int k;
  vector<unsigned int>::iterator iters[size];
  vector<unsigned int>::iterator ends[size];
  vector<unsigned int> vectores[size];
  for (int i = 0; i != size; i++) {
    if (results[i] == 0) return intersect;
    counter = counters[results[i]];
    vector<unsigned int> vec(indexes+(counter+1), indexes+(counter+1+indexes[counter]));
    vectores[i] = vec;
    iters[i] = vectores[i].begin();
    ends[i] = vectores[i].end();
  };
  while(iters[0] != ends[0]) {
    common = true;
    for(k = 1; k != size; k++) {
      while(iters[k] != ends[k] and *iters[k] < *iters[0])
        iters[k]++;
      if (iters[k] == ends[k])
        return intersect;
      if (*iters[k] > *iters[0]) {
        common = false;
        k = size-1;
      };
    };
    if (common)
      intersect.push_back(*iters[0]);
    iters[0]++;
  };
  return intersect;
};
