#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "util.h"

void solution() {
  ifstream file("million_lines.txt");
  vector<string> even_lines;
  vector<string> odd_lines;
  string str;

  size_t counter = 0;
  while (getline(file, str)) {
    if (counter % 2 == 0) {
      even_lines.push_back(str);
    } else {
      odd_lines.push_back(str);
    }
    counter++;
  }

  for (const auto line : even_lines) {
    _print(line);
  }
  for (const auto line : odd_lines) {
    _print(line);
  }
}

int main() { _time(solution); }
