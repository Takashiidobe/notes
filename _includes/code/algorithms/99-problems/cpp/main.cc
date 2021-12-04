#include "algorithms/binary_search.h"
#include "algorithms/linear_search.h"
#include "algorithms/reverse_string.h"
#include "lists/last.h"
#include "lists/sum.h"
#include "test/test.h"

using namespace std;

int main() {
  using namespace lists;
  last::test();
  sum::test();

  using namespace algorithms;
  binary_search::test();
  linear_search::test();
  reverse_string::test();
}
