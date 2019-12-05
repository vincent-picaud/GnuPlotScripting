#pragma once

#include "GnuPlotScripting/data.hpp"

#include <cassert>

namespace GnuPlotScripting
{
  // NOTE: directly use data defined by a string
  //
  // By example

  // works.
  //
  class Data_Ascii final : public Data
  {
   public:
    Data_Ascii(const std::string& data) : Data(data) {}
  };
}
