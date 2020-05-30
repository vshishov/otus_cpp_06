#pragma once

#include "matrix_iterator.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <sstream>

namespace Otus{

template<size_t N, class... Args>
struct Matrix_Index
{
	using type = typename Matrix_Index<N-1, size_t, Args...>::type;
};

template<class... Args>
struct Matrix_Index<0, Args...>
{
	using type = std::tuple<Args...>;
};

template<size_t index, class T, size_t size = index>
struct Get_Matrix_Index
{
	void operator()(const T& arg, std::stringstream& buffer) const
	{
		Get_Matrix_Index<index-1, T, size> ()(arg, buffer);
    buffer << std::get<index-1> (arg);

		if (index < size)
      buffer << ":";
	}
};

template<class T, size_t size>
struct Get_Matrix_Index<0, T, size>
{
	void operator()(const T&, std::stringstream&) const
	{}
};

template<size_t index, class D, class S, size_t size = index>
struct Set_Matrix_Index
{
	bool operator()(D &dest, S &src)
	{
		if (src.empty())
			return false;

		std::get<index-1> (dest) = src.back();
		src.pop_back();

		return Set_Matrix_Index <index-1, D, S, size> ()(dest, src);
	}
};

template<class D, class S, size_t size>
struct Set_Matrix_Index<0, D, S, size>
{
	bool operator()(D&, S&)
	{
		return true;
	}
};

template<typename T, T DefaultValue, size_t N = 2>
class Matrix
{
  using Matrix_t = typename Matrix_Index<N>::type;
  using Matrix_Value_t = typename Matrix_Index<N, T>::type;  
  
  struct IndexHash
  {
    size_t operator()(const Matrix_t &s) const
    {
      std::stringstream ss;
      Get_Matrix_Index<std::tuple_size<Matrix_t>::value, Matrix_t>()(s, ss);
      return std::hash<std::string>()(ss.str());
    }
  }; // IndexHash
  
  
 public:

  Matrix() = default;

  Matrix(const Matrix& other)
  { 
    m_Storage = other.m_Storage;
    other.m_CurrIndex.clear();
  }

  Matrix(const Matrix&& other)
    : Matrix()
  { 
    m_Storage = std::move(other.m_Storage);
    other.m_CurrIndex.clear();
  }

  Matrix& operator=(const Matrix& other) 
  {
    if (this != other) {
      this->m_Storage = other.m_Storage;
      other.m_CurrIndex.clear();
    }
    return *this;
  }

  Matrix& operator=(const Matrix&& other)
  {
    if (this != other) {
      this->m_Storage = std::move(other.m_Storage);
      other.m_CurrIndex.clear();
    }
    return *this;
  }

  Matrix& operator[](const std::size_t idx)
  {
    if (this->m_CurrIndex.size() != N)
      this->m_CurrIndex.emplace_back(idx);

    return *this;
  } 

  const T& operator=(const T& _data)
  {
    if (this->m_CurrIndex.size() != N)
      return m_defaultValue;

    Matrix_t dest;
    if (!Set_Matrix_Index<std::tuple_size<Matrix_t>::value, Matrix_t, std::vector<size_t>>()(dest, this->m_CurrIndex))
      return m_defaultValue;

    auto iter = this->m_Storage.find(dest);

    if (iter == this->m_Storage.end() && _data == DefaultValue)
      return m_defaultValue;

    if (_data == DefaultValue)
    {
      this->m_Storage.erase(iter);
      return m_defaultValue;
    }

    this->m_Storage[dest] = _data;
    return this->m_Storage[dest];
  }

  operator const T()
  {
    if (this->m_CurrIndex.size() != N)
		  return m_defaultValue;

    Matrix_t dest;
    if (!Set_Matrix_Index<std::tuple_size<Matrix_t>::value, Matrix_t, std::vector<size_t>>()(dest, this->m_CurrIndex))
      return m_defaultValue;

    auto iter = this->m_Storage.find(dest);

    if (iter == this->m_Storage.end())
      return m_defaultValue;

    return iter->second;
  }
  
  std::size_t size() const
  {
    return m_Storage.size();
  } 

  auto begin()
  {
    return Matrix_Iterator<typename std::unordered_map<Matrix_t, T, IndexHash>::iterator, Matrix_Value_t>(m_Storage.begin(), m_Storage.end());
  }

  auto end()
  {
    return Matrix_Iterator<typename std::unordered_map<Matrix_t, T, IndexHash>::iterator, Matrix_Value_t>(m_Storage.end(), m_Storage.end());
  }

private:
  std::unordered_map<Matrix_t, T, IndexHash> m_Storage;
  mutable std::vector<size_t> m_CurrIndex;
  T m_defaultValue = DefaultValue;
}; // Matrix

} // Otus::