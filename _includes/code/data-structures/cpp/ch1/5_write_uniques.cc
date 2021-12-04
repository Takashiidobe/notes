#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "util.h"

void solution() {
  ifstream file("million_lines.txt");
  map<string, int> unique_lines = {};
  string str;

  vector<int> lines_to_delete;

  size_t line_number = 1;
  while (getline(file, str)) {
    if (unique_lines.contains(str)) {
      _print(str);
    } else {
      unique_lines[str] = line_number;
      lines_to_delete.push_back(line_number);
    }
    line_number++;
  }

  for (const auto item : lines_to_delete) {
    _print(item);
  }
}

int main() { _time(solution); }
