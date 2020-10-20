#pragma once

#include "GnuPlotScripting/data.hpp"
#include "GnuPlotScripting/array_2.hpp"

#include <cassert>
#include <sstream>

namespace GnuPlotScripting
{
  // Eat a Array_2 (see Array_2 doc for motivation)
  //
  class Data_Array_2 final : public Data
  {
    std::size_t _I_size;
    std::size_t _J_size;

   public:
    Data_Array_2(const Array_2& array_2);

    std::size_t
    I_size() const noexcept
    {
      return _I_size;
    };
    std::size_t
    J_size() const noexcept
    {
      return _J_size;
    };
  };

}
