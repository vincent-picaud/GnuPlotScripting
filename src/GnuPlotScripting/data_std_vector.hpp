#pragma once

#include "GnuPlotScripting/data.hpp"

#include <cassert>
#include <sstream>
#include <valarray>
#include <vector>

namespace GnuPlotScripting
{
  class Data_Std_Vector final : public Data
  {
    template <typename T, typename... Ts>
    static std::string
    create_embedded_data(const std::vector<T>& vector, const std::vector<Ts>&... vectors)
    {
      const size_t n = vector.size();
      assert(((n == vectors.size()) && ...));

      std::stringstream buffer;
      for (size_t i = 0; i < n; ++i)
      {
        buffer << vector[i] << " ";
        ((buffer << vectors[i] << " "), ...);
        buffer << "\n";
      }

      return buffer.str();
    }

   public:
    template <typename T, typename... Ts>
    Data_Std_Vector(const std::vector<T>& vector, const std::vector<Ts>&... vectors)
        : Data(create_embedded_data(vector, vectors...))
    {
    }
  };
}
