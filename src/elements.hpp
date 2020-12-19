#pragma once

/**
  \file
  Заголовочный файл, описывающий классы составных частей бесконечной матрицы.
*/

#include <map>
#include <tuple>

template <typename T> using Values = std::map<std::tuple<size_t, size_t>, T>;
template <typename T> using MatrixIterator = typename Values<T>::iterator;

/**
  Интерфейс для хранения данных с адресом.
  @tparam T Тип данных в контейнере.
 */
template <typename T> struct Container {
  Container(size_t row, size_t column, Values<T> &values)
      : row(row), column(column), values(values) {}

protected:
  size_t row, column;
  Values<T> &values;
};

/**
  Ячейка матрицы.
  @tparam T Тип данных в ячейке.
  @tparam std_value Значение для ячейки по умолчанию.
 */
template <typename T, T std_value> struct Cell : public Container<T> {
  /**
    Создать ячейку матрицы.
    @param row Индекс строки.
    @param column Индекс столбца.
    @param value Значение, хранящееся в ячейке.
  */
  Cell(size_t row, size_t column, Values<T> &values)
      : Container<T>(row, column, values){};

  operator T() {
    return (this->values.count({this->row, this->column}) > 0)
               ? this->values[{this->row, this->column}]
               : std_value;
  };

  Cell &operator=(T cell) {
    if (cell != std_value)
      this->values[{this->row, this->column}] = cell;
    else
      this->values.erase({this->row, this->column});

    return *this;
  };
};

/**
    Строка матрицы.
    @tparam T Тип данных в строке.
    @tparam std_value Заполнить этим значением все ячейки строки.
  */
template <typename T, T std_value> struct Row : public Container<T> {
  /**
    Создать строку.
    @param value Значение в ячейке.
    @param row Индекс строки.
  */
  Row(size_t row, Values<T> &values) : Container<T>(row, 0, values) {}

  Cell<T, std_value> operator[](size_t column) {
    return Cell<T, std_value>(this->row, column, this->values);
  };
};
