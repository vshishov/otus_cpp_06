#include "matrix.h"

#include <iostream>
#include <memory>
#include <assert.h>

int main(int, const char**) 
{
  Otus::Matrix<int, 0> matrix;
  int nCount = 10;
  for (int i = 0; i < nCount; ++i) {
    matrix[i][i] = i;
    matrix[nCount - 1 - i][i] = nCount - 1 - i;
  }

  int nCountPrint = 8;
  for (int i = 1; i <= nCountPrint; ++i) {
    for (int j = 1; j <= nCountPrint; ++j) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }

  std::cout << matrix.size() << std::endl;

  for (auto c : matrix) {
    int x;
    int y;
    int v;
    std::tie(x, y, v) = c;
    std::cout << x << y << v << std::endl;
  }

  return 0;
}