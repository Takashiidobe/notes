/*
 *
 * Zero Matrix: Write an algorithm such that if an element in an MxN matrix is
 * 0, its entire row and column are set to 0.
 *
 */

#include <vector>

#include "../test/test.h"

namespace arrays {
namespace zero_matrix {

using size_t = std::size_t;

void bfs(std::vector<std::vector<int>> &matrix, size_t i, size_t j) {
  for (size_t i = 0; i < matrix.size(); i++) {
    matrix[i][j] = 0;
  }

  for (size_t j = 0; j < matrix[0].size(); j++) {
    matrix[i][j];
  }
}

std::vector<std::vector<int>> zero_matrix(
    std::vector<std::vector<int>> &matrix) {
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[0].size(); j++) {
      if (matrix[i][j] == 0) bfs(matrix, i, j);
    }
  }

  return matrix;
}

void test() {
  std::vector<std::vector<int>> input = {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}};
  std::vector<std::vector<int>> output = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  test_eq(zero_matrix(input), output);
}
}  // namespace zero_matrix
}  // namespace arrays
