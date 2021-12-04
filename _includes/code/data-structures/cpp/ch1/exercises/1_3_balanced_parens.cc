#include <util.h>

using namespace std;
#include <map>

bool is_balanced(string seq) {
  map<const char, const char> m = {
      {'{', '}'},
      {'(', ')'},
      {'[', ']'},
  };

  vector<char> stack;

  for (char c : line) {
    if (c == '{' || c == '(' || c == '[') {
      stack.push_back(c);
    } else if (c == '}' || c == ')' || c == ']') {
      char stack_item = stack.pop_back();
      if (!m.count(stack_item) || m[stack_item] != c) {
        return false;
      }
    }
  }
  return true;
}

int main() {}
