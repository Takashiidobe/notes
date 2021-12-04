#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "util.h"

void solution() {
  ifstream file("million_lines.txt");
  vector<string> lines;
  string str;

  while (getline(file, str)) {
    lines.push_back(str);
  }

  random_shuffle(lines.begin(), lines.end());

  for (const auto line : lines) {
    _print(line);
  }
}

int main() { _time(solution); }
