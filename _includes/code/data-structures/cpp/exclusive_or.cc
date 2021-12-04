#include <iostream>

int main() {
  int x = 400;
  int y = 0;

  x = x ^ y;
  y = y ^ x;
  x = x - y;

  using namespace std;
  cout << x << endl;
  cout << y << endl;
}
