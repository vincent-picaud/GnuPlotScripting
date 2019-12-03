#pragma once

#include "GnuPlotScripting/data.hpp"
#include "GnuPlotScripting/detection_idiom.hpp"

#include <cassert>
#include <sstream>

namespace GnuPlotScripting
{

  class Data_Vector final : public Data
  {
    template <typename VECTOR, typename... VECTORs>
    std::string
    create_embedded_data(const VECTOR& vector, const VECTORs&... vectors)
    {
      static_assert(has_size_method_v<VECTOR> && (has_size_method_v<VECTORs> && ...));
      static_assert(has_random_access_operator_v<VECTOR> &&
                    (has_random_access_operator_v<VECTORs> && ...));

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
    template <typename VECTOR, typename... VECTORs>
    Data_Vector(const VECTOR& vector, const VECTORs&... vectors)
        : Data(create_embedded_data(vector, vectors...))
    {
    }
  };
}
