#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "util.h"

void solution() {
  ifstream file("million_lines.txt");
  set<string> unique_lines = {};
  string str;

  while (getline(file, str)) {
    if (!unique_lines.contains(str)) {
      _print(str);
      unique_lines.insert(str);
    }
  }
}

int main() { _time(solution); }
