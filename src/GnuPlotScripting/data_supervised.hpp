#pragma once

#include "GnuPlotScripting/data.hpp"
#include "GnuPlotScripting/detection_idiom.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>  // iota
#include <sstream>
#include <vector>

namespace GnuPlotScripting
{
  // NOTE: based on Data_Vector and also support any kind of "vector".
  //
  // The idea is to split sample according to their category to be
  // able to plot sample with different point types.
  //
  // One must perform this prepossessing as GnuPlot cannot directly
  // manage point type from column data:
  //
  // See: http://www.gnuplotting.org/plotting-single-points/
  //      https://stackoverflow.com/questions/29622885/how-set-point-type-from-data-in-gnuplot
  //
  class Data_Supervised final : public Data
  {
    template <typename CATEGORY_VECTOR, typename VECTOR, typename... VECTORs>
    static std::string create_embedded_data(const CATEGORY_VECTOR& category_vector,
                                            std::size_t& index_size,
                                            std::size_t& I_size,
                                            std::size_t& J_size,
                                            const VECTOR& vector,
                                            const VECTORs&... vectors);

    std::size_t _index_size;
    std::size_t _I_size;
    std::size_t _J_size;

   public:
    template <typename CATEGORY_VECTOR, typename VECTOR, typename... VECTORs>
    Data_Supervised(const CATEGORY_VECTOR& category_vector,
                    const VECTOR& vector,
                    const VECTORs&... vectors)
        : Data(create_embedded_data(
              category_vector, _index_size, _I_size, _J_size, vector, vectors...))
    {
    }
    std::size_t
    index_size() const noexcept
    {
      return _index_size;
    };
    std::size_t
    I_size() const noexcept
    {
      return _I_size;
    };
    // J_size refers to X J_size, Y category is at position J_size + 1
    std::size_t
    J_size() const noexcept
    {
      return _J_size;
    };
    //    std::size_t index_size() const { return index_
  };

  //////////////////////////////////////////////////////////////////

  template <typename CATEGORY_VECTOR, typename VECTOR, typename... VECTORs>
  std::string
  Data_Supervised::create_embedded_data(const CATEGORY_VECTOR& category_vector,
                                        std::size_t& index_size,
                                        std::size_t& I_size,
                                        std::size_t& J_size,
                                        const VECTOR& vector,
                                        const VECTORs&... vectors)
  {
    static_assert(has_size_method_v<CATEGORY_VECTOR> && has_size_method_v<VECTOR> &&
                  (has_size_method_v<VECTORs> && ...));
    static_assert(has_random_access_operator_v<CATEGORY_VECTOR> &&
                  has_random_access_operator_v<VECTOR> &&
                  (has_random_access_operator_v<VECTORs> && ...));

    index_size = 1;
    I_size     = vector.size();
    J_size     = 1 + sizeof...(vectors);

    assert((I_size == category_vector.size()) && ((I_size == vectors.size()) && ...));

    if (I_size == 0) return {};

    // Sort sample according to their categories
    //
    std::vector<std::size_t> indirection(I_size);
    std::iota(indirection.begin(), indirection.end(), 0);
    std::sort(indirection.begin(), indirection.end(), [&](size_t i, size_t j) {
      return category_vector[i] < category_vector[j];
    });

    std::stringstream buffer;
    auto helper = [&](size_t i) {
      buffer << vector[indirection[i]] << " ";
      ((buffer << vectors[indirection[i]] << " "), ...);
      buffer << category_vector[indirection[i]] << " ";
      buffer << std::endl;
    };

    for (size_t i = 0; i + 1 < I_size; ++i)
    {
      helper(i);

      if (category_vector[i] != category_vector[i + 1])
      {
        ++index_size;
        buffer << std::endl << std::endl;
      }
    }
    helper(I_size - 1);

    return buffer.str();
  }

}
