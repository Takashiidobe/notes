/*
 *
 * Rotate Matrix: Given an image represented by an NxN matrix, where each pixel
 * in the image is 4 bytes, write a method to rotate the image by 90 degrees.
 * Can you do this in place?
 *
 */

#include "../test/test.h"
#include <algorithm>
#include <ranges>

namespace arrays {
namespace rotate_matrix {
std::vector<std::vector<int>> rotate(std::vector<std::vector<int>> &matrix) {
  for (std::size_t i = 0; i < matrix.size(); i++)
    for (std::size_t j = i; j < matrix[0].size(); j++)
      std::swap(matrix[i][j], matrix[j][i]);

  for (std::size_t i = 0; i < matrix.size(); i++)
    std::ranges::reverse(matrix[i]);

  return matrix;
}

void test() {
  std::vector<std::vector<int>> input = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  std::vector<std::vector<int>> output = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
  test_eq(rotate(input), output);

  std::vector<std::vector<int>> input_2 = {
      {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
  std::vector<std::vector<int>> output_2 = {
      {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}};
  test_eq(rotate(input_2), output_2);
}

} // namespace rotate_matrix
} // namespace arrays
