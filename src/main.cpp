/**
  \file
  Программа, демонстрирующая пример работы с разреженной матрицей.
*/

#include "matrix.hpp"

/**
  Точка старта программы.
*/
int main() {
  {
    const size_t begin = 0;
    const size_t end = 10 - 1;
    InfiniteMatrix<int, 0> matrix;

    // Задать главную диагональ
    for (size_t index = begin; index <= end; index++) {
      matrix[index][index] = index;
    }
    // Задать второстепенную диагональ
    for (size_t index = begin; index <= end; index++) {
      matrix[index][end - index] = end - index;
    }

    matrix.print(begin + 1, end);

    std::cout << "Real count is " << matrix.count() << " cell(s)." << std::endl;

    matrix.printReal();
  }

  return 0;
}
