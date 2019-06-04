#include <iostream>
#include <vector>

using namespace std;

/*
  void print_titles(const vector<int> *indexes, const vector<PTI> &titles) {
  if (indexes) {
  answer  = "";
  k = 0;
  //
  last_index = indexes->back();
  vector<PTI> searched_titles;
  for (vector<int>::const_iterator it = indexes->begin(); it != indexes->end(); it++) {
  searched_titles.push_back(titles[*it]);
  }
  quickSort(searched_titles, 0, searched_titles.size());
  //
  for (vector<PTI>::const_iterator index = searched_titles.begin(); index != searched_titles.end() and answer != "n"; k++) {
  cout << "[" << k+1 << "] " << index->titulo << endl;
  ++index;
  if (index != searched_titles.end() and k % 20 == 19) {
  cout << "More results? (y, n): ";
  getline(cin >> ws, answer);
  };
  };
  cout << "Do you want to open any result [n or result number]? ";
  getline(cin >> ws, answer);
  // TO-DO
  };
  };
*/

vector<int> intersection(const int results[], const int * counters, const int * indexes, const int &size) {
  bool common;
  int i, k, counter;
  int positions[size];
  int sizes[size];
  vector<int> intersect;
  vector<int> vectors[size];
  for (i = 0; i < size; i++) {
    if (results[i] == 0) return intersect;
    counter = indexes[counters[results[i]]];
    vectors[i].reserve(counter);
    for(k = 0; k < counter; k++)
      vectors[i][k] = indexes[counters[results[i]]+k+1];
    positions[i] = 0;
    sizes[i] = counter;
  };
  while(positions[0] < sizes[0]) {
    common = true;
    for(i = 1; i < size; i++) {
      while(positions[i] < sizes[i] and vectors[i][positions[i]] < vectors[0][positions[0]])
        positions[i]++;
      if (positions[i] == sizes[i])
        return intersect;
      if (vectors[i][positions[i]] > vectors[0][positions[0]]) {
        common = false;
        i = size;
      };
    };
    if (common)
      intersect.push_back(vectors[0][positions[0]]);
    positions[0]++;
  };
  return intersect;
};
