#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "util.h"

void solution() {
  ios_base::sync_with_stdio(false);
  ifstream file("million_lines.txt");
  list<string> lines;
  string str;
  while (getline(file, str)) {
    if (str == "\n") {
      _print(lines.front());
    }
    if (lines.size() <= 42) {
      lines.push_back(str);
    } else {
      lines.pop_front();
    }
  }
  ofstream write_file("forty_two.txt");
  for (const auto line : lines) {
    write_file << line + '\n';
  }
}

int main() { _time(solution); }
