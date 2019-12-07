#pragma once

#include "GnuPlotScripting/data.hpp"

#include <cassert>

namespace GnuPlotScripting
{
  class Data_Ascii final : public Data
  {
   public:
    Data_Ascii(const std::string& data) : Data(data) {}
  };
}
