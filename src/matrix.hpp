#pragma once

/**
  \file
  Заголовочный файл, описывающий основной класс бесконечной матрицы.
*/

#include <iostream>

#include "elements.hpp"

/**
  Бесконечная матрица.
  @tparam T Тип данных в ячейке.
  @tparam std_value Заполнить этим значением все ячейки по умолчанию.
 */
template <typename T, T std_value> struct InfiniteMatrix {
  /**
    Вернуть размер.
    @return Количество реально занятых ячеек.
  */
  size_t count() const { return values.size(); };

  /**
    Очистить матрицу.
  */
  void clear() { values.clear(); }

  /**
    Печать участка матрицы в заданных границах.
    @tparam leftCorner Индекс по диагонали с верхнего левого угла.
    @tparam rightCorner Индекс по диагонали с нижнего правого угла.
  */
  void print(size_t leftCorner, size_t rightCorner) {
    for (size_t i = leftCorner; i < rightCorner; i++) {
      for (size_t j = leftCorner; j < rightCorner; j++) {
        std::cout << (*this)[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  /**
    Напечатать список всех занятых ячеек.
  */
  void printReal() {
    for (const auto cell : *this) {
      int row;
      int column;
      int value;
      std::tie(row, column, value) = cell;
      std::cout << '[' << row << ", " << column << "] = " << value << std::endl;
    }
  }

  /**
    Итератор для матрицы.
   */
  struct Iterator {
    MatrixIterator<T> iterator;
    Iterator(MatrixIterator<T> other) : iterator(other){};

    bool operator==(Iterator &other) { return iterator == other.iterator; }

    bool operator!=(Iterator &other) { return iterator != other.iterator; }

    std::tuple<size_t, size_t, T> operator*() {
      return {std::get<0>(iterator->first), std::get<1>(iterator->first),
              iterator->second};
    }

    Iterator &operator++() {
      ++iterator;
      return *this;
    }

    Iterator &operator--() {
      --iterator;
      return *this;
    }
  };

  /**
    Адресация по указанному индексу строки.
  */
  Row<T, std_value> operator[](size_t row) {
    return Row<T, std_value>(row, values);
  };

  // For "for" support
  Iterator begin() { return values.begin(); };
  Iterator end() { return values.end(); };

private:
  Values<T> values;
};
