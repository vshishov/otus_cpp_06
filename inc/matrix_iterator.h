#pragma once

#include <tuple>

namespace Otus {

template <class I, class T>
class Matrix_Iterator
{
public:
	Matrix_Iterator(I a_data_begin, I a_data_end)
    : m_iterator(a_data_begin)
    , m_iterator_end(a_data_end)
  { }

	auto* operator->()
  {
    auto map_value = this->m_iterator.operator*();
    m_value = std::tuple_cat(map_value.first, std::make_tuple(map_value.second));

    return &m_value;
  }

	auto& operator*()
  {
    auto map_value = this->m_iterator.operator*();
    m_value = std::tuple_cat(map_value.first, std::make_tuple(map_value.second));

    return m_value;
  }

	auto& operator++()
  {
    this->m_iterator = std::next(m_iterator);

    if (this->m_iterator == this->m_iterator_end)
      return m_value;

    auto map_value = m_iterator.operator*();
    m_value = std::tuple_cat(map_value.first, std::make_tuple(map_value.second));

    return m_value;
  }

	auto& operator=(const T& a_data)
  {
    this->m_iterator.second = a_data;

    auto map_value = m_iterator.operator*();
    m_value = std::tuple_cat(map_value.first, std::make_tuple(map_value.second));

    return m_value;
  }

	bool operator!=(const Matrix_Iterator& other)
  {
    return !(*this == other);
  }

	bool operator==(const Matrix_Iterator& other)
  {
    return (this->m_iterator == other.m_iterator);
  }

private:
	T m_value;
	I m_iterator;
	I m_iterator_end;
};

} // Otus::