#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "util.h"

void solution() {
  ifstream file("million_lines.txt");
  set<string> lines;
  string str;

  while (getline(file, str)) {
    lines.insert(str);
  }

  vector<string> uniques;

  for (const auto item : lines) {
    uniques.push_back(item);
  }

  sort(uniques.begin(), uniques.end(),
       [](const string &first, const string &second) {
         return first.size() < second.size();
       });

  for (const auto line : uniques) {
    _print(line);
  }
}

int main() { _time(solution); }
