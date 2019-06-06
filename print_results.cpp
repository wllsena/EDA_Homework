//William
#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

void print_results(const vector<int> &results) {
  ifstream sorted_titles("sorted_titles.txt");
  ifstream sorted_texts("sorted_texts.txt");
  string line_titles, line_texts, answer  = "y";
  string texts[20];
  for (int i = 0, k = 0; i < results.size() and answer == "y";) {
    while (results[i] >= k and getline(sorted_titles, line_titles) and getline(sorted_texts, line_texts))
      k++;
    cout << "[" << i + 1 << "] " << line_titles << endl;
    texts[i%20] = "---------- " + line_titles + " ----------\n\n" + line_texts;
    i++;
    if (i != results.size() and i != 0 and i % 20 == 0) {
      cout << "More results? (y, n): ";
      getline(cin >> ws, answer);
    };
  };
  cout << "Do you want to open any result [n or result number (in the last 20 prints)]? ";
  getline(cin >> ws, answer);
  if (isdigit(answer[0]) and (answer.length() != 1? isdigit(answer[1]) : true))
    cout << boost::replace_all_copy(texts[(stoi(answer)-1)%20], "物", "\n");
};

vector<int> intersection(const int results[], const int * counters, const int * indexes, const int &size) {
  vector<int> intersect;
  bool common;
  int i, counter;
  vector<int>::iterator iters[size];
  vector<int>::iterator ends[size];
  vector<int> vectores[size];
  for (i = 0; i < size; i++) {
    if (results[i] == 0) return intersect;
    counter = counters[results[i]];
    vector<int> vec(indexes+(counter+1), indexes+(counter+1+indexes[counter]));
    vectores[i] = vec;
    iters[i] = vectores[i].begin();
    ends[i] = vectores[i].end();
  };
  while(iters[0] < ends[0]) {
    common = true;
    for(i = 1; i < size; i++) {
      while(iters[i] < ends[i] and *iters[i] < *iters[0])
        iters[i]++;
      if (iters[i] == ends[i])
        return intersect;
      if (*iters[i] > *iters[0]) {
        common = false;
        i = size;
      };
    };
    if (common)
      intersect.push_back(*iters[0]);
    iters[0]++;
  };
  return intersect;
};
