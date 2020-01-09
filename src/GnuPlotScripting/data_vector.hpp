#pragma once

#include "GnuPlotScripting/data.hpp"
#include "GnuPlotScripting/detection_idiom.hpp"

#include <cassert>
#include <sstream>

namespace GnuPlotScripting
{
  // NOTE: support any kind of "vector" (not only std::vector). The
  // required methods are:
  // - size()
  // - operator[]
  //
  // By example
  //
  // std::vector<double> v1(10, 5);
  // std::valarray<int> v2(10);
  // std::string v3("01234567891");
  // Data_Vector test_1(v1, v2, v3);
  //
  // works.
  //
  class Data_Vector final : public Data
  {
    template <typename VECTOR, typename... VECTORs>
    static std::string create_embedded_data(const VECTOR& vector, const VECTORs&... vectors);

    std::size_t _I_size;
    std::size_t _J_size;

   public:
    template <typename VECTOR, typename... VECTORs>
    Data_Vector(const VECTOR& vector, const VECTORs&... vectors)
        : Data(create_embedded_data(vector, vectors...)),
          _I_size(vector.size()),
          _J_size(1 + sizeof...(VECTORs))
    {
    }

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

  //////////////////////////////////////////////////////////////////

  template <typename VECTOR, typename... VECTORs>
  std::string
  Data_Vector::create_embedded_data(const VECTOR& vector, const VECTORs&... vectors)
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

}
