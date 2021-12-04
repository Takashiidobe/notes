#include <cassert>
#include <iostream>
#include <map>
#include <string>

class IntList {
 public:
  int& operator[](const int index);
  const int& operator[](const int index) const;

 private:
  int m_list[10]{};
};

// used for setting
int& IntList::operator[](const int index) {
  assert(index >= 0 && index < 10);
  return m_list[index];
}
// used for getting
const int& IntList::operator[](const int index) const {
  assert(index >= 0 && index < 10);
  return m_list[index];
}

int main() {
  IntList list{};
  list[2] = 3;                   // set a value
  std::cout << list[2] << '\n';  // get a value
  std::cout << list[3] << '\n';

  // std::map can be initialized
  std::map<std::string, char> grades{{"Joe", 'A'}, {"Frank", 'B'}};

  // and assigned
  grades["Susan"] = 'C';
  grades["Tom"] = 'D';

  std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
  std::cout << "Frank has a grade of " << grades["Frank"] << '\n';
  std::cout << "Unknown has a grade of " << grades["Unknown"] << '\n';
}
