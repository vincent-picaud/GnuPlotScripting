#pragma once

#include <bits/c++config.h>
#include <cassert>
#include <vector>

namespace GnuPlotScripting
{
  // Motivation:
  //
  // Data_Vector support an arbitrary number of vectors, however this
  // number must be known at compile-time as the contructor take the
  // form:
  //
  // Data_Vector data(v1,v2,...,vn);
  //
  // When one want to define the number of columns at run-time you
  // must use this class as follows:
  //
  // Array_2 array_2(10,5); // 10 rows & 5 columns
  // ...
  // Data_Array_2 data(array_2)
  //
  // Note: there is no way to modify data after construction
  //
  class Array_2
  {
    std::vector<double> _array;
    std::size_t _I_size, _J_size;

    // column-major
    std::size_t
    offset(const std::size_t i, const std::size_t j) const noexcept
    {
      return i + _I_size * j;
    }
    bool
    check_index(const std::size_t i, const std::size_t j) const noexcept
    {
      return i < _I_size and j < _J_size;
    }

   public:
    Array_2() = default;
    Array_2(const std::size_t I_size, const std::size_t J_size)
        : _array(I_size * J_size), _I_size(I_size), _J_size(J_size)
    {
    }
    template <typename LAMBDA>
    Array_2(const std::size_t I_size, const std::size_t J_size, LAMBDA lambda)
        : Array_2(I_size, J_size)
    {
      for (std::size_t i = 0; i < I_size; i++)
        for (std::size_t j = 0; j < J_size; j++) (*this)(i, j) = lambda(i, j);
    }
    std::size_t
    I_size() const noexcept
    {
      return _I_size;
    }
    std::size_t
    J_size() const noexcept
    {
      return _J_size;
    }
    const double&
    operator()(const std::size_t i, const std::size_t j) const
    {
      assert(check_index(i, j));
      return *(_array.data() + offset(i, j));
    }
    double&
    operator()(const std::size_t i, const std::size_t j)
    {
      assert(check_index(i, j));
      return *(_array.data() + offset(i, j));
    }
  };
}
