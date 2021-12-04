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
  ofstream write_file("million_lines_reversed_fifty.txt");
  while (getline(file, str)) {
    lines.push_back(str);
    if (lines.size() == 50) {
      reverse(lines.begin(), lines.end());
      for (const auto line : lines) {
        write_file << line + '\n';
      }
      lines.clear();
    }
  }
}

int main() { _time(solution); }
