#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "util.h"

void solution() {
  ios_base::sync_with_stdio(false);
  ifstream file("million_lines.txt");
  vector<string> lines;
  string str;
  while (getline(file, str)) {
    lines.push_back(str);
  }
  reverse(lines.begin(), lines.end());
  ofstream write_file("million_lines_reversed.txt");
  for (const auto line : lines) {
    write_file << line + '\n';
  }
}

int main() { _time(solution); }
