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
  class Data_Supervised final : public Data
  {
    template <typename CATEGORY_VECTOR, typename VECTOR, typename... VECTORs>
    std::string
    create_embedded_data(const CATEGORY_VECTOR& category_vector,
                         const VECTOR& vector,
                         const VECTORs&... vectors)
    {
      static_assert(has_size_method_v<CATEGORY_VECTOR> && has_size_method_v<VECTOR> &&
                    (has_size_method_v<VECTORs> && ...));
      static_assert(has_random_access_operator_v<CATEGORY_VECTOR> &&
                    has_random_access_operator_v<VECTOR> &&
                    (has_random_access_operator_v<VECTORs> && ...));

      const size_t n = vector.size();
      assert((n == category_vector.size()) && ((n == vectors.size()) && ...));

      // Sort sample according to their categories
      //
      std::vector<std::size_t> indirection(n);
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

      for (size_t i = 0; i + 1 < n; ++i)
      {
        helper(i);

        if (category_vector[i] != category_vector[i + 1])
        {
          buffer << std::endl << std::endl;
        }
      }
      helper(n - 1);

      return buffer.str();
    }

   public:
    template <typename CATEGORY_VECTOR, typename VECTOR, typename... VECTORs>
    Data_Supervised(const CATEGORY_VECTOR& category_vector,
                    const VECTOR& vector,
                    const VECTORs&... vectors)
        : Data(create_embedded_data(category_vector, vector, vectors...))
    {
    }

    //    std::size_t index_size() const { return index_
  };
}
