#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "util.h"

void solution() {
  ifstream file("million_lines.txt");
  map<string, int> lines;
  string str;

  while (getline(file, str)) {
    lines[str]++;
  }

  for (const auto [line, occ] : lines) {
    _print(line + ' ' + to_string(occ));
  }
}

int main() { _time(solution); }
