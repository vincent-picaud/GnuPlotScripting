#include "GnuPlotScripting/data_array_2.hpp"

#include <string>

namespace GnuPlotScripting
{
  namespace
  {
    std::string
    create_embedded_data(const Array_2& array_2)
    {
      const auto I_size = array_2.I_size();
      const auto J_size = array_2.J_size();

      std::stringstream buffer;

      for (size_t i = 0; i < I_size; ++i)
      {
        for (size_t j = 0; j < J_size; ++j)
        {
          buffer << array_2(i, j) << " ";
        }
        buffer << "\n";
      }

      return buffer.str();
    }
  }

  Data_Array_2::Data_Array_2(const Array_2& array_2)
      : Data(create_embedded_data(array_2)), _I_size(array_2.I_size()), _J_size(array_2.J_size())
  {
  }

}
